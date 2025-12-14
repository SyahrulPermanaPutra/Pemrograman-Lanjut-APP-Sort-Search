#include "database_mysql.h"
#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;

// Constructor
DatabaseMySQL::DatabaseMySQL(const string& host, const string& user,
    const string& pass, const string& database) {

    try {
        // Initialize MySQL driver
        driver = sql::mysql::get_mysql_driver_instance();

        // Create connection
        con = driver->connect(host, user, pass);

        if (con) {
            con->setSchema(database);
            cout << "[INFO] Connected to MySQL database: " << database << endl;
            connected = true;
        }
        else {
            cerr << "[ERROR] Failed to create connection object" << endl;
            connected = false;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "[ERROR] Connection failed: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        con = nullptr;
        connected = false;
    }
    catch (std::exception& e) {
        cerr << "[ERROR] General error: " << e.what() << endl;
        con = nullptr;
        connected = false;
    }
}

// Destructor
DatabaseMySQL::~DatabaseMySQL() {
    disconnect();
}

// Connect
bool DatabaseMySQL::connect() {
    return isConnected();
}

// Disconnect
void DatabaseMySQL::disconnect() {
    if (con) {
        try {
            con->close();
        }
        catch (...) {
            // Ignore errors during disconnect
        }
        delete con;
        con = nullptr;
        cout << "[INFO] Disconnected from database" << endl;
    }
    connected = false;
}

// Check Connection
bool DatabaseMySQL::isConnected() {
    if (!con) return false;

    try {
        // Simple query to test connection
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT 1");
        delete res;
        delete stmt;
        return true;
    }
    catch (...) {
        return false;
    }
}

// Helper: Convert ResultSet to Lowongan
Lowongan DatabaseMySQL::resultSetToLowongan(sql::ResultSet* res) {
    Lowongan l;

    try {
        l.id = res->getInt("id");
        l.posisi = res->getString("posisi");
        l.perusahaan = res->getString("perusahaan");
        l.jenis_pekerjaan = res->getString("jenis_pekerjaan");
        l.level = res->getString("level");

        l.alamat.jalan = res->getString("jalan");
        l.alamat.kota = res->getString("kota");
        l.alamat.provinsi = res->getString("provinsi");
        l.alamat.kode_pos = res->getString("kode_pos");

        l.gaji.minimal = res->getDouble("gaji_minimal");
        l.gaji.maksimal = res->getDouble("gaji_maksimal");
        l.gaji.tipe = "Per bulan";

        l.requirement.pengalaman_minimal = res->getInt("pengalaman_minimal");
        l.requirement.pendidikan_minimal = res->getString("pendidikan_minimal");
        l.requirement.bahasa = res->getString("bahasa");

        // Skills dari database - untuk sementara kosong, bisa di-extend nanti
        l.requirement.skills_wajib.clear();
        l.requirement.skills_plus.clear();

        l.benefit.asuransi_kesehatan = res->getString("asuransi_kesehatan");

        // Handle boolean columns safely
        try {
            l.benefit.tunjangan_transport = res->getBoolean("tunjangan_transport");
        }
        catch (...) {
            l.benefit.tunjangan_transport = false;
        }

        try {
            l.benefit.tunjangan_makan = res->getBoolean("tunjangan_makan");
        }
        catch (...) {
            l.benefit.tunjangan_makan = false;
        }

        l.benefit.program_pensiun = res->getString("program_pensiun");
        l.benefit.pengembangan_karir = res->getString("pengembangan_karir");

        try {
            l.benefit.cuti_tahunan = res->getInt("cuti_tahunan");
        }
        catch (...) {
            l.benefit.cuti_tahunan = 12;
        }

        l.deskripsi_pekerjaan = res->getString("deskripsi_pekerjaan");
        l.tanggal_post = res->getString("tanggal_post");
        l.jumlah_pelamar = res->getInt("jumlah_pelamar");

        try {
            l.status_aktif = res->getBoolean("status_aktif");
        }
        catch (...) {
            l.status_aktif = true;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "[ERROR] Error converting result set to Lowongan: " << e.what() << endl;
    }
    catch (std::exception& e) {
        cerr << "[ERROR] General error in conversion: " << e.what() << endl;
    }

    return l;
}

// Load All Lowongan
vector<Lowongan> DatabaseMySQL::loadAllLowongan() {
    vector<Lowongan> data;

    if (!isConnected()) {
        cerr << "[ERROR] Not connected to database!" << endl;
        return data;
    }

    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery(
            "SELECT * FROM lowongan WHERE status_aktif = TRUE ORDER BY id"
        );

        while (res->next()) {
            data.push_back(resultSetToLowongan(res));
        }

        delete res;
        delete stmt;

        cout << "[INFO] Loaded " << data.size() << " lowongan from database" << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "[ERROR] Load failed: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
    }
    catch (std::exception& e) {
        cerr << "[ERROR] General error in load: " << e.what() << endl;
    }

    return data;
}

// Create Lowongan
int DatabaseMySQL::createLowongan(const Lowongan& l) {
    if (!isConnected()) return -1;

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO lowongan (posisi, perusahaan, jenis_pekerjaan, level, "
            "jalan, kota, provinsi, kode_pos, gaji_minimal, gaji_maksimal, "
            "pengalaman_minimal, pendidikan_minimal, bahasa, "
            "asuransi_kesehatan, tunjangan_transport, tunjangan_makan, "
            "program_pensiun, pengembangan_karir, cuti_tahunan, "
            "deskripsi_pekerjaan, tanggal_post, jumlah_pelamar, status_aktif) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
        );

        // Set parameters
        int paramIndex = 1;
        pstmt->setString(paramIndex++, l.posisi);
        pstmt->setString(paramIndex++, l.perusahaan);
        pstmt->setString(paramIndex++, l.jenis_pekerjaan);
        pstmt->setString(paramIndex++, l.level);
        pstmt->setString(paramIndex++, l.alamat.jalan);
        pstmt->setString(paramIndex++, l.alamat.kota);
        pstmt->setString(paramIndex++, l.alamat.provinsi);
        pstmt->setString(paramIndex++, l.alamat.kode_pos);
        pstmt->setDouble(paramIndex++, l.gaji.minimal);
        pstmt->setDouble(paramIndex++, l.gaji.maksimal);
        pstmt->setInt(paramIndex++, l.requirement.pengalaman_minimal);
        pstmt->setString(paramIndex++, l.requirement.pendidikan_minimal);
        pstmt->setString(paramIndex++, l.requirement.bahasa);
        pstmt->setString(paramIndex++, l.benefit.asuransi_kesehatan);
        pstmt->setBoolean(paramIndex++, l.benefit.tunjangan_transport);
        pstmt->setBoolean(paramIndex++, l.benefit.tunjangan_makan);
        pstmt->setString(paramIndex++, l.benefit.program_pensiun);
        pstmt->setString(paramIndex++, l.benefit.pengembangan_karir);
        pstmt->setInt(paramIndex++, l.benefit.cuti_tahunan);
        pstmt->setString(paramIndex++, l.deskripsi_pekerjaan);
        pstmt->setString(paramIndex++, l.tanggal_post);
        pstmt->setInt(paramIndex++, l.jumlah_pelamar);
        pstmt->setBoolean(paramIndex++, l.status_aktif);

        pstmt->executeUpdate();

        // Get last insert ID
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT LAST_INSERT_ID() as id");
        int new_id = 0;
        if (res->next()) {
            new_id = res->getInt("id");
        }

        delete res;
        delete stmt;
        delete pstmt;

        cout << "[INFO] Created lowongan ID " << new_id << endl;
        return new_id;
    }
    catch (sql::SQLException& e) {
        cerr << "[ERROR] Create failed: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        return -1;
    }
    catch (std::exception& e) {
        cerr << "[ERROR] General error in create: " << e.what() << endl;
        return -1;
    }
}

