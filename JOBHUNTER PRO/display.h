#ifndef DISPLAY_H
#define DISPLAY_H

#include "database.h"

// Deklarasi fungsi display yang sudah ada
void tampilkan_lowongan(const Lowongan& l);
void tampilkan_semua_lowongan(const vector<Lowongan>& lowongan);
void tampilkan_lowongan_remote(const vector<Lowongan>& lowongan);
void header_aplikasi();
void clear_screen();

//  DEKLARASI FUNGSI BARU
void tampilkan_semua_posisi(const vector<Lowongan>& data);
void tampilkan_lowongan_by_posisi(const vector<Lowongan>& data, const string& posisi);
void tampilkan_hasil_search_posisi(const vector<Lowongan>& data, const string& keyword);

#endif