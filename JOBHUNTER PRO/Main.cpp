#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <limits>
#include "database.h"
#include "database_mysql.h"
#include "search.h"
#include "sort.h"
#include "display.h"
#include "auth.h"
#include "json_handler.h"

using namespace std;

// Global variables
static DatabaseMySQL* db = nullptr;
static AuthSystem authSystem;
static vector<Lowongan> global_data;  // Ganti nama dari 'data' ke 'global_data'

// Forward declarations
static void menu_admin();
static void menu_user();
static void refresh_data();

// ==================== UTILITY FUNCTIONS ====================

static void clear_input_buffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ==================== ADMIN FUNCTIONS ====================

static void admin_tambah_lowongan() {
    header_aplikasi();
    cout << "=== TAMBAH LOWONGAN BARU ===" << endl << endl;

    Lowongan l;

    cout << "Posisi: ";
    clear_input_buffer();
    getline(cin, l.posisi);

    cout << "Perusahaan: ";
    getline(cin, l.perusahaan);

    cout << "Jenis Pekerjaan (Full-time/Part-time/Remote/Hybrid): ";
    getline(cin, l.jenis_pekerjaan);

    cout << "Level (Junior/Middle/Senior/Lead): ";
    getline(cin, l.level);

    cout << "\n--- Alamat ---" << endl;
    cout << "Jalan: ";
    getline(cin, l.alamat.jalan);

    cout << "Kota: ";
    getline(cin, l.alamat.kota);

    cout << "Provinsi: ";
    getline(cin, l.alamat.provinsi);

    cout << "Kode Pos: ";
    getline(cin, l.alamat.kode_pos);

    cout << "\n--- Gaji ---" << endl;
    cout << "Gaji Minimal (juta): ";
    cin >> l.gaji.minimal;

    cout << "Gaji Maksimal (juta): ";
    cin >> l.gaji.maksimal;

    l.gaji.tipe = "Per bulan";

    cout << "\n--- Requirement ---" << endl;
    cout << "Pengalaman Minimal (tahun): ";
    cin >> l.requirement.pengalaman_minimal;

    cout << "Pendidikan Minimal (D3/S1/S2/S3): ";
    clear_input_buffer();
    getline(cin, l.requirement.pendidikan_minimal);

    cout << "Bahasa: ";
    getline(cin, l.requirement.bahasa);

    // Skills (simplified)
    l.requirement.skills_wajib.push_back("Programming");
    l.requirement.skills_plus.push_back("Communication");

    cout << "\n--- Benefit ---" << endl;
    cout << "Asuransi Kesehatan: ";
    getline(cin, l.benefit.asuransi_kesehatan);

    char response;
    cout << "Tunjangan Transport (y/n): ";
    cin >> response;
    l.benefit.tunjangan_transport = (response == 'y' || response == 'Y');

    cout << "Tunjangan Makan (y/n): ";
    cin >> response;
    l.benefit.tunjangan_makan = (response == 'y' || response == 'Y');

    clear_input_buffer();
    cout << "Program Pensiun: ";
    getline(cin, l.benefit.program_pensiun);

    cout << "Pengembangan Karir: ";
    getline(cin, l.benefit.pengembangan_karir);

    cout << "Cuti Tahunan (hari): ";
    cin >> l.benefit.cuti_tahunan;

    clear_input_buffer();
    cout << "\nDeskripsi Pekerjaan: ";
    getline(cin, l.deskripsi_pekerjaan);

    // Auto-fill
    l.tanggal_post = "2025-12-14";
    l.jumlah_pelamar = 0;
    l.status_aktif = true;

    // Save to database
    int new_id = db->createLowongan(l);

    if (new_id > 0) {
        cout << "\n[SUCCESS] Lowongan berhasil ditambahkan dengan ID: " << new_id << endl;
        refresh_data();
    }
    else {
        cout << "\n[ERROR] Gagal menambahkan lowongan!" << endl;
    }
}

