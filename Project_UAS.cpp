#include <iostream>
#include <vector>
using namespace std;

struct deadline {
    string hari;
    string bulan;
    string tahun;
};

struct Tugas {
    string nama;
    deadline batas_waktu;
};

int main() {
    vector<Tugas> daftar_tugas;
    int menuOption = 0;

    do {
        cout << "\n-----Program Academic Workload Management System-----\n" << endl;
        cout << "Opsi menu yang tersedia:\n" << endl;
        cout << "1. Mencatat Tugas dan Deadline" << endl;
        cout << "2. Prioritas Tugas" << endl;
        cout << "3. Status Tugas" << endl;
        cout << "4. Keluar" << endl;
        cout << "\nSilakan pilih opsi menu (1-4): ";
        cin >> menuOption;

        switch (menuOption) {
            case 1: {
                int jumlah_tugas;
                cout << "\n--- Anda memilih opsi 1: Mencatat Tugas dan Deadline ---\n" << endl;
                cout << "Masukkan jumlah tugas yang ingin dicatat: ";
                cin >> jumlah_tugas;

                daftar_tugas.resize(jumlah_tugas);

                for (int i = 0; i < jumlah_tugas; i++) {
                    cout << "\nMasukkan Data Tugas ke-" << i + 1 << endl;
                    cout << "Nama tugas : ";
                    cin >> daftar_tugas[i].nama;
                    
                    cout << "Deadline (Hari)  : ";
                    cin >> daftar_tugas[i].batas_waktu.hari;
                    cout << "Deadline (Bulan) : ";
                    cin >> daftar_tugas[i].batas_waktu.bulan;
                    cout << "Deadline (Tahun) : ";
                    cin >> daftar_tugas[i].batas_waktu.tahun;
                }
                break;
            }
            case 2:
                cout << "\n--- Anda memilih opsi 2: Prioritas Tugas ---" << endl;
                if (daftar_tugas.empty()) {
                    cout << "Belum ada tugas yang dicatat! Silakan isi menu 1 terlebih dahulu." << endl;
                }
                break;
            case 3:
                cout << "\n--- Anda memilih opsi 3: Status Tugas ---" << endl;
                if (daftar_tugas.empty()) {
                    cout << "Belum ada tugas yang dicatat! Silakan isi menu 1 terlebih dahulu." << endl;
                }
                break;
            case 4:
                cout << "\nKeluar dari program. Terima kasih!" << endl;
                break;
            default:
                cout << "\nOpsi menu tidak valid. Silakan pilih angka antara 1 hingga 4." << endl;
                break;
        }

        if (menuOption == 1 && !daftar_tugas.empty()) {
            cout << "\n========================================" << endl;
            cout << "      DAFTAR TUGAS DAN DEADLINE ANDA     " << endl;
            cout << "========================================" << endl;
            for (size_t i = 0; i < daftar_tugas.size(); i++) {
                cout << "Tugas ke-" << i + 1 << endl;
                cout << "  - Nama Tugas : " << daftar_tugas[i].nama << endl;
                cout << "  - Deadline   : " << daftar_tugas[i].batas_waktu.hari << " " 
                     << daftar_tugas[i].batas_waktu.bulan << " " 
                     << daftar_tugas[i].batas_waktu.tahun << endl;
                cout << "----------------------------------------" << endl;
            }
        }

    } while (menuOption != 4);

    return 0;
}