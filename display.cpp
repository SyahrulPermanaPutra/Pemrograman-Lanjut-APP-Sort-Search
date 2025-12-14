#include "display.h"
#include <iostream>
#include <iomanip>
#include "search.h"

using namespace std;

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void header_aplikasi() {
    clear_screen();
    cout << "=========================================" << endl;
    cout << "         JOBHUNTER PRO v1.0" << endl;
    cout << "=========================================" << endl;
}

void tampilkan_lowongan(const Lowongan& l) {
    cout << "=========================================" << endl;
    cout << "ID: " << l.id << " | " << l.posisi << " di " << l.perusahaan << endl;
    cout << "Lokasi: " << l.alamat.kota << ", " << l.alamat.provinsi;
    cout << " | " << l.jenis_pekerjaan << " | " << l.level << endl;
    cout << "Gaji: Rp " << fixed << setprecision(1) << l.gaji.minimal << " - "
        << l.gaji.maksimal << " juta (" << l.gaji.tipe << ")" << endl;
    cout << "Requirement: " << l.requirement.pendidikan_minimal << ", "
        << l.requirement.pengalaman_minimal << " tahun experience" << endl;
    cout << "Skills: ";
    for (size_t i = 0; i < l.requirement.skills_wajib.size(); i++) {
        cout << l.requirement.skills_wajib[i];
        if (i < l.requirement.skills_wajib.size() - 1) cout << ", ";
    }
    cout << endl;
    cout << "Pelamar: " << l.jumlah_pelamar << " orang";
    cout << " | Posted: " << l.tanggal_post << endl;
    cout << "Deskripsi: " << l.deskripsi_pekerjaan.substr(0, 100) << "..." << endl;
    cout << "=========================================" << endl << endl;
}

void tampilkan_semua_lowongan(const vector<Lowongan>& lowongan) {
    cout << "\nDAFTAR LOWONGAN KERJA (" << lowongan.size() << " positions)\n" << endl;
    for (const auto& l : lowongan) {
        if (l.status_aktif) {
            tampilkan_lowongan(l);
        }
    }
}

void tampilkan_lowongan_remote(const vector<Lowongan>& lowongan) {
    cout << "\nLOWONGAN REMOTE WORK:" << endl;
    int count = 0;
    for (const auto& l : lowongan) {
        if (l.jenis_pekerjaan == "Remote" && l.status_aktif) {
            tampilkan_lowongan(l);
            count++;
        }
    }
    if (count == 0) {
        cout << "Tidak ada lowongan remote work saat ini." << endl;
    }
}

// ==================== FUNGSI BARU TANPA UNICODE ====================

void tampilkan_semua_posisi(const vector<Lowongan>& data) {
    vector<string> posisi_list = get_semua_posisi_unik(data);

    cout << "\nDAFTAR POSISI YANG TERSEDIA:\n" << endl;
    cout << "=========================================" << endl;

    for (size_t i = 0; i < posisi_list.size(); i++) {
        cout << i + 1 << ". " << posisi_list[i] << endl;
    }

    cout << "=========================================" << endl;
    cout << "Total: " << posisi_list.size() << " posisi berbeda\n" << endl;
}

void tampilkan_lowongan_by_posisi(const vector<Lowongan>& data, const string& posisi) {
    vector<int> indices = cari_semua_lowongan_by_posisi(data, posisi);

    if (!indices.empty()) {
        cout << "\nDitemukan " << indices.size() << " lowongan untuk posisi '" << posisi << "':\n" << endl;
        for (int idx : indices) {
            tampilkan_lowongan(data[idx]);
        }
    }
    else {
        cout << "\nTidak ditemukan lowongan untuk posisi '" << posisi << "'." << endl;
    }
}

void tampilkan_hasil_search_posisi(const vector<Lowongan>& data, const string& keyword) {
    vector<int> hasil = blok_search_by_posisi_partial(data, keyword);

    if (!hasil.empty()) {
        cout << "\nDitemukan " << hasil.size() << " lowongan dengan kata kunci '" << keyword << "':\n" << endl;
        for (int idx : hasil) {
            tampilkan_lowongan(data[idx]);
        }
    }
    else {
        cout << "\nTidak ditemukan lowongan dengan kata kunci '" << keyword << "'." << endl;

        // Tampilkan suggestion
        vector<string> posisi_list = get_semua_posisi_unik(data);
        if (!posisi_list.empty()) {
            cout << "\nSuggestion: Coba salah satu posisi berikut:" << endl;
            for (size_t i = 0; i < min(posisi_list.size(), size_t(5)); i++) {
                cout << "  - " << posisi_list[i] << endl;
            }
        }
    }
}