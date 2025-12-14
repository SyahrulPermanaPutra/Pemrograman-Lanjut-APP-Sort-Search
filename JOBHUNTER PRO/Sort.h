#ifndef SORT_H
#define SORT_H

#include "database.h"

// Fungsi sort dengan parameter ascending/descending
void merge_sort_by_gaji(vector<Lowongan>& arr, int left, int right, bool ascending = true);
void merge_sort_by_pelamar(vector<Lowongan>& arr, int left, int right, bool ascending = true);
void merge_sort_by_tanggal(vector<Lowongan>& arr, int left, int right, bool ascending = true);
void quick_sort_by_posisi(vector<Lowongan>& arr, int low, int high, bool ascending = true);
void quick_sort_by_perusahaan(vector<Lowongan>& arr, int low, int high, bool ascending = true);
void quick_sort_by_kota(vector<Lowongan>& arr, int low, int high, bool ascending = true);

#endif