#include "sort.h"
#include <algorithm>

using namespace std;

// ==================== MERGE SORT BY GAJI ====================
void merge_sort_by_gaji(vector<Lowongan>& arr, int left, int right, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_by_gaji(arr, left, mid, ascending);
        merge_sort_by_gaji(arr, mid + 1, right, ascending);

        // Konversi ke size_t untuk perhitungan yang aman
        size_t n1 = static_cast<size_t>(mid - left + 1);
        size_t n2 = static_cast<size_t>(right - mid);

        vector<Lowongan> L(n1), R(n2);

        for (size_t i = 0; i < n1; i++)
            L[i] = arr[left + static_cast<int>(i)];
        for (size_t j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + static_cast<int>(j)];

        size_t i = 0, j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            bool condition = ascending ?
                (L[i].gaji.maksimal <= R[j].gaji.maksimal) :
                (L[i].gaji.maksimal >= R[j].gaji.maksimal);

            if (condition) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
}

// ==================== MERGE SORT BY PELAMAR ====================
void merge_sort_by_pelamar(vector<Lowongan>& arr, int left, int right, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_by_pelamar(arr, left, mid, ascending);
        merge_sort_by_pelamar(arr, mid + 1, right, ascending);

        size_t n1 = static_cast<size_t>(mid - left + 1);
        size_t n2 = static_cast<size_t>(right - mid);

        vector<Lowongan> L(n1), R(n2);

        for (size_t i = 0; i < n1; i++)
            L[i] = arr[left + static_cast<int>(i)];
        for (size_t j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + static_cast<int>(j)];

        size_t i = 0, j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            bool condition = ascending ?
                (L[i].jumlah_pelamar <= R[j].jumlah_pelamar) :
                (L[i].jumlah_pelamar >= R[j].jumlah_pelamar);

            if (condition) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
}

// ==================== MERGE SORT BY TANGGAL ====================
void merge_sort_by_tanggal(vector<Lowongan>& arr, int left, int right, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_by_tanggal(arr, left, mid, ascending);
        merge_sort_by_tanggal(arr, mid + 1, right, ascending);

        size_t n1 = static_cast<size_t>(mid - left + 1);
        size_t n2 = static_cast<size_t>(right - mid);

        vector<Lowongan> L(n1), R(n2);

        for (size_t i = 0; i < n1; i++)
            L[i] = arr[left + static_cast<int>(i)];
        for (size_t j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + static_cast<int>(j)];

        size_t i = 0, j = 0;
        int k = left;

        while (i < n1 && j < n2) {
            bool condition = ascending ?
                (L[i].tanggal_post <= R[j].tanggal_post) :
                (L[i].tanggal_post >= R[j].tanggal_post);

            if (condition) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
}

// ==================== QUICK SORT BY POSISI ====================
int partition_by_posisi(vector<Lowongan>& arr, int low, int high, bool ascending) {
    string pivot = arr[high].posisi;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        bool condition = ascending ?
            (arr[j].posisi <= pivot) :
            (arr[j].posisi >= pivot);

        if (condition) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort_by_posisi(vector<Lowongan>& arr, int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition_by_posisi(arr, low, high, ascending);
        quick_sort_by_posisi(arr, low, pi - 1, ascending);
        quick_sort_by_posisi(arr, pi + 1, high, ascending);
    }
}

// ==================== QUICK SORT BY PERUSAHAAN ====================
int partition_by_perusahaan(vector<Lowongan>& arr, int low, int high, bool ascending) {
    string pivot = arr[high].perusahaan;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        bool condition = ascending ?
            (arr[j].perusahaan <= pivot) :
            (arr[j].perusahaan >= pivot);

        if (condition) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort_by_perusahaan(vector<Lowongan>& arr, int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition_by_perusahaan(arr, low, high, ascending);
        quick_sort_by_perusahaan(arr, low, pi - 1, ascending);
        quick_sort_by_perusahaan(arr, pi + 1, high, ascending);
    }
}

// ==================== QUICK SORT BY KOTA ====================
int partition_by_kota(vector<Lowongan>& arr, int low, int high, bool ascending) {
    string pivot = arr[high].alamat.kota;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        bool condition = ascending ?
            (arr[j].alamat.kota <= pivot) :
            (arr[j].alamat.kota >= pivot);

        if (condition) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort_by_kota(vector<Lowongan>& arr, int low, int high, bool ascending) {
    if (low < high) {
        int pi = partition_by_kota(arr, low, high, ascending);
        quick_sort_by_kota(arr, low, pi - 1, ascending);
        quick_sort_by_kota(arr, pi + 1, high, ascending);
    }
}