// Update Lowongan
bool DatabaseMySQL::updateLowongan(const Lowongan& l) {
    if (!isConnected()) return false;

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "UPDATE lowongan SET posisi=?, perusahaan=?, jenis_pekerjaan=?, level=?, "
            "jalan=?, kota=?, provinsi=?, kode_pos=?, gaji_minimal=?, gaji_maksimal=?, "
            "pengalaman_minimal=?, pendidikan_minimal=?, bahasa=?, "
            "asuransi_kesehatan=?, tunjangan_transport=?, tunjangan_makan=?, "
            "program_pensiun=?, pengembangan_karir=?, cuti_tahunan=?, "
            "deskripsi_pekerjaan=?, tanggal_post=?, jumlah_pelamar=?, status_aktif=? "
            "WHERE id=?"
        );

        // Set parameters
        int paramIndex = 1;
        pstmt->setString(paramIndex++, l.posisi);
        pstmt->setString(paramIndex++, l.perusahaan);
        pstmt->setString(paramIndex++, l.jenis_pekerjaan);
        pstmt->setString(paramIndex++, l.level);
        pstmt->setString(paramIndex++, l.alamat.jalan);
        pstmt->setString(paramIndex++, l.alamat.kota);
        pstmt->setString(paramIndex++, l.alamat.provinsi);
        pstmt->setString(paramIndex++, l.alamat.kode_pos);
        pstmt->setDouble(paramIndex++, l.gaji.minimal);
        pstmt->setDouble(paramIndex++, l.gaji.maksimal);
        pstmt->setInt(paramIndex++, l.requirement.pengalaman_minimal);
        pstmt->setString(paramIndex++, l.requirement.pendidikan_minimal);
        pstmt->setString(paramIndex++, l.requirement.bahasa);
        pstmt->setString(paramIndex++, l.benefit.asuransi_kesehatan);
        pstmt->setBoolean(paramIndex++, l.benefit.tunjangan_transport);
        pstmt->setBoolean(paramIndex++, l.benefit.tunjangan_makan);
        pstmt->setString(paramIndex++, l.benefit.program_pensiun);
        pstmt->setString(paramIndex++, l.benefit.pengembangan_karir);
        pstmt->setInt(paramIndex++, l.benefit.cuti_tahunan);
        pstmt->setString(paramIndex++, l.deskripsi_pekerjaan);
        pstmt->setString(paramIndex++, l.tanggal_post);
        pstmt->setInt(paramIndex++, l.jumlah_pelamar);
        pstmt->setBoolean(paramIndex++, l.status_aktif);
        pstmt->setInt(paramIndex++, l.id);

        int rowsAffected = pstmt->executeUpdate();
        delete pstmt;

        if (rowsAffected > 0) {
            cout << "[INFO] Lowongan ID " << l.id << " updated" << endl;
            return true;
        }
        else {
            cout << "[WARNING] No rows affected for lowongan ID " << l.id << endl;
            return false;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "[ERROR] Update failed: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        return false;
    }
    catch (std::exception& e) {
        cerr << "[ERROR] General error in update: " << e.what() << endl;
        return false;
    }
}

