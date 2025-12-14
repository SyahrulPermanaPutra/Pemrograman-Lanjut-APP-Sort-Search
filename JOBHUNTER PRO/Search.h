#ifndef SEARCH_H
#define SEARCH_H

#include "database.h"
#include <vector>
#include <string>

// Search by Gaji
vector<int> blok_search_by_rentang_gaji(const vector<Lowongan>& arr, double target_gaji);
vector<int> search_by_gaji_range(const vector<Lowongan>& arr, double min_gaji, double max_gaji);

// Search by Posisi
vector<int> blok_search_by_posisi_partial(const vector<Lowongan>& arr, const string& target);
vector<string> get_semua_posisi_unik(const vector<Lowongan>& arr);
vector<int> cari_semua_lowongan_by_posisi(const vector<Lowongan>& arr, const string& target_posisi);

// Search by Perusahaan
vector<int> search_by_perusahaan(const vector<Lowongan>& arr, const string& keyword);
vector<string> get_semua_perusahaan_unik(const vector<Lowongan>& arr);

// Search by Lokasi
vector<int> search_by_kota(const vector<Lowongan>& arr, const string& kota);
vector<int> search_by_provinsi(const vector<Lowongan>& arr, const string& provinsi);
vector<string> get_semua_kota_unik(const vector<Lowongan>& arr);

// Search by Jenis Pekerjaan
vector<int> search_by_jenis_pekerjaan(const vector<Lowongan>& arr, const string& jenis);

// Search by Level
vector<int> search_by_level(const vector<Lowongan>& arr, const string& level);

// Search by Pengalaman
vector<int> search_by_pengalaman(const vector<Lowongan>& arr, int max_experience);

// Advanced Search - Multiple criteria
vector<int> advanced_search(const vector<Lowongan>& arr,
    const string& posisi_keyword = "",
    const string& kota = "",
    double min_gaji = 0.0,
    double max_gaji = 999.9,
    const string& jenis = "",
    const string& level = "");

#endif