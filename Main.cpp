#include <iostream>
#include <vector>
#include "database.h"
#include "search.h"
#include "sort.h"
#include "display.h"

using namespace std;

void menu_utama() {
    vector<Lowongan> data = inisialisasi_data();
    int pilihan;

    do {
        header_aplikasi();
        cout << "1. Tampilkan Semua Lowongan" << endl;
        cout << "2. Cari Lowongan Berdasarkan Gaji" << endl;
        cout << "3. Cari Lowongan Berdasarkan Posisi" << endl;
        cout << "4. Urutkan Berdasarkan Gaji (Tertinggi)" << endl;
        cout << "5. Urutkan Berdasarkan Jumlah Pelamar" << endl;
        cout << "6. Tampilkan Lowongan Remote Work" << endl;
        cout << "7. Urutkan Berdasarkan Posisi (A-Z)" << endl;
        cout << "0. Keluar" << endl;
        cout << "=========================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: {
            header_aplikasi();
            tampilkan_semua_lowongan(data);
            break;
        }
        case 2: {
            header_aplikasi();
            double gaji_cari;
            cout << "Masukkan gaji yang diinginkan (dalam juta): ";
            cin >> gaji_cari;

            vector<int> hasil_indices = blok_search_by_rentang_gaji(data, gaji_cari);

            if (!hasil_indices.empty()) {
                cout << "\nDitemukan " << hasil_indices.size() << " lowongan dengan rentang gaji sekitar " << gaji_cari << " juta:" << endl;
                for (int idx : hasil_indices) {
                    tampilkan_lowongan(data[idx]);
                }
            }
            else {
                cout << "\nTidak ditemukan lowongan dengan rentang gaji sekitar " << gaji_cari << " juta." << endl;

            }
            break;
        }
        case 3: {
            header_aplikasi();
            int sub_pilihan;

            cout << "PENCARIAN BERDASARKAN POSISI\n" << endl;
            cout << "1. Cari dengan kata kunci" << endl;
            cout << "2. Lihat semua posisi yang tersedia" << endl;
            cout << "0. Kembali ke menu utama" << endl;
            cout << "=========================================" << endl;
            cout << "Pilihan Anda: ";
            cin >> sub_pilihan;

            switch (sub_pilihan) {
            case 1: {
                header_aplikasi();
                string keyword;
                cout << "Masukkan kata kunci posisi: ";
                cin.ignore();
                getline(cin, keyword);

                if (!keyword.empty()) {
                    tampilkan_hasil_search_posisi(data, keyword);
                }
                else {
                    cout << "Kata kunci tidak boleh kosong!" << endl;
                }
                break;
            }
            case 2: {
                header_aplikasi();
                tampilkan_semua_posisi(data);

                char pilih_langsung;
                cout << "Ingin melihat lowongan untuk posisi tertentu? (y/n): ";
                cin >> pilih_langsung;

                if (pilih_langsung == 'y' || pilih_langsung == 'Y') {
                    int nomor_posisi;
                    cout << "Masukkan nomor posisi: ";
                    cin >> nomor_posisi;

                    vector<string> posisi_list = get_semua_posisi_unik(data);
                    if (nomor_posisi >= 1 && nomor_posisi <= (int)posisi_list.size()) {
                        string posisi_terpilih = posisi_list[nomor_posisi - 1];
                        tampilkan_lowongan_by_posisi(data, posisi_terpilih);
                    }
                    else {
                        cout << "Nomor posisi tidak valid!" << endl;
                    }
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
            }
            break;
        }
        case 4: {
            header_aplikasi();
            vector<Lowongan> data_sort = data;
            merge_sort_by_gaji(data_sort, 0, data_sort.size() - 1, false);
            cout << "Lowongan diurutkan berdasarkan Gaji Tertinggi:" << endl;
            tampilkan_semua_lowongan(data_sort);
            break;
        }
        case 5: {
            header_aplikasi();
            vector<Lowongan> data_sort = data;
            merge_sort_by_pelamar(data_sort, 0, data_sort.size() - 1, false);
            cout << "Lowongan diurutkan berdasarkan Jumlah Pelamar Terbanyak:" << endl;
            tampilkan_semua_lowongan(data_sort);
            break;
        }
        case 6: {
            header_aplikasi();
            tampilkan_lowongan_remote(data);
            break;
        }
        case 7: {
            header_aplikasi();
            vector<Lowongan> data_sort = data;
            quick_sort_by_posisi(data_sort, 0, data_sort.size() - 1, true);
            cout << "Lowongan diurutkan berdasarkan Posisi (A-Z):" << endl;
            tampilkan_semua_lowongan(data_sort);
            break;
        }
        case 0: {
            cout << "Terima kasih telah menggunakan JobHunter Pro!" << endl;
            break;
        }
        default: {
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }

    } while (pilihan != 0);
}

int main() {
    menu_utama();
    return 0;
}