// Delete Lowongan
bool DatabaseMySQL::deleteLowongan(int id) {
    if (!isConnected()) return false;

    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "DELETE FROM lowongan WHERE id = ?"
        );
        pstmt->setInt(1, id);

        int rowsAffected = pstmt->executeUpdate();
        delete pstmt;

        if (rowsAffected > 0) {
            cout << "[INFO] Lowongan ID " << id << " deleted" << endl;
            return true;
        }
        else {
            cout << "[WARNING] No lowongan found with ID " << id << endl;
            return false;
        }
    }
    catch (sql::SQLException& e) {
        cerr << "[ERROR] Delete failed: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        return false;
    }
    catch (std::exception& e) {
        cerr << "[ERROR] General error in delete: " << e.what() << endl;
        return false;
    }
}

// Get Total Lowongan
int DatabaseMySQL::getTotalLowongan() {
    if (!isConnected()) return 0;

    try {
        sql::Statement* stmt = con->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT COUNT(*) as total FROM lowongan");
        int total = 0;
        if (res->next()) {
            total = res->getInt("total");
        }
        delete res;
        delete stmt;
        return total;
    }
    catch (sql::SQLException& e) {
        cerr << "[ERROR] Count failed: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
        return 0;
    }
    catch (std::exception& e) {
        cerr << "[ERROR] General error in count: " << e.what() << endl;
        return 0;
    }
}

// Clear All Data
void DatabaseMySQL::clearAllData() {
    if (!isConnected()) return;

    try {
        sql::Statement* stmt = con->createStatement();
        int rowsAffected = stmt->executeUpdate("DELETE FROM lowongan");
        delete stmt;

        cout << "[INFO] " << rowsAffected << " records cleared from database" << endl;
    }
    catch (sql::SQLException& e) {
        cerr << "[ERROR] Clear failed: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        cerr << "SQLState: " << e.getSQLState() << endl;
    }
    catch (std::exception& e) {
        cerr << "[ERROR] General error in clear: " << e.what() << endl;
    }
}

