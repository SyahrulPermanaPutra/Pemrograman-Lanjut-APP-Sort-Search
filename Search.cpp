#include "search.h"
#include <vector>
#include <algorithm>
#include <cctype> // untuk tolower()
#include <string>

using namespace std;

// Implementasi manual square root
double sqrt_manual(double x) {
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

// ==================== FUNGSI SEARCH RENTANG GAJI ====================

vector<int> blok_search_by_rentang_gaji(const vector<Lowongan>& arr, double target_gaji) {
    vector<int> hasil;
    int n = (int)arr.size();

    if (n == 0) return hasil;

    int step = (int)sqrt_manual(n);
    int prev = 0;

    while (prev < n) {
        int current_end = min(prev + step, n);

        for (int i = prev; i < current_end; i++) {
            if (target_gaji >= arr[i].gaji.minimal && target_gaji <= arr[i].gaji.maksimal) {
                hasil.push_back(i);
            }
        }

        prev = current_end;

        if (prev < n && arr[prev].gaji.minimal > target_gaji) {
            break;
        }
    }

    return hasil;
}

// ==================== FUNGSI SEARCH POSISI ====================

vector<int> blok_search_by_posisi_partial(const vector<Lowongan>& arr, const string& target) {
    vector<int> hasil;
    int n = (int)arr.size();

    if (n == 0) return hasil;

    string target_lower = target;
    for (char& c : target_lower) {
        c = tolower(c);
    }

    int step = (int)sqrt_manual(n);
    int prev = 0;

    while (prev < n) {
        int current_end = min(prev + step, n);

        for (int i = prev; i < current_end; i++) {
            string posisi_lower = arr[i].posisi;
            for (char& c : posisi_lower) {
                c = tolower(c);
            }

            if (posisi_lower.find(target_lower) != string::npos) {
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

    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i].posisi == target_posisi && arr[i].status_aktif) {
            hasil.push_back(i);
        }
    }

    return hasil;
}

