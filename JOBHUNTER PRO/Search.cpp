#include "search.h"
#include <vector>
#include <algorithm>
#include <cctype> 
#include <string>

using namespace std;

// Helper: Manual square root
static double sqrt_manual(double x) {
    if (x < 0) return -1;
    if (x == 0 || x == 1) return x;

    double precision = 0.00001;
    double start = 0, end = x;
    if (x < 1) end = 1;

    double ans = 0;
    while (end - start > precision) {
        double mid = (start + end) / 2;
        double square = mid * mid;

        if (square == x) return mid;
        else if (square < x) {
            start = mid;
            ans = mid;
        }
        else {
            end = mid;
        }
    }
    return ans;
}

// Helper: Convert to lowercase
static string to_lower(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

// ==================== SEARCH BY GAJI ====================

vector<int> blok_search_by_rentang_gaji(const vector<Lowongan>& arr, double target_gaji) {
    vector<int> hasil;
    int n = static_cast<int>(arr.size());  // Konversi ke int

    if (n == 0) return hasil;

    int step = static_cast<int>(sqrt_manual(n));
    int prev = 0;

    while (prev < n) {
        int current_end = min(prev + step, n);

        for (int i = prev; i < current_end; i++) {
            if (target_gaji >= arr[i].gaji.minimal && target_gaji <= arr[i].gaji.maksimal) {
                hasil.push_back(i);
            }
        }

        prev = current_end;
    }

    return hasil;
}

vector<int> search_by_gaji_range(const vector<Lowongan>& arr, double min_gaji, double max_gaji) {
    vector<int> hasil;

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        if (arr[i].gaji.minimal >= min_gaji && arr[i].gaji.maksimal <= max_gaji && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

// ==================== SEARCH BY POSISI ====================

vector<int> blok_search_by_posisi_partial(const vector<Lowongan>& arr, const string& target) {
    vector<int> hasil;
    int n = static_cast<int>(arr.size());  // Konversi ke int

    if (n == 0) return hasil;

    string target_lower = to_lower(target);
    int step = static_cast<int>(sqrt_manual(n));
    int prev = 0;

    while (prev < n) {
        int current_end = min(prev + step, n);

        for (int i = prev; i < current_end; i++) {
            string posisi_lower = to_lower(arr[i].posisi);

            if (posisi_lower.find(target_lower) != string::npos && arr[i].status_aktif) {
                hasil.push_back(i);
            }
        }

        prev = current_end;
    }

    return hasil;
}

vector<string> get_semua_posisi_unik(const vector<Lowongan>& arr) {
    vector<string> posisi_list;

    for (const auto& lowongan : arr) {
        bool sudah_ada = false;
        for (const auto& posisi : posisi_list) {
            if (posisi == lowongan.posisi) {
                sudah_ada = true;
                break;
            }
        }

        if (!sudah_ada && lowongan.status_aktif) {
            posisi_list.push_back(lowongan.posisi);
        }
    }

    return posisi_list;
}

vector<int> cari_semua_lowongan_by_posisi(const vector<Lowongan>& arr, const string& target_posisi) {
    vector<int> hasil;

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        if (arr[i].posisi == target_posisi && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

// ==================== SEARCH BY PERUSAHAAN ====================

vector<int> search_by_perusahaan(const vector<Lowongan>& arr, const string& keyword) {
    vector<int> hasil;
    string keyword_lower = to_lower(keyword);

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        string perusahaan_lower = to_lower(arr[i].perusahaan);
        if (perusahaan_lower.find(keyword_lower) != string::npos && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

vector<string> get_semua_perusahaan_unik(const vector<Lowongan>& arr) {
    vector<string> perusahaan_list;

    for (const auto& lowongan : arr) {
        bool sudah_ada = false;
        for (const auto& perusahaan : perusahaan_list) {
            if (perusahaan == lowongan.perusahaan) {
                sudah_ada = true;
                break;
            }
        }

        if (!sudah_ada && lowongan.status_aktif) {
            perusahaan_list.push_back(lowongan.perusahaan);
        }
    }

    return perusahaan_list;
}

// ==================== SEARCH BY LOKASI ====================

vector<int> search_by_kota(const vector<Lowongan>& arr, const string& kota) {
    vector<int> hasil;
    string kota_lower = to_lower(kota);

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        string kota_arr_lower = to_lower(arr[i].alamat.kota);
        if (kota_arr_lower.find(kota_lower) != string::npos && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

vector<int> search_by_provinsi(const vector<Lowongan>& arr, const string& provinsi) {
    vector<int> hasil;
    string provinsi_lower = to_lower(provinsi);

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        string provinsi_arr_lower = to_lower(arr[i].alamat.provinsi);
        if (provinsi_arr_lower.find(provinsi_lower) != string::npos && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

vector<string> get_semua_kota_unik(const vector<Lowongan>& arr) {
    vector<string> kota_list;

    for (const auto& lowongan : arr) {
        bool sudah_ada = false;
        for (const auto& kota : kota_list) {
            if (kota == lowongan.alamat.kota) {
                sudah_ada = true;
                break;
            }
        }

        if (!sudah_ada && lowongan.status_aktif) {
            kota_list.push_back(lowongan.alamat.kota);
        }
    }

    return kota_list;
}

// ==================== SEARCH BY JENIS PEKERJAAN ====================

vector<int> search_by_jenis_pekerjaan(const vector<Lowongan>& arr, const string& jenis) {
    vector<int> hasil;
    string jenis_lower = to_lower(jenis);

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        string jenis_arr_lower = to_lower(arr[i].jenis_pekerjaan);
        if (jenis_arr_lower == jenis_lower && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

// ==================== SEARCH BY LEVEL ====================

vector<int> search_by_level(const vector<Lowongan>& arr, const string& level) {
    vector<int> hasil;
    string level_lower = to_lower(level);

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        string level_arr_lower = to_lower(arr[i].level);
        if (level_arr_lower == level_lower && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

// ==================== SEARCH BY PENGALAMAN ====================

vector<int> search_by_pengalaman(const vector<Lowongan>& arr, int max_experience) {
    vector<int> hasil;

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        if (arr[i].requirement.pengalaman_minimal <= max_experience && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

// ==================== ADVANCED SEARCH ====================

vector<int> advanced_search(const vector<Lowongan>& arr,
    const string& posisi_keyword,
    const string& kota,
    double min_gaji,
    double max_gaji,
    const string& jenis,
    const string& level) {
    vector<int> hasil;

    string posisi_lower = to_lower(posisi_keyword);
    string kota_lower = to_lower(kota);
    string jenis_lower = to_lower(jenis);
    string level_lower = to_lower(level);

    for (int i = 0; i < static_cast<int>(arr.size()); i++) {  // Konversi ke int
        if (!arr[i].status_aktif) continue;

        bool match = true;

        // Check posisi
        if (!posisi_keyword.empty()) {
            string arr_posisi_lower = to_lower(arr[i].posisi);
            if (arr_posisi_lower.find(posisi_lower) == string::npos) {
                match = false;
            }
        }

        // Check kota
        if (!kota.empty() && match) {
            string arr_kota_lower = to_lower(arr[i].alamat.kota);
            if (arr_kota_lower.find(kota_lower) == string::npos) {
                match = false;
            }
        }

        // Check gaji
        if (match && min_gaji > 0) {
            if (arr[i].gaji.maksimal < min_gaji || arr[i].gaji.minimal > max_gaji) {
                match = false;
            }
        }

        // Check jenis pekerjaan
        if (!jenis.empty() && match) {
            string arr_jenis_lower = to_lower(arr[i].jenis_pekerjaan);
            if (arr_jenis_lower != jenis_lower) {
                match = false;
            }
        }

        // Check level
        if (!level.empty() && match) {
            string arr_level_lower = to_lower(arr[i].level);
            if (arr_level_lower != level_lower) {
                match = false;
            }
        }

        if (match) {
            hasil.push_back(i);
        }
    }

    return hasil;
}