static void admin_edit_lowongan() {
    header_aplikasi();
    cout << "=== EDIT LOWONGAN ===" << endl << endl;

    tampilkan_semua_lowongan(global_data);

    int id;
    cout << "\nMasukkan ID lowongan yang ingin diedit: ";
    cin >> id;

    // Find lowongan
    int index = -1;
    for (size_t i = 0; i < global_data.size(); i++) {  // Gunakan size_t
        if (global_data[i].id == id) {
            index = static_cast<int>(i);  // Konversi ke int
            break;
        }
    }

    if (index == -1) {
        cout << "[ERROR] Lowongan dengan ID " << id << " tidak ditemukan!" << endl;
        return;
    }

    Lowongan& l = global_data[index];

    cout << "\n--- Data Saat Ini ---" << endl;
    tampilkan_lowongan(l);

    cout << "\n--- Edit Data (Enter untuk skip) ---" << endl;
    clear_input_buffer();

    string input;

    cout << "Posisi [" << l.posisi << "]: ";
    getline(cin, input);
    if (!input.empty()) l.posisi = input;

    cout << "Perusahaan [" << l.perusahaan << "]: ";
    getline(cin, input);
    if (!input.empty()) l.perusahaan = input;

    cout << "Jenis Pekerjaan [" << l.jenis_pekerjaan << "]: ";
    getline(cin, input);
    if (!input.empty()) l.jenis_pekerjaan = input;

    cout << "Level [" << l.level << "]: ";
    getline(cin, input);
    if (!input.empty()) l.level = input;

    cout << "Kota [" << l.alamat.kota << "]: ";
    getline(cin, input);
    if (!input.empty()) l.alamat.kota = input;

    cout << "Gaji Minimal [" << l.gaji.minimal << "]: ";
    getline(cin, input);
    if (!input.empty()) l.gaji.minimal = stod(input);

    cout << "Gaji Maksimal [" << l.gaji.maksimal << "]: ";
    getline(cin, input);
    if (!input.empty()) l.gaji.maksimal = stod(input);

    // Update to database
    if (db->updateLowongan(l)) {
        cout << "\n[SUCCESS] Lowongan berhasil diupdate!" << endl;
        refresh_data();
    }
    else {
        cout << "\n[ERROR] Gagal mengupdate lowongan!" << endl;
    }
}

static void admin_hapus_lowongan() {
    header_aplikasi();
    cout << "=== HAPUS LOWONGAN ===" << endl << endl;

    tampilkan_semua_lowongan(global_data);

    int id;
    cout << "\nMasukkan ID lowongan yang ingin dihapus: ";
    cin >> id;

    cout << "Apakah Anda yakin ingin menghapus lowongan ID " << id << "? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        if (db->deleteLowongan(id)) {
            cout << "\n[SUCCESS] Lowongan berhasil dihapus!" << endl;
            refresh_data();
        }
        else {
            cout << "\n[ERROR] Gagal menghapus lowongan!" << endl;
        }
    }
    else {
        cout << "\nPenghapusan dibatalkan." << endl;
    }
}

static void admin_export_json() {
    header_aplikasi();
    cout << "=== EXPORT DATA KE JSON ===" << endl << endl;

    string filename;
    cout << "Nama file (tanpa .json): ";
    clear_input_buffer();
    getline(cin, filename);
    filename += ".json";

    if (JSONHandler::saveToJSON(global_data, filename)) {
        cout << "\n[SUCCESS] Data berhasil di-export ke " << filename << endl;
    }
    else {
        cout << "\n[ERROR] Gagal export data!" << endl;
    }
}

static void admin_import_json() {
    header_aplikasi();
    cout << "=== IMPORT DATA DARI JSON ===" << endl << endl;

    string filename;
    cout << "Nama file (dengan .json): ";
    clear_input_buffer();
    getline(cin, filename);

    vector<Lowongan> imported_data = JSONHandler::loadFromJSON(filename);

    if (!imported_data.empty()) {
        cout << "\nDitemukan " << imported_data.size() << " lowongan dari file JSON." << endl;
        cout << "Import ke database? (y/n): ";
        char confirm;
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y') {
            int success = 0;
            for (const auto& l : imported_data) {
                if (db->createLowongan(l) > 0) {
                    success++;
                }
            }
            cout << "\n[SUCCESS] Berhasil import " << success << " dari " << imported_data.size() << " lowongan" << endl;
            refresh_data();
        }
    }
    else {
        cout << "\n[ERROR] Gagal membaca file atau file kosong!" << endl;
    }
}

