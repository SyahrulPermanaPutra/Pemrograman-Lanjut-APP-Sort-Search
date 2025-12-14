#ifndef SEARCH_H
#define SEARCH_H

#include "database.h"
#include <vector>
#include <string>

// Deklarasi fungsi search yang sudah ada
int blok_search_by_posisi(const vector<Lowongan>& arr, const string& target);
int fibonacci_search_by_gaji(const vector<Lowongan>& arr, double target);
vector<int> blok_search_by_rentang_gaji(const vector<Lowongan>& arr, double target_gaji);

// ✅ DEKLARASI FUNGSI BARU
vector<int> blok_search_by_posisi_partial(const vector<Lowongan>& arr, const string& target);
vector<string> get_semua_posisi_unik(const vector<Lowongan>& arr);
vector<int> cari_semua_lowongan_by_posisi(const vector<Lowongan>& arr, const string& target_posisi);

#endif