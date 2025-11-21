#include "database.h"
#include <iostream>
#include <iomanip>

using namespace std;

vector<Lowongan> inisialisasi_data() {
    vector<Lowongan> data;

    // Lowongan 1
    Lowongan l1;
    l1.id = 1;
    l1.posisi = "Software Engineer";
    l1.perusahaan = "TechInnovation Indonesia";
    l1.jenis_pekerjaan = "Full-time";
    l1.level = "Middle";
    l1.alamat = { "Jl. Sudirman No. 123", "Jakarta", "DKI Jakarta", "12190" };
    l1.gaji = { 18.5, 25.0, "Per bulan" };
    l1.requirement = { 2, "S1", {"C++", "Python", "SQL"}, {"Docker", "AWS"}, "English Intermediate" };
    l1.benefit = { "BPJS Kesehatan + Swasta", true, true, "BPJS Ketengakerjaan", "Training Budget $1000/tahun", 14 };
    l1.deskripsi_pekerjaan = "Mengembangkan aplikasi backend menggunakan C++ dan Python. Bertanggung jawab pada optimasi performa sistem.";
    l1.tanggal_post = "2025-11-01";
    l1.jumlah_pelamar = 45;
    l1.status_aktif = true;
    data.push_back(l1);

    // Lowongan 2
    Lowongan l2;
    l2.id = 2;
    l2.posisi = "Data Scientist";
    l2.perusahaan = "DataDriven Solutions";
    l2.jenis_pekerjaan = "Remote";
    l2.level = "Senior";
    l2.alamat = { "Jl. Thamrin No. 456", "Jakarta", "DKI Jakarta", "10230" };
    l2.gaji = { 25.0, 35.0, "Per bulan" };
    l2.requirement = { 4, "S2", {"Python", "R", "Machine Learning", "SQL"}, {"TensorFlow", "PyTorch", "Big Data"}, "English Fluent" };
    l2.benefit = { "Asuransi Comprehensive", true, false, "Company Pension", "Conference Budget $3000/tahun", 18 };
    l2.deskripsi_pekerjaan = "Membangun model machine learning untuk predictive analytics. Memimpin tim data analysis.";
    l2.tanggal_post = "2025-11-05";
    l2.jumlah_pelamar = 23;
    l2.status_aktif = true;
    data.push_back(l2);

    // Lowongan 3
    Lowongan l3;
    l3.id = 3;
    l3.posisi = "UX Designer";
    l3.perusahaan = "CreativeHub Studio";
    l3.jenis_pekerjaan = "Hybrid";
    l3.level = "Junior";
    l3.alamat = { "Jl. Asia Afrika No. 789", "Bandung", "Jawa Barat", "40115" };
    l3.gaji = { 12.0, 16.5, "Per bulan" };
    l3.requirement = { 1, "D3/S1", {"Figma", "User Research", "Wireframing"}, {"Adobe Creative Suite", "Prototyping"}, "English Basic" };
    l3.benefit = { "BPJS Kesehatan", true, true, "BPJS Ketengakerjaan", "Design Workshop", 12 };
    l3.deskripsi_pekerjaan = "Mendesain user interface untuk aplikasi mobile dan web. Melakukan user research dan testing.";
    l3.tanggal_post = "2025-10-28";
    l3.jumlah_pelamar = 67;
    l3.status_aktif = true;
    data.push_back(l3);

    // Lowongan 4
    Lowongan l4;
    l4.id = 4;
    l4.posisi = "Network Security Specialist";
    l4.perusahaan = "SecureNet Systems";
    l4.jenis_pekerjaan = "Full-time";
    l4.level = "Senior";
    l4.alamat = { "Jl. Gatot Subroto No. 321", "Jakarta", "DKI Jakarta", "12950" };
    l4.gaji = { 28.0, 40.0, "Per bulan" };
    l4.requirement = { 5, "S1", {"Cisco", "Firewall", "Security Audit", "Linux"}, {"CISSP", "CEH Certification", "Python"}, "English Advanced" };
    l4.benefit = { "Asuransi Keluarga", true, true, "Enhanced Pension", "Certification Reimbursement", 20 };
    l4.deskripsi_pekerjaan = "Mengamankan infrastruktur jaringan perusahaan. Melakukan penetration testing dan security audit.";
    l4.tanggal_post = "2025-11-07";
    l4.jumlah_pelamar = 18;
    l4.status_aktif = true;
    data.push_back(l4);

    // Lowongan 5
    Lowongan l5;
    l5.id = 5;
    l5.posisi = "Digital Marketing Manager";
    l5.perusahaan = "E-Commerce Giant";
    l5.jenis_pekerjaan = "Full-time";
    l5.level = "Lead";
    l5.alamat = { "Jl. Pemuda No. 654", "Surabaya", "Jawa Timur", "60272" };
    l5.gaji = { 30.0, 45.0, "Per bulan" };
    l5.requirement = { 6, "S1", {"SEO", "Google Analytics", "Social Media", "Content Strategy"}, {"Team Management", "Budget Planning"}, "English Fluent" };
    l5.benefit = { "Executive Health Insurance", true, true, "Manager Pension Plan", "Leadership Training", 22 };
    l5.deskripsi_pekerjaan = "Memimpin tim digital marketing. Mengelola budget iklan dan strategy campaign untuk multiple channels.";
    l5.tanggal_post = "2025-11-03";
    l5.jumlah_pelamar = 34;
    l5.status_aktif = true;
    data.push_back(l5);

    // Lowongan 6
    Lowongan l6;
    l6.id = 6;
    l6.posisi = "DevOps Engineer";
    l6.perusahaan = "CloudNative Tech";
    l6.jenis_pekerjaan = "Remote";
    l6.level = "Middle";
    l6.alamat = { "Jl. Hayam Wuruk No. 222", "Jakarta", "DKI Jakarta", "10150" };
    l6.gaji = { 20.0, 28.0, "Per bulan" };
    l6.requirement = { 3, "S1", {"Docker", "Kubernetes", "AWS", "CI/CD"}, {"Terraform", "Python", "Monitoring"}, "English Intermediate" };
    l6.benefit = { "BPJS + Swasta", true, false, "BPJS Ketengakerjaan", "Cloud Certification", 16 };
    l6.deskripsi_pekerjaan = "Mengelola infrastructure as code. Membangun dan maintain CI/CD pipeline untuk microservices.";
    l6.tanggal_post = "2025-10-30";
    l6.jumlah_pelamar = 52;
    l6.status_aktif = true;
    data.push_back(l6);

    // Lowongan 7
    Lowongan l7;
    l7.id = 7;
    l7.posisi = "Product Manager";
    l7.perusahaan = "FinTech Startup";
    l7.jenis_pekerjaan = "Full-time";
    l7.level = "Senior";
    l7.alamat = { "Jl. Rasuna Said No. 888", "Jakarta", "DKI Jakarta", "12960" };
    l7.gaji = { 35.0, 50.0, "Per bulan" };
    l7.requirement = { 5, "S1", {"Product Strategy", "Market Research", "Agile", "Data Analysis"}, {"Fintech Experience", "Leadership"}, "English Fluent" };
    l7.benefit = { "Comprehensive Insurance", true, true, "Equity Options", "Executive Education", 25 };
    l7.deskripsi_pekerjaan = "Mengelola product lifecycle dari ideation sampai launch. Bekerja dengan cross-functional teams.";
    l7.tanggal_post = "2025-11-06";
    l7.jumlah_pelamar = 28;
    l7.status_aktif = true;
    data.push_back(l7);

    // Lowongan 8
    Lowongan l8;
    l8.id = 8;
    l8.posisi = "Mobile Developer";
    l8.perusahaan = "AppWorks Studio";
    l8.jenis_pekerjaan = "Hybrid";
    l8.level = "Junior";
    l8.alamat = { "Jl. Cihampelas No. 111", "Bandung", "Jawa Barat", "40131" };
    l8.gaji = { 13.0, 17.0, "Per bulan" };
    l8.requirement = { 1, "D3/S1", {"Flutter", "Dart", "REST API"}, {"Firebase", "iOS/Android Native"}, "English Basic" };
    l8.benefit = { "BPJS Kesehatan", true, true, "BPJS Ketengakerjaan", "Tech Training", 12 };
    l8.deskripsi_pekerjaan = "Mengembangkan aplikasi mobile cross-platform menggunakan Flutter. Maintenance dan update existing apps.";
    l8.tanggal_post = "2025-11-02";
    l8.jumlah_pelamar = 89;
    l8.status_aktif = true;
    data.push_back(l8);

    // Lowongan 9
    Lowongan l9;
    l9.id = 9;
    l9.posisi = "Database Administrator";
    l9.perusahaan = "Bank Mega Data";
    l9.jenis_pekerjaan = "Full-time";
    l9.level = "Senior";
    l9.alamat = { "Jl. Jenderal Sudirman No. 555", "Jakarta", "DKI Jakarta", "12190" };
    l9.gaji = { 22.0, 32.0, "Per bulan" };
    l9.requirement = { 4, "S1", {"Oracle", "SQL Server", "Performance Tuning", "Backup Recovery"}, {"NoSQL", "Python Scripting"}, "English Intermediate" };
    l9.benefit = { "Family Insurance", true, true, "Bank Pension Plan", "Oracle Certification", 18 };
    l9.deskripsi_pekerjaan = "Manage dan optimize database systems. Ensure high availability dan performance untuk critical systems.";
    l9.tanggal_post = "2025-10-25";
    l9.jumlah_pelamar = 31;
    l9.status_aktif = true;
    data.push_back(l9);

    // Lowongan 10
    Lowongan l10;
    l10.id = 10;
    l10.posisi = "AI Research Scientist";
    l10.perusahaan = "AI Research Lab";
    l10.jenis_pekerjaan = "Full-time";
    l10.level = "Lead";
    l10.alamat = { "Jl. Science Park No. 777", "Tangerang", "Banten", "15345" };
    l10.gaji = { 40.0, 65.0, "Per bulan" };
    l10.requirement = { 7, "S3", {"Deep Learning", "Research Methodology", "Python", "Publications"}, {"PhD", "TensorFlow/PyTorch", "Mathematics"}, "English Fluent" };
    l10.benefit = { "Premium Insurance", true, true, "Research Grant", "International Conference", 30 };
    l10.deskripsi_pekerjaan = "Melakukan research di bidang AI/ML. Publish papers dan develop innovative AI solutions.";
    l10.tanggal_post = "2025-11-04";
    l10.jumlah_pelamar = 12;
    l10.status_aktif = true;
    data.push_back(l10);

    return data;
}

void tampilkan_data_lengkap(const Lowongan& l) {
    cout << "===========================================================" << endl;
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
    cout << "===========================================================" << endl << endl;
}