static void menu_admin() {
    int pilihan;

    do {
        header_aplikasi();
        cout << "LOGGED IN AS: ADMIN (" << authSystem.getCurrentUsername() << ")" << endl;
        cout << "DATABASE: " << global_data.size() << " lowongan" << endl;
        cout << "=========================================" << endl;
        cout << "         MENU ADMINISTRATOR" << endl;
        cout << "=========================================" << endl;
        cout << "1. Tampilkan Semua Lowongan" << endl;
        cout << "2. Tambah Lowongan Baru" << endl;
        cout << "3. Edit Lowongan" << endl;
        cout << "4. Hapus Lowongan" << endl;
        cout << "5. Export Data ke JSON" << endl;
        cout << "6. Import Data dari JSON" << endl;
        cout << "7. Generate Sample Data" << endl;
        cout << "8. Clear All Data" << endl;
        cout << "9. Refresh Data" << endl;
        cout << "0. Logout" << endl;
        cout << "=========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            header_aplikasi();
            tampilkan_semua_lowongan(global_data);
            break;
        }
        case 2: {
            admin_tambah_lowongan();
            break;
        }
        case 3: {
            admin_edit_lowongan();
            break;
        }
        case 4: {
            admin_hapus_lowongan();
            break;
        }
        case 5: {
            admin_export_json();
            break;
        }
        case 6: {
            admin_import_json();
            break;
        }
        case 7: {
            header_aplikasi();
            int count;
            cout << "Jumlah data yang akan di-generate: ";
            cin >> count;

            cout << "\nGenerating " << count << " sample data..." << endl;
            int generated = db->generateSampleData(count);

            if (generated > 0) {
                cout << "[SUCCESS] Berhasil generate " << generated << " data!" << endl;
                refresh_data();
            }
            break;
        }
        case 8: {
            header_aplikasi();
            cout << "PERINGATAN: Semua data akan dihapus!" << endl;
            cout << "Ketik 'CONFIRM' untuk melanjutkan: ";
            string confirm;
            cin >> confirm;

            if (confirm == "CONFIRM") {
                db->clearAllData();
                refresh_data();
                cout << "[SUCCESS] Semua data telah dihapus!" << endl;
            }
            break;
        }
        case 9: {
            refresh_data();
            cout << "[SUCCESS] Data berhasil di-refresh!" << endl;
            break;
        }
        case 0: {
            cout << "Logging out..." << endl;
            break;
        }
        default: {
            cout << "Pilihan tidak valid!" << endl;
        }
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            clear_input_buffer();
            cin.get();
        }

    } while (pilihan != 0);
}

// ==================== USER FUNCTIONS ====================

