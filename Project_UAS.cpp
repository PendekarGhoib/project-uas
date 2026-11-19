#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// ==========================================
// 1. STRUCT DAN ENUM
// ==========================================

struct Deadline {
    int hari;
    int bulan;
    int tahun;
};

struct HariSekarang {
    int hari;
    int bulan;
    int tahun;
};

enum Status {
    BELUM_DIKERJAKAN,
    SEDANG_DIKERJAKAN,
    SELESAI
};

struct Tugas {
    string mataKuliah;
    string nama;
    Deadline batasWaktu;
    Status status;
};

// Array Dinamis
vector<Tugas> daftarTugas;


// ==========================================
// 2. FUNCTION INPUT
// ==========================================

int inputAngka(string pesan) {
    int angka;
    string input;

    while (true) {
        cout << pesan;
        getline(cin, input);

        try {
            size_t posisi;
            angka = stoi(input, &posisi);

            if (posisi == input.length()) {
                return angka;
            }
        } catch (...) {
        }

        cout << "Input harus berupa angka!\n";
    }
}

string inputTeks(string pesan) {
    string teks;

    do {
        cout << pesan;
        getline(cin, teks);

        if (teks.empty()) {
            cout << "Input tidak boleh kosong!\n";
        }

    } while (teks.empty());

    return teks;
}


// ==========================================
// 3. PERHITUNGAN DAN VALIDASI TANGGAL
// ==========================================

bool tahunKabisat(int tahun) {
    return (tahun % 400 == 0 ||
           (tahun % 4 == 0 && tahun % 100 != 0));
}