// Generate Sample Data
int DatabaseMySQL::generateSampleData(int count) {
    if (!isConnected()) {
        cerr << "[ERROR] Not connected to database!" << endl;
        return 0;
    }

    // Data untuk random generation
    vector<string> posisi_list = {
        "Software Engineer", "Data Scientist", "Frontend Developer", "Backend Developer",
        "Full Stack Developer", "DevOps Engineer", "Mobile Developer", "UI/UX Designer",
        "Product Manager", "Project Manager", "Business Analyst", "QA Engineer",
        "Data Analyst", "System Administrator", "Network Engineer", "Security Analyst",
        "AI Engineer", "Machine Learning Engineer", "Cloud Architect", "Database Administrator"
    };

    vector<string> perusahaan_list = {
        "Tech Innovate", "Digital Solutions", "Smart Systems", "Cloud Networks",
        "Data Dynamics", "AI Labs", "Cyber Security Corp", "Mobile Apps Inc",
        "Web Masters", "Code Factory", "Startup Hub", "Enterprise Tech",
        "Global IT", "Indonesia Digital", "Nusantara Tech", "Jakarta Systems",
        "Tokopedia", "Gojek", "Bukalapak", "Traveloka"
    };

    vector<string> kota_list = {
        "Jakarta", "Surabaya", "Bandung", "Medan", "Semarang",
        "Makassar", "Palembang", "Tangerang", "Depok", "Bekasi",
        "Yogyakarta", "Bogor", "Malang", "Batam", "Denpasar"
    };

    vector<string> provinsi_map = {
        "DKI Jakarta", "Jawa Timur", "Jawa Barat", "Sumatera Utara", "Jawa Tengah",
        "Sulawesi Selatan", "Sumatera Selatan", "Banten", "Jawa Barat", "Jawa Barat",
        "DI Yogyakarta", "Jawa Barat", "Jawa Timur", "Kepulauan Riau", "Bali"
    };

    vector<string> jenis_list = { "Full-time", "Part-time", "Remote", "Hybrid" };
    vector<string> level_list = { "Junior", "Middle", "Senior", "Lead" };
    vector<string> pendidikan_list = { "D3", "S1", "S2" };

    // Initialize random seed
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "[INFO] Generating " << count << " sample data..." << endl;

    // Disable autocommit untuk performance
    bool originalAutoCommit = true;
    try {
        originalAutoCommit = con->getAutoCommit();
        con->setAutoCommit(false);
    }
    catch (...) {
        // Ignore if autocommit can't be changed
    }

    int success_count = 0;
    int batch_size = 100;  // Commit setiap 100 record

    auto start_time = chrono::high_resolution_clock::now();

    for (int i = 0; i < count; i++) {
        Lowongan l;

        int kota_idx = rand() % kota_list.size();

        l.posisi = posisi_list[rand() % posisi_list.size()];
        l.perusahaan = perusahaan_list[rand() % perusahaan_list.size()];
        l.jenis_pekerjaan = jenis_list[rand() % jenis_list.size()];
        l.level = level_list[rand() % level_list.size()];

        l.alamat.jalan = "Jl. Sudirman No. " + to_string(rand() % 1000 + 1);
        l.alamat.kota = kota_list[kota_idx];
        l.alamat.provinsi = provinsi_map[kota_idx];
        l.alamat.kode_pos = to_string(10000 + (rand() % 90000));

        double gaji_min = 8.0 + (rand() % 220) / 10.0;  // 8.0 - 30.0
        l.gaji.minimal = gaji_min;
        l.gaji.maksimal = gaji_min + 5.0 + (rand() % 200) / 10.0;  // +5.0 - +25.0
        l.gaji.tipe = "Per bulan";

        l.requirement.pengalaman_minimal = rand() % 11;  // 0-10 tahun
        l.requirement.pendidikan_minimal = pendidikan_list[rand() % pendidikan_list.size()];
        l.requirement.bahasa = "English";

        // Add some skills
        l.requirement.skills_wajib.push_back("Programming");
        l.requirement.skills_wajib.push_back("Problem Solving");

        l.benefit.asuransi_kesehatan = "BPJS + Swasta";
        l.benefit.tunjangan_transport = (rand() % 2) == 1;
        l.benefit.tunjangan_makan = (rand() % 2) == 1;
        l.benefit.program_pensiun = "BPJS Ketengakerjaan";
        l.benefit.pengembangan_karir = "Training & Development";
        l.benefit.cuti_tahunan = 12 + (rand() % 19);  // 12-30 hari

        l.deskripsi_pekerjaan = "Join our team as " + l.posisi + " at " + l.perusahaan +
            ". We offer competitive salary and great benefits.";

        // Generate random date in 2024-2025
        int year = 2024 + (rand() % 2);  // 2024 or 2025
        int month = 1 + (rand() % 12);
        int day = 1 + (rand() % 28);

        char date_buffer[11];
        snprintf(date_buffer, sizeof(date_buffer), "%04d-%02d-%02d", year, month, day);
        l.tanggal_post = string(date_buffer);

        l.jumlah_pelamar = 5 + (rand() % 146);  // 5-150
        l.status_aktif = true;

        if (createLowongan(l) > 0) {
            success_count++;
        }

        // Progress indicator dan batch commit
        if ((i + 1) % batch_size == 0) {
            try {
                con->commit();
                cout << "[PROGRESS] Generated " << (i + 1) << " / " << count << " records ("
                    << success_count << " successful)..." << endl;
            }
            catch (...) {
                // Continue even if commit fails
            }
        }
    }

    // Final commit
    try {
        con->commit();
    }
    catch (...) {
        // Ignore final commit errors
    }

    // Restore autocommit setting
    try {
        con->setAutoCommit(originalAutoCommit);
    }
    catch (...) {
        // Ignore if can't restore
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time);

    cout << "[SUCCESS] Generated " << success_count << " out of " << count << " records" << endl;
    cout << "[INFO] Time taken: " << duration.count() << " seconds" << endl;

    return success_count;
}

// Get connection status
bool DatabaseMySQL::getConnectionStatus() const {
    return connected;
}