static void user_search_menu() {
    int pilihan;

    do {
        header_aplikasi();
        cout << "=========================================" << endl;
        cout << "           MENU PENCARIAN" << endl;
        cout << "=========================================" << endl;
        cout << "1. Cari berdasarkan Posisi" << endl;
        cout << "2. Cari berdasarkan Perusahaan" << endl;
        cout << "3. Cari berdasarkan Kota" << endl;
        cout << "4. Cari berdasarkan Rentang Gaji" << endl;
        cout << "5. Cari berdasarkan Jenis Pekerjaan" << endl;
        cout << "6. Cari berdasarkan Level" << endl;
        cout << "7. Pencarian Advanced" << endl;
        cout << "0. Kembali" << endl;
        cout << "=========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            header_aplikasi();
            string keyword;
            cout << "Kata kunci posisi: ";
            clear_input_buffer();
            getline(cin, keyword);

            vector<int> hasil = blok_search_by_posisi_partial(global_data, keyword);
            if (!hasil.empty()) {
                cout << "\nDitemukan " << hasil.size() << " lowongan:\n" << endl;
                for (int idx : hasil) {
                    tampilkan_lowongan(global_data[idx]);
                }
            }
            else {
                cout << "\nTidak ada hasil." << endl;
            }
            break;
        }
        case 2: {
            header_aplikasi();
            string keyword;
            cout << "Nama perusahaan: ";
            clear_input_buffer();
            getline(cin, keyword);

            vector<int> hasil = search_by_perusahaan(global_data, keyword);
            if (!hasil.empty()) {
                cout << "\nDitemukan " << hasil.size() << " lowongan:\n" << endl;
                for (int idx : hasil) {
                    tampilkan_lowongan(global_data[idx]);
                }
            }
            else {
                cout << "\nTidak ada hasil." << endl;
            }
            break;
        }
        case 3: {
            header_aplikasi();
            string kota;
            cout << "Nama kota: ";
            clear_input_buffer();
            getline(cin, kota);

            vector<int> hasil = search_by_kota(global_data, kota);
            if (!hasil.empty()) {
                cout << "\nDitemukan " << hasil.size() << " lowongan:\n" << endl;
                for (int idx : hasil) {
                    tampilkan_lowongan(global_data[idx]);
                }
            }
            else {
                cout << "\nTidak ada hasil." << endl;
            }
            break;
        }
        case 4: {
            header_aplikasi();
            double min_gaji, max_gaji;
            cout << "Gaji minimal (juta): ";
            cin >> min_gaji;
            cout << "Gaji maksimal (juta): ";
            cin >> max_gaji;

            vector<int> hasil = search_by_gaji_range(global_data, min_gaji, max_gaji);
            if (!hasil.empty()) {
                cout << "\nDitemukan " << hasil.size() << " lowongan:\n" << endl;
                for (int idx : hasil) {
                    tampilkan_lowongan(global_data[idx]);
                }
            }
            else {
                cout << "\nTidak ada hasil." << endl;
            }
            break;
        }
        case 5: {
            header_aplikasi();
            cout << "Jenis Pekerjaan:" << endl;
            cout << "1. Full-time" << endl;
            cout << "2. Part-time" << endl;
            cout << "3. Remote" << endl;
            cout << "4. Hybrid" << endl;
            cout << "Pilih: ";
            int jenis_pilih;
            cin >> jenis_pilih;

            string jenis;
            switch (jenis_pilih) {
            case 1: jenis = "Full-time"; break;
            case 2: jenis = "Part-time"; break;
            case 3: jenis = "Remote"; break;
            case 4: jenis = "Hybrid"; break;
            default: jenis = "Full-time";
            }

            vector<int> hasil = search_by_jenis_pekerjaan(global_data, jenis);
            if (!hasil.empty()) {
                cout << "\nDitemukan " << hasil.size() << " lowongan " << jenis << ":\n" << endl;
                for (int idx : hasil) {
                    tampilkan_lowongan(global_data[idx]);
                }
            }
            else {
                cout << "\nTidak ada hasil." << endl;
            }
            break;
        }
        case 6: {
            header_aplikasi();
            cout << "Level:" << endl;
            cout << "1. Junior" << endl;
            cout << "2. Middle" << endl;
            cout << "3. Senior" << endl;
            cout << "4. Lead" << endl;
            cout << "Pilih: ";
            int level_pilih;
            cin >> level_pilih;

            string level;
            switch (level_pilih) {
            case 1: level = "Junior"; break;
            case 2: level = "Middle"; break;
            case 3: level = "Senior"; break;
            case 4: level = "Lead"; break;
            default: level = "Junior";
            }

            vector<int> hasil = search_by_level(global_data, level);
            if (!hasil.empty()) {
                cout << "\nDitemukan " << hasil.size() << " lowongan level " << level << ":\n" << endl;
                for (int idx : hasil) {
                    tampilkan_lowongan(global_data[idx]);
                }
            }
            else {
                cout << "\nTidak ada hasil." << endl;
            }
            break;
        }
        case 7: {
            header_aplikasi();
            cout << "=== PENCARIAN ADVANCED ===" << endl << endl;

            string posisi, kota, jenis, level;
            double min_gaji, max_gaji;

            clear_input_buffer();
            cout << "Kata kunci posisi (kosongkan untuk skip): ";
            getline(cin, posisi);

            cout << "Kota (kosongkan untuk skip): ";
            getline(cin, kota);

            cout << "Gaji minimal (0 untuk skip): ";
            cin >> min_gaji;

            cout << "Gaji maksimal (999 untuk skip): ";
            cin >> max_gaji;

            clear_input_buffer();
            cout << "Jenis pekerjaan (kosongkan untuk skip): ";
            getline(cin, jenis);

            cout << "Level (kosongkan untuk skip): ";
            getline(cin, level);

            vector<int> hasil = advanced_search(global_data, posisi, kota, min_gaji, max_gaji, jenis, level);

            if (!hasil.empty()) {
                cout << "\nDitemukan " << hasil.size() << " lowongan yang sesuai:\n" << endl;
                for (int idx : hasil) {
                    tampilkan_lowongan(global_data[idx]);
                }
            }
            else {
                cout << "\nTidak ada hasil yang sesuai kriteria." << endl;
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            clear_input_buffer();
            cin.get();
        }

    } while (pilihan != 0);
}