int jumlahHariBulan(int bulan, int tahun) {
    int jumlah[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (bulan == 2 && tahunKabisat(tahun)) {
        return 29;
    }

    return jumlah[bulan - 1];
}

bool validasiTanggal(Deadline tanggal) {

    if (tanggal.tahun < 1 || tanggal.tahun > 9999)
        return false;

    if (tanggal.bulan < 1 || tanggal.bulan > 12)
        return false;

    if (tanggal.hari < 1 ||
        tanggal.hari > jumlahHariBulan(
            tanggal.bulan, tanggal.tahun))
        return false;

    return true;
}

Deadline inputTanggal(string judul) {
    Deadline tanggal;

    while (true) {
        cout << "\n" << judul << endl;

        tanggal.hari = inputAngka("Hari  : ");
        tanggal.bulan = inputAngka("Bulan : ");
        tanggal.tahun = inputAngka("Tahun : ");

        if (validasiTanggal(tanggal)) {
            return tanggal;
        }

        cout << "Tanggal tidak valid! Silakan masukkan ulang.\n";
    }
}

// Mengubah tanggal menjadi jumlah hari kalender
// agar bisa dibandingkan secara akurat.

long long hitungHariTotal(Deadline tanggal) {

    long long tahun = tanggal.tahun - 1;

    long long total = tahun * 365
                    + tahun / 4
                    - tahun / 100
                    + tahun / 400;

    for (int i = 1; i < tanggal.bulan; i++) {
        total += jumlahHariBulan(i, tanggal.tahun);
    }

    total += tanggal.hari;

    return total;
}

long long selisihHari(Deadline tanggal1,
                      Deadline tanggal2) {

    return hitungHariTotal(tanggal1)
         - hitungHariTotal(tanggal2);
}

void tampilkanTanggal(Deadline tanggal) {
    cout << setfill('0')
         << setw(2) << tanggal.hari << "/"
         << setw(2) << tanggal.bulan << "/"
         << setw(4) << tanggal.tahun
         << setfill(' ');
}


// ==========================================
// 4. STATUS TUGAS
// ==========================================

string namaStatus(Status status) {

    switch (status) {

        case BELUM_DIKERJAKAN:
            return "Belum Dikerjakan";

        case SEDANG_DIKERJAKAN:
            return "Sedang Dikerjakan";

        case SELESAI:
            return "Selesai";

        default:
            return "Tidak Diketahui";
    }
}


// ==========================================
// 5. MENAMBAH TUGAS
// ==========================================

void tambahTugas() {

    Tugas tugasBaru;

    cout << "\n========== TAMBAH TUGAS ==========\n";

    tugasBaru.mataKuliah =
        inputTeks("Nama Mata Kuliah : ");

    tugasBaru.nama =
        inputTeks("Nama Tugas       : ");

    tugasBaru.batasWaktu =
        inputTanggal("Masukkan Deadline");

    tugasBaru.status = BELUM_DIKERJAKAN;

    // Menambahkan data tanpa menghapus tugas sebelumnya
    daftarTugas.push_back(tugasBaru);

    cout << "\nTugas berhasil ditambahkan!\n";
}


// ==========================================
// 6. MENAMPILKAN DAFTAR TUGAS
// ==========================================

void tampilkanTugas() {

    cout << "\n========== DAFTAR SEMUA TUGAS ==========\n";

    if (daftarTugas.empty()) {
        cout << "Belum ada tugas yang dicatat.\n";
        return;
    }

    for (size_t i = 0; i < daftarTugas.size(); i++) {

        cout << "\nTugas ke-" << i + 1 << endl;

        cout << "Mata Kuliah : "
             << daftarTugas[i].mataKuliah << endl;

        cout << "Nama Tugas  : "
             << daftarTugas[i].nama << endl;

        cout << "Deadline    : ";

        tampilkanTanggal(daftarTugas[i].batasWaktu);

        cout << "\nStatus      : "
             << namaStatus(daftarTugas[i].status) << endl;

        cout << "--------------------------------------\n";
    }
}


// ==========================================
// 7. BUBBLE SORT DEADLINE
// ==========================================

void urutkanDeadline() {

    for (size_t i = 0; i + 1 < daftarTugas.size(); i++) {

        for (size_t j = 0;
             j + 1 < daftarTugas.size() - i; j++) {

            long long tanggal1 =
                hitungHariTotal(daftarTugas[j].batasWaktu);

            long long tanggal2 =
                hitungHariTotal(daftarTugas[j + 1].batasWaktu);

            if (tanggal1 > tanggal2) {

                Tugas sementara = daftarTugas[j];

                daftarTugas[j] = daftarTugas[j + 1];

                daftarTugas[j + 1] = sementara;
            }
        }
    }
}

void tampilkanPrioritas(Deadline hariIni) {

    if (daftarTugas.empty()) {
        cout << "\nBelum ada tugas yang dicatat!\n";
        return;
    }

    urutkanDeadline();

    cout << "\n========== PRIORITAS TUGAS ==========\n";

    bool adaTugasAktif = false;

    for (size_t i = 0; i < daftarTugas.size(); i++) {

        if (daftarTugas[i].status == SELESAI) {
            continue;
        }

        adaTugasAktif = true;

        long long sisaHari =
            selisihHari(daftarTugas[i].batasWaktu, hariIni);

        cout << "\n" << daftarTugas[i].nama << endl;

        cout << "Mata Kuliah : "
             << daftarTugas[i].mataKuliah << endl;

        cout << "Deadline    : ";

        tampilkanTanggal(daftarTugas[i].batasWaktu);

        cout << endl;

        if (sisaHari < 0) {
            cout << "Prioritas   : OVERDUE (Terlambat)\n";
        }
        else if (sisaHari == 0) {
            cout << "Prioritas   : CRITICAL (Hari Ini!)\n";
        }
        else if (sisaHari <= 2) {
            cout << "Prioritas   : URGENT\n";
            cout << "Sisa waktu  : " << sisaHari << " hari\n";
        }
        else if (sisaHari <= 5) {
            cout << "Prioritas   : MEDIUM\n";
            cout << "Sisa waktu  : " << sisaHari << " hari\n";
        }
        else {
            cout << "Prioritas   : UPCOMING\n";
            cout << "Sisa waktu  : " << sisaHari << " hari\n";
        }

        cout << "--------------------------------------\n";
    }

    if (!adaTugasAktif) {
        cout << "Semua tugas sudah selesai!\n";
    }
}


// ==========================================
// 8. DEADLINE REMINDER
// ==========================================

void deadlineReminder(Deadline hariIni) {

    cout << "\n========== DEADLINE REMINDER ==========\n";

    if (daftarTugas.empty()) {
        cout << "Belum ada tugas yang dicatat.\n";
        return;
    }

    bool ditemukan = false;

    for (size_t i = 0; i < daftarTugas.size(); i++) {

        if (daftarTugas[i].status == SELESAI) {
            continue;
        }

        long long sisaHari =
            selisihHari(daftarTugas[i].batasWaktu, hariIni);

        if (sisaHari <= 2) {

            ditemukan = true;

            cout << "\nPERINGATAN!\n";

            cout << "Tugas      : "
                 << daftarTugas[i].nama << endl;

            cout << "Mata Kuliah: "
                 << daftarTugas[i].mataKuliah << endl;

            if (sisaHari < 0) {
                cout << "Status     : SUDAH TERLAMBAT!\n";
            }
            else if (sisaHari == 0) {
                cout << "Status     : DEADLINE HARI INI!\n";
            }
            else {
                cout << "Status     : DEADLINE "
                     << sisaHari << " HARI LAGI!\n";
            }
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada deadline yang mendesak.\n";
    }
}


// ==========================================
// 9. MENCARI INDEX TUGAS
// ==========================================

int pilihTugas() {

    if (daftarTugas.empty()) {
        cout << "\nBelum ada tugas yang tersedia.\n";
        return -1;
    }

    tampilkanTugas();

    int pilihan = inputAngka(
        "\nMasukkan nomor tugas: ");

    if (pilihan < 1 ||
        pilihan > (int)daftarTugas.size()) {

        cout << "Nomor tugas tidak valid!\n";
        return -1;
    }

    return pilihan - 1;
}


// ==========================================
// 10. MENGUBAH STATUS TUGAS
// ==========================================

void ubahStatus() {

    cout << "\n========== UBAH STATUS TUGAS ==========\n";

    int index = pilihTugas();

    if (index == -1) {
        return;
    }

    cout << "\nPilihan Status:\n";
    cout << "1. Belum Dikerjakan\n";
    cout << "2. Sedang Dikerjakan\n";
    cout << "3. Selesai\n";

    int pilihan = inputAngka("Pilih status: ");

    switch (pilihan) {

        case 1:
            daftarTugas[index].status = BELUM_DIKERJAKAN;
            break;

        case 2:
            daftarTugas[index].status = SEDANG_DIKERJAKAN;
            break;

        case 3:
            daftarTugas[index].status = SELESAI;
            break;

        default:
            cout << "Pilihan status tidak valid!\n";
            return;
    }

    cout << "Status tugas berhasil diperbarui!\n";
}


// ==========================================
// 11. EDIT TUGAS
// ==========================================

void editTugas() {

    cout << "\n========== EDIT TUGAS ==========\n";

    int index = pilihTugas();

    if (index == -1) {
        return;
    }

    cout << "\nMasukkan data baru:\n";

    daftarTugas[index].mataKuliah =
        inputTeks("Mata Kuliah Baru : ");

    daftarTugas[index].nama =
        inputTeks("Nama Tugas Baru  : ");

    daftarTugas[index].batasWaktu =
        inputTanggal("Deadline Baru");

    cout << "\nData tugas berhasil diperbarui!\n";
}


// ==========================================
// 12. HAPUS TUGAS
// ==========================================

void hapusTugas() {

    cout << "\n========== HAPUS TUGAS ==========\n";

    int index = pilihTugas();

    if (index == -1) {
        return;
    }

    string nama = daftarTugas[index].nama;

    daftarTugas.erase(daftarTugas.begin() + index);

    cout << "\nTugas \"" << nama
         << "\" berhasil dihapus!\n";
}


// ==========================================
// 13. STATISTIK AKADEMIK
// ==========================================

void statistikAkademik(Deadline hariIni) {

    int total = daftarTugas.size();

    int selesai = 0;
    int proses = 0;
    int belum = 0;
    int terlambat = 0;

    for (size_t i = 0; i < daftarTugas.size(); i++) {

        switch (daftarTugas[i].status) {

            case SELESAI:
                selesai++;
                break;

            case SEDANG_DIKERJAKAN:
                proses++;
                break;

            case BELUM_DIKERJAKAN:
                belum++;
                break;
        }

        if (daftarTugas[i].status != SELESAI &&
            selisihHari(
                daftarTugas[i].batasWaktu, hariIni) < 0) {

            terlambat++;
        }
    }

    double persentase = 0;

    if (total > 0) {
        persentase = (double)selesai / total * 100;
    }

    cout << "\n========== STATISTIK AKADEMIK ==========\n";

    cout << "Total Tugas       : " << total << endl;
    cout << "Tugas Selesai     : " << selesai << endl;
    cout << "Sedang Dikerjakan : " << proses << endl;
    cout << "Belum Dikerjakan  : " << belum << endl;
    cout << "Tugas Terlambat   : " << terlambat << endl;

    cout << fixed << setprecision(1);

    cout << "Progres Akademik  : "
         << persentase << "%\n";

    cout << "========================================\n";
}


// ==========================================
// 14. MAIN PROGRAM
// ==========================================

int main() {

    HariSekarang hariIni;

    int menuOption;

    cout << "============================================\n";
    cout << "  ACADEMIC WORKLOAD MANAGEMENT SYSTEM\n";
    cout << "============================================\n";

    Deadline tanggal;

    tanggal = inputTanggal(
        "Masukkan Tanggal Hari Ini");

    hariIni.hari = tanggal.hari;
    hariIni.bulan = tanggal.bulan;
    hariIni.tahun = tanggal.tahun;

    do {

        cout << "\n============================================\n";
        cout << "  ACADEMIC WORKLOAD MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "Tanggal Hari Ini: ";
        tampilkanTanggal({
            hariIni.hari,
            hariIni.bulan,
            hariIni.tahun
        });

        cout << "\n\nMENU UTAMA\n";

        cout << "1. Tambah Tugas\n";
        cout << "2. Daftar Semua Tugas\n";
        cout << "3. Deadline Reminder\n";
        cout << "4. Prioritas Tugas\n";
        cout << "5. Ubah Status Tugas\n";
        cout << "6. Edit Tugas\n";
        cout << "7. Hapus Tugas\n";
        cout << "8. Statistik Akademik\n";
        cout << "9. Ubah Tanggal Hari Ini\n";
        cout << "10. Keluar\n";

        menuOption = inputAngka("\nPilih Menu (1-10): ");

        switch (menuOption) {

            case 1:
                tambahTugas();
                break;

            case 2:
                tampilkanTugas();
                break;

            case 3:
                deadlineReminder({
                    hariIni.hari,
                    hariIni.bulan,
                    hariIni.tahun
                });
                break;

            case 4:
                tampilkanPrioritas({
                    hariIni.hari,
                    hariIni.bulan,
                    hariIni.tahun
                });
                break;

            case 5:
                ubahStatus();
                break;

            case 6:
                editTugas();
                break;

            case 7:
                hapusTugas();
                break;

            case 8:
                statistikAkademik({
                    hariIni.hari,
                    hariIni.bulan,
                    hariIni.tahun
                });
                break;

            case 9: {
                Deadline tanggalBaru =
                    inputTanggal("Ubah Tanggal Hari Ini");

                hariIni.hari = tanggalBaru.hari;
                hariIni.bulan = tanggalBaru.bulan;
                hariIni.tahun = tanggalBaru.tahun;

                cout << "Tanggal berhasil diperbarui!\n";
                break;
            }

            case 10:
                cout << "\nTerima kasih telah menggunakan "
                     << "Academic Workload Management System!\n";
                break;

            default:
                cout << "\nPilihan menu tidak valid!\n";
                break;
        }

    } while (menuOption != 10);

    return 0;
}
