#include "json_handler.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

string JSONHandler::escapeJSON(const string& str) {
    string result;
    for (char c : str) {
        switch (c) {
        case '"': result += "\\\""; break;
        case '\\': result += "\\\\"; break;
        case '\n': result += "\\n"; break;
        case '\r': result += "\\r"; break;
        case '\t': result += "\\t"; break;
        default: result += c;
        }
    }
    return result;
}

string JSONHandler::vectorToJSON(const vector<string>& vec) {
    string result = "[";
    for (size_t i = 0; i < vec.size(); i++) {
        result += "\"" + escapeJSON(vec[i]) + "\"";
        if (i < vec.size() - 1) result += ",";
    }
    result += "]";
    return result;
}

bool JSONHandler::saveToJSON(const vector<Lowongan>& data, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "[ERROR] Cannot open file: " << filename << endl;
        return false;
    }

    file << "[\n";

    for (size_t i = 0; i < data.size(); i++) {
        const Lowongan& l = data[i];

        file << "  {\n";
        file << "    \"id\": " << l.id << ",\n";
        file << "    \"posisi\": \"" << escapeJSON(l.posisi) << "\",\n";
        file << "    \"perusahaan\": \"" << escapeJSON(l.perusahaan) << "\",\n";
        file << "    \"jenis_pekerjaan\": \"" << escapeJSON(l.jenis_pekerjaan) << "\",\n";
        file << "    \"level\": \"" << escapeJSON(l.level) << "\",\n";

        file << "    \"alamat\": {\n";
        file << "      \"jalan\": \"" << escapeJSON(l.alamat.jalan) << "\",\n";
        file << "      \"kota\": \"" << escapeJSON(l.alamat.kota) << "\",\n";
        file << "      \"provinsi\": \"" << escapeJSON(l.alamat.provinsi) << "\",\n";
        file << "      \"kode_pos\": \"" << escapeJSON(l.alamat.kode_pos) << "\"\n";
        file << "    },\n";

        file << "    \"gaji\": {\n";
        file << "      \"minimal\": " << l.gaji.minimal << ",\n";
        file << "      \"maksimal\": " << l.gaji.maksimal << ",\n";
        file << "      \"tipe\": \"" << escapeJSON(l.gaji.tipe) << "\"\n";
        file << "    },\n";

        file << "    \"requirement\": {\n";
        file << "      \"pengalaman_minimal\": " << l.requirement.pengalaman_minimal << ",\n";
        file << "      \"pendidikan_minimal\": \"" << escapeJSON(l.requirement.pendidikan_minimal) << "\",\n";
        file << "      \"skills_wajib\": " << vectorToJSON(l.requirement.skills_wajib) << ",\n";
        file << "      \"skills_plus\": " << vectorToJSON(l.requirement.skills_plus) << ",\n";
        file << "      \"bahasa\": \"" << escapeJSON(l.requirement.bahasa) << "\"\n";
        file << "    },\n";

        file << "    \"benefit\": {\n";
        file << "      \"asuransi_kesehatan\": \"" << escapeJSON(l.benefit.asuransi_kesehatan) << "\",\n";
        file << "      \"tunjangan_transport\": " << (l.benefit.tunjangan_transport ? "true" : "false") << ",\n";
        file << "      \"tunjangan_makan\": " << (l.benefit.tunjangan_makan ? "true" : "false") << ",\n";
        file << "      \"program_pensiun\": \"" << escapeJSON(l.benefit.program_pensiun) << "\",\n";
        file << "      \"pengembangan_karir\": \"" << escapeJSON(l.benefit.pengembangan_karir) << "\",\n";
        file << "      \"cuti_tahunan\": " << l.benefit.cuti_tahunan << "\n";
        file << "    },\n";

        file << "    \"deskripsi_pekerjaan\": \"" << escapeJSON(l.deskripsi_pekerjaan) << "\",\n";
        file << "    \"tanggal_post\": \"" << l.tanggal_post << "\",\n";
        file << "    \"jumlah_pelamar\": " << l.jumlah_pelamar << ",\n";
        file << "    \"status_aktif\": " << (l.status_aktif ? "true" : "false") << "\n";

        file << "  }";
        if (i < data.size() - 1) file << ",";
        file << "\n";
    }

    file << "]\n";
    file.close();

    cout << "[SUCCESS] Data saved to " << filename << endl;
    return true;
}

vector<string> JSONHandler::parseJSONArray(const string& str) {
    vector<string> result;
    string cleaned = str;

    // Remove brackets and quotes
    size_t start = cleaned.find('[');
    size_t end = cleaned.rfind(']');
    if (start != string::npos && end != string::npos) {
        cleaned = cleaned.substr(start + 1, end - start - 1);
    }

    stringstream ss(cleaned);
    string item;
    while (getline(ss, item, ',')) {
        // Remove quotes and whitespace
        item.erase(0, item.find_first_not_of(" \t\n\r\""));
        item.erase(item.find_last_not_of(" \t\n\r\"") + 1);
        if (!item.empty()) {
            result.push_back(item);
        }
    }

    return result;
}

vector<Lowongan> JSONHandler::loadFromJSON(const string& filename) {
    vector<Lowongan> data;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "[ERROR] Cannot open file: " << filename << endl;
        return data;
    }

    cout << "[INFO] Loading data from " << filename << "..." << endl;
    cout << "[WARNING] Simple JSON parser - format must be exact!" << endl;

    // Simple JSON parsing (untuk demonstrasi)
    // Dalam produksi, gunakan library seperti nlohmann/json

    string line;
    Lowongan current;
    bool inObject = false;
    bool inAlamat = false;
    bool inGaji = false;
    bool inRequirement = false;
    bool inBenefit = false;

    while (getline(file, line)) {
        // Remove whitespace
        line.erase(0, line.find_first_not_of(" \t\n\r"));
        line.erase(line.find_last_not_of(" \t\n\r,") + 1);

        if (line == "{") {
            inObject = true;
            current = Lowongan(); // Reset
        }
        else if (line == "}") {
            if (inObject && !inAlamat && !inGaji && !inRequirement && !inBenefit) {
                data.push_back(current);
                inObject = false;
            }
            inAlamat = false;
            inGaji = false;
            inRequirement = false;
            inBenefit = false;
        }
        else if (line.find("\"alamat\":") != string::npos) {
            inAlamat = true;
        }
        else if (line.find("\"gaji\":") != string::npos) {
            inGaji = true;
        }
        else if (line.find("\"requirement\":") != string::npos) {
            inRequirement = true;
        }
        else if (line.find("\"benefit\":") != string::npos) {
            inBenefit = true;
        }
        else if (line.find("\"id\":") != string::npos) {
            size_t pos = line.find(":");
            current.id = stoi(line.substr(pos + 1));
        }
        else if (line.find("\"posisi\":") != string::npos && !inRequirement) {
            size_t start = line.find(":") + 1;
            size_t first = line.find("\"", start);
            size_t last = line.rfind("\"");
            current.posisi = line.substr(first + 1, last - first - 1);
        }
        // ... (parsing lainnya - simplified untuk demo)
    }

    file.close();
    cout << "[SUCCESS] Loaded " << data.size() << " records from JSON" << endl;

    return data;
}