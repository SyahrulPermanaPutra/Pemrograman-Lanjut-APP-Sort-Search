#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

using namespace std;

struct AlamatPerusahaan {
    string jalan = "";
    string kota = "";
    string provinsi = "";
    string kode_pos = "";
};

struct Gaji {
    double minimal = 0.0;
    double maksimal = 0.0;
    string tipe = "";
};

struct Requirement {
    int pengalaman_minimal = 0;  // ✅ DIINISIALISASI
    string pendidikan_minimal = "";
    vector<string> skills_wajib;
    vector<string> skills_plus;
    string bahasa = "";
};

struct Benefit {
    string asuransi_kesehatan = "";
    bool tunjangan_transport = false;  // ✅ DIINISIALISASI
    bool tunjangan_makan = false;      // ✅ DIINISIALISASI
    string program_pensiun = "";
    string pengembangan_karir = "";
    int cuti_tahunan = 0;             // ✅ DIINISIALISASI
};

struct Lowongan {
    int id = 0;                       // ✅ DIINISIALISASI
    string posisi = "";
    string perusahaan = "";
    string jenis_pekerjaan = "";
    string level = "";
    AlamatPerusahaan alamat;
    Gaji gaji;
    Requirement requirement;
    Benefit benefit;
    string deskripsi_pekerjaan = "";
    string tanggal_post = "";
    int jumlah_pelamar = 0;           // ✅ DIINISIALISASI
    bool status_aktif = false;        // ✅ DIINISIALISASI
};

// Deklarasi fungsi
vector<Lowongan> inisialisasi_data();
void tampilkan_data_lengkap(const Lowongan& l);

#endif