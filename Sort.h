#ifndef SORT_H
#define SORT_H

#include "database.h"

// Deklarasi fungsi sort
void merge_sort_by_gaji(vector<Lowongan>& arr, int left, int right, bool ascending = true);
void merge_sort_by_pelamar(vector<Lowongan>& arr, int left, int right, bool ascending = true);
void quick_sort_by_posisi(vector<Lowongan>& arr, int low, int high, bool ascending = true);

#endif