test 
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct deadline {
    int hari;
    int bulan;
    int tahun;
};

struct Tugas {
    string nama;
    deadline batas_waktu;
};

struct hari_sekarang {
    int Hari;
    int Bulan;
    int Tahun;
};

long long hitungHariTotal(int h, int b, int t) {
    return (long long)t * 365 + (long long)b * 30 + (long long)h;
}

int main() {
    vector<Tugas> daftar_tugas;
    int menuOption = 0;
    hari_sekarang hari_ini;
    bool tanggal_sudah_diset = false;

    do {
        cout << "\n-----Program Academic Workload Management System-----\n" << endl;

        if (!tanggal_sudah_diset) {
            cout << "Masukkan terlebih dahulu tanggal hari ini (format angka - Hari Bulan Tahun): ";
            cin >> hari_ini.Hari >> hari_ini.Bulan >> hari_ini.Tahun;
            tanggal_sudah_diset = true;
            cout << "Tanggal Hari Ini telah diset menjadi: " << hari_ini.Hari << "/" << hari_ini.Bulan << "/" << hari_ini.Tahun << endl;
            cout << "\n\n\n";
        } else {
            cout << "Tanggal Hari Ini: " << hari_ini.Hari << "/" << hari_ini.Bulan << "/" << hari_ini.Tahun << " (Ketik 0 jika ingin mengubah tanggal)" << endl;
        }

        cout << "\nOpsi menu yang tersedia:" << endl;
        cout << "1. Mencatat Tugas dan Deadline" << endl;
        cout << "2. Prioritas Tugas (Cari Tenggat Paling Dekat & Urgent)" << endl;
        cout << "3. Status Tugas" << endl;
        cout << "4. Keluar" << endl;
        cout << "\nSilakan pilih opsi menu (1-4): ";
        cin >> menuOption;

        if (menuOption == 0) {
            tanggal_sudah_diset = false;
            continue;
        }

        switch (menuOption) {
            case 1: {
                int jumlah_tugas;
                cout << "--- Anda memilih opsi 1: Mencatat Tugas dan Deadline ---\n" << endl;
                cout << "Masukkan jumlah tugas yang ingin dicatat: ";
                cin >> jumlah_tugas;

                daftar_tugas.resize(jumlah_tugas);

                for (int i = 0; i < jumlah_tugas; i++) {
                    cout << "\nMasukkan Data Tugas ke-" << i + 1 << endl;
                    cout << "Nama tugas : ";
                    cin >> daftar_tugas[i].nama;
                    
                    cout << "Deadline (Hari angka)  : ";
                    cin >> daftar_tugas[i].batas_waktu.hari;
                    cout << "Deadline (Bulan angka) : ";
                    cin >> daftar_tugas[i].batas_waktu.bulan;
                    cout << "Deadline (Tahun angka) : ";
                    cin >> daftar_tugas[i].batas_waktu.tahun;
                }
                break;
            }
            case 2: {
                cout << "--- Anda memilih opsi 2: Prioritas Tugas (Urgent & Terdekat) ---" << endl;
                if (daftar_tugas.empty()) {
                    cout << "Belum ada tugas yang dicatat! Silakan isi menu 1 terlebih dahulu." << endl;
                    break;
                }

                long long hari_ini_total = hitungHariTotal(hari_ini.Hari, hari_ini.Bulan, hari_ini.Tahun);
                
                // Variabel untuk melacak tugas paling mendesak
                int index_paling_urgent = -1;
                long long selisih_terkecil = -1;

                cout << "\n\n\n=======================================================" << endl;
                cout << "               ANALISIS PRIORITAS TUGAS                " << endl;
                cout << "=======================================================" << endl;

                for (size_t i = 0; i < daftar_tugas.size(); i++) {
                    long long deadline_total = hitungHariTotal(daftar_tugas[i].batas_waktu.hari, 
                                                               daftar_tugas[i].batas_waktu.bulan, 
                                                               daftar_tugas[i].batas_waktu.tahun);
                    long long sisa_hari = deadline_total - hari_ini_total;

                    cout << "Tugas ke-" << i + 1 << ": " << daftar_tugas[i].nama << endl;
                    cout << "  - Deadline : " << daftar_tugas[i].batas_waktu.hari << "/" 
                         << daftar_tugas[i].batas_waktu.bulan << "/" 
                         << daftar_tugas[i].batas_waktu.tahun << endl;

                    if (sisa_hari < 0) {
                        cout << "  - Status   : \033[31mTERLAMBAT (Overdue)!\033[0m" << endl;
                    } else if (sisa_hari == 0) {
                        cout << "  - Status   : \033[33mJATUH TEMPO HARI INI!\033[0m" << endl;
                    } else {
                        cout << "  - Sisa Waktu: " << sisa_hari << " hari lagi" << endl;
                    }

                    if (sisa_hari >= 0) {
                        if (selisih_terkecil == -1 || sisa_hari < selisih_terkecil) {
                            selisih_terkecil = sisa_hari;
                            index_paling_urgent = i;
                        }
                    }
                    cout << "-------------------------------------------------------" << endl;
                }

                if (index_paling_urgent != -1) {
                    cout << "\n>>> REKOMENDASI UTAMA (PALING URGENT): <<<\n";
                    cout << "Kerjakan tugas \"" << daftar_tugas[index_paling_urgent].nama 
                         << "\" terlebih dahulu karena tenggatnya paling dekat (" 
                         << selisih_terkecil << " hari lagi)!\n";
                } else {
                    cout << "\n>>> Semua tugas yang tercatat sudah melewati tenggat waktu (Overdue). <<<\n";
                }
                break;
            }
            case 3:
                cout << "--- Anda memilih opsi 3: Status Tugas ---" << endl;
                if (daftar_tugas.empty()) {
                    cout << "Belum ada tugas yang dicatat! Silakan isi menu 1 terlebih dahulu." << endl;
                } else {
                    cout << "Total tugas aktif saat ini: " << daftar_tugas.size() << " tugas." << endl;
                }
                break;
            case 4:
                cout << "Keluar dari program. Terima kasih!" << endl;
                break;
            default:
                cout << "\nOpsi menu tidak valid. Silakan pilih angka antara 1 hingga 4." << endl;
                break;
        }

        if (menuOption == 1 && !daftar_tugas.empty()) {
            cout << "\n\n\n========================================" << endl;
            cout << "      DAFTAR TUGAS DAN DEADLINE ANDA     " << endl;
            cout << "========================================" << endl;
            for (size_t i = 0; i < daftar_tugas.size(); i++) {
                cout << "Tugas ke-" << i + 1 << endl;
                cout << "  - Nama Tugas : " << daftar_tugas[i].nama << endl;
                cout << "  - Deadline   : " << daftar_tugas[i].batas_waktu.hari << "/" 
                     << daftar_tugas[i].batas_waktu.bulan << "/" 
                     << daftar_tugas[i].batas_waktu.tahun << endl;
                cout << "----------------------------------------" << endl;
            }
        }

    } while (menuOption != 4);

    return 0;
}