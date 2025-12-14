#include "sort.h"
#include <algorithm>

using namespace std;

void merge_sort_by_gaji(vector<Lowongan>& arr, int left, int right, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_by_gaji(arr, left, mid, ascending);
        merge_sort_by_gaji(arr, mid + 1, right, ascending);

        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Lowongan> L(n1), R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (ascending) {
                if (L[i].gaji.maksimal <= R[j].gaji.maksimal) {
                    arr[k] = L[i];
                    i++;
                }
                else {
                    arr[k] = R[j];
                    j++;
                }
            }
            else {
                if (L[i].gaji.maksimal >= R[j].gaji.maksimal) {
                    arr[k] = L[i];
                    i++;
                }
                else {
                    arr[k] = R[j];
                    j++;
                }
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

void merge_sort_by_pelamar(vector<Lowongan>& arr, int left, int right, bool ascending) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort_by_pelamar(arr, left, mid, ascending);
        merge_sort_by_pelamar(arr, mid + 1, right, ascending);

        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<Lowongan> L(n1), R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (ascending) {
                if (L[i].jumlah_pelamar <= R[j].jumlah_pelamar) {
                    arr[k] = L[i];
                    i++;
                }
                else {
                    arr[k] = R[j];
                    j++;
                }
            }
            else {
                if (L[i].jumlah_pelamar >= R[j].jumlah_pelamar) {
                    arr[k] = L[i];
                    i++;
                }
                else {
                    arr[k] = R[j];
                    j++;
                }
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

// Quick Sort partition function
int partition_by_posisi(vector<Lowongan>& arr, int low, int high, bool ascending) {
    string pivot = arr[high].posisi;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (ascending) {
            if (arr[j].posisi <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        else {
            if (arr[j].posisi >= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
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