static void user_sort_menu() {
    int pilihan;

    do {
        header_aplikasi();
        cout << "=========================================" << endl;
        cout << "           MENU SORTING" << endl;
        cout << "=========================================" << endl;
        cout << "1. Urutkan berdasarkan Gaji" << endl;
        cout << "2. Urutkan berdasarkan Jumlah Pelamar" << endl;
        cout << "3. Urutkan berdasarkan Tanggal Post" << endl;
        cout << "4. Urutkan berdasarkan Posisi (A-Z)" << endl;
        cout << "5. Urutkan berdasarkan Perusahaan" << endl;
        cout << "6. Urutkan berdasarkan Kota" << endl;
        cout << "0. Kembali" << endl;
        cout << "=========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan >= 1 && pilihan <= 6) {
            cout << "\nUrutan:" << endl;
            cout << "1. Ascending (kecil ke besar / A-Z)" << endl;
            cout << "2. Descending (besar ke kecil / Z-A)" << endl;
            cout << "Pilih: ";
            int order;
            cin >> order;
            bool ascending = (order == 1);

            vector<Lowongan> sorted_data = global_data;

            // Konversi size_t ke int untuk parameter fungsi sort
            int size_int = static_cast<int>(sorted_data.size());
            int high_index = size_int > 0 ? size_int - 1 : 0;

            switch (pilihan) {
            case 1:
                merge_sort_by_gaji(sorted_data, 0, high_index, ascending);
                header_aplikasi();
                cout << "Diurutkan berdasarkan Gaji (" << (ascending ? "Terendah" : "Tertinggi") << "):\n" << endl;
                break;
            case 2:
                merge_sort_by_pelamar(sorted_data, 0, high_index, ascending);
                header_aplikasi();
                cout << "Diurutkan berdasarkan Jumlah Pelamar (" << (ascending ? "Terendah" : "Terbanyak") << "):\n" << endl;
                break;
            case 3:
                merge_sort_by_tanggal(sorted_data, 0, high_index, ascending);
                header_aplikasi();
                cout << "Diurutkan berdasarkan Tanggal (" << (ascending ? "Terlama" : "Terbaru") << "):\n" << endl;
                break;
            case 4:
                quick_sort_by_posisi(sorted_data, 0, high_index, ascending);
                header_aplikasi();
                cout << "Diurutkan berdasarkan Posisi (" << (ascending ? "A-Z" : "Z-A") << "):\n" << endl;
                break;
            case 5:
                quick_sort_by_perusahaan(sorted_data, 0, high_index, ascending);
                header_aplikasi();
                cout << "Diurutkan berdasarkan Perusahaan (" << (ascending ? "A-Z" : "Z-A") << "):\n" << endl;
                break;
            case 6:
                quick_sort_by_kota(sorted_data, 0, high_index, ascending);
                header_aplikasi();
                cout << "Diurutkan berdasarkan Kota (" << (ascending ? "A-Z" : "Z-A") << "):\n" << endl;
                break;
            }

            tampilkan_semua_lowongan(sorted_data);
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            clear_input_buffer();
            cin.get();
        }

    } while (pilihan != 0);
}

static void menu_user() {
    int pilihan;

    do {
        header_aplikasi();
        cout << "LOGGED IN AS: USER (" << authSystem.getCurrentUsername() << ")" << endl;
        cout << "DATABASE: " << global_data.size() << " lowongan" << endl;
        cout << "=========================================" << endl;
        cout << "             MENU USER" << endl;
        cout << "=========================================" << endl;
        cout << "1. Lihat Semua Lowongan" << endl;
        cout << "2. Cari Lowongan (Search)" << endl;
        cout << "3. Urutkan Lowongan (Sort)" << endl;
        cout << "4. Lihat Lowongan Remote" << endl;
        cout << "5. Lihat Lowongan Terbaru" << endl;
        cout << "6. Export Hasil ke JSON" << endl;
        cout << "7. Refresh Data" << endl;
        cout << "0. Logout" << endl;
        cout << "=========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            header_aplikasi();
            tampilkan_semua_lowongan(global_data);
            break;
        }
        case 2: {
            user_search_menu();
            break;
        }
        case 3: {
            user_sort_menu();
            break;
        }
        case 4: {
            header_aplikasi();
            tampilkan_lowongan_remote(global_data);
            break;
        }
        case 5: {
            header_aplikasi();
            vector<Lowongan> sorted = global_data;

            // Konversi size_t ke int
            int size_int = static_cast<int>(sorted.size());
            int high_index = size_int > 0 ? size_int - 1 : 0;

            merge_sort_by_tanggal(sorted, 0, high_index, false);
            cout << "LOWONGAN TERBARU:\n" << endl;

            // Tampilkan 10 terbaru
            int count = min(10, size_int);
            for (int i = 0; i < count; i++) {
                tampilkan_lowongan(sorted[i]);
            }
            break;
        }
        case 6: {
            header_aplikasi();
            string filename;
            cout << "Nama file (tanpa .json): ";
            clear_input_buffer();
            getline(cin, filename);
            filename += ".json";

            JSONHandler::saveToJSON(global_data, filename);
            break;
        }
        case 7: {
            refresh_data();
            cout << "[SUCCESS] Data berhasil di-refresh!" << endl;
            break;
        }
        case 0: {
            cout << "Logging out..." << endl;
            break;
        }
        default: {
            cout << "Pilihan tidak valid!" << endl;
        }
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            clear_input_buffer();
            cin.get();
        }

    } while (pilihan != 0);
}

// ==================== MAIN FUNCTIONS ====================

static void refresh_data() {
    global_data = db->loadAllLowongan();
}

static void login_screen() {
    while (true) {
        header_aplikasi();
        cout << "=========================================" << endl;
        cout << "              LOGIN SYSTEM" << endl;
        cout << "=========================================" << endl;
        cout << "\nDefault Accounts:" << endl;
        cout << "  Admin - username: admin | password: admin123" << endl;
        cout << "  User  - username: user  | password: user123" << endl;
        cout << "\n=========================================" << endl;

        string username, password;

        cout << "\nUsername: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        if (authSystem.login(username, password)) {
            cout << "\n[SUCCESS] Login berhasil!" << endl;
            cout << "Selamat datang, " << username << "!" << endl;

            cout << "\nTekan Enter untuk melanjutkan...";
            clear_input_buffer();
            cin.get();

            // Route to appropriate menu
            if (authSystem.getCurrentUserRole() == ROLE_ADMIN) {
                menu_admin();
            }
            else {
                menu_user();
            }

            authSystem.logout();
        }
        else {
            cout << "\n[ERROR] Username atau password salah!" << endl;
            cout << "\nTekan Enter untuk mencoba lagi...";
            clear_input_buffer();
            cin.get();
        }
    }
}

int main() {
    cout << "=========================================" << endl;
    cout << "  JOBHUNTER PRO v3.0 - Full Edition" << endl;
    cout << "=========================================" << endl;
    cout << endl;

    // Database Configuration
    string db_host = "tcp://127.0.0.1:3306";
    string db_user = "root";
    string db_pass = "";  // GANTI dengan password MySQL Anda
    string db_name = "jobhunter_db";

    cout << "[INFO] Connecting to MySQL Database..." << endl;

    db = new DatabaseMySQL(db_host, db_user, db_pass, db_name);

    if (!db->isConnected()) {
        cerr << "\n[ERROR] Gagal koneksi ke database!" << endl;
        cerr << "Pastikan MySQL Server running dan database sudah dibuat." << endl;
        delete db;
        return 1;
    }

    // Load initial data
    refresh_data();

    if (global_data.empty()) {
        cout << "\n[WARNING] Database kosong!" << endl;
        cout << "Silakan login sebagai admin untuk menambah data." << endl;
    }

    cout << "\n[SUCCESS] Sistem siap digunakan!" << endl;
    cout << "Total lowongan di database: " << global_data.size() << endl;

    cout << "\nTekan Enter untuk login...";
    cin.get();

    // Start login screen
    login_screen();

    // Cleanup
    db->disconnect();
    delete db;
    db = nullptr;

    return 0;
}