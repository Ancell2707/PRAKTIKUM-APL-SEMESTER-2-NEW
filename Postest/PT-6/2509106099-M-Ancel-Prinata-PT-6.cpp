

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;
struct Buku {
    int    id;
    string judul;
    string penulis;
    int    tahun;
};
const int MAX_BUKU = 100;
string toLowerCase(const string& s) {
    string hasil = s;
    transform(hasil.begin(), hasil.end(), hasil.begin(), ::tolower);
    return hasil;
}
void tampilHeader() {
    cout << "\n" << string(65, '=') << "\n";
    cout << left
         << setw(6)  << "ID"
         << setw(28) << "Judul"
         << setw(20) << "Penulis"
         << setw(6)  << "Tahun" << "\n";
    cout << string(65, '-') << "\n";
}
void tampilBuku(const Buku& b) {
    cout << left
         << setw(6)  << b.id
         << setw(28) << b.judul
         << setw(20) << b.penulis
         << setw(6)  << b.tahun << "\n";
}
void tampilSemuaBuku(const Buku data[], int n) {
    if (n == 0) {
        cout << "\n  Belum ada data buku.\n";
        return;
    }
    tampilHeader();
    for (int i = 0; i < n; i++) tampilBuku(data[i]);
    cout << string(65, '=') << "\n";
}
void sortById(Buku data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (data[j].id > data[j + 1].id) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}
int binarySearchId(const Buku data[], int n, int targetId) {
    int low  = 0;
    int high = n - 1;
    int iterasi = 0;

    cout << "\n  Mencari ID: " << targetId << "\n";
    cout << string(40, '-') << "\n";

    while (low <= high) {
        int mid = (low + high) / 2;
        iterasi++;

        cout << "  Iterasi " << iterasi
             << " | low=" << low
             << "   mid="   << mid
             << "   high="  << high
             << " | data[mid].id=" << data[mid].id << "\n";

        if (data[mid].id == targetId) {
            cout << "  -> COCOK ditemukan di indeks " << mid << "\n";
            cout << string(40, '-') << "\n";
            cout << "  Total iterasi: " << iterasi << "\n";
            return mid;
        } else if (data[mid].id < targetId) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << string(40, '-') << "\n";
    cout << "  Total iterasi: " << iterasi << "\n";
    return -1; 
}

void linearSearchJudul(const Buku data[], int n, const string& targetJudul) {
    string target = toLowerCase(targetJudul);
    bool   ada    = false;
    int    iterasi = 0;

    cout << "\n  Mencari judul mengandung: \"" << targetJudul << "\"\n";
    cout << string(65, '-') << "\n";

    tampilHeader();

    for (int i = 0; i < n; i++) {
        iterasi++;
        string judulLower = toLowerCase(data[i].judul);
        if (judulLower.find(target) != string::npos) {
            tampilBuku(data[i]);
            ada = true;
        }
    }

    cout << string(65, '=') << "\n";
    cout << "  Total data diperiksa: " << iterasi << "\n";

    if (!ada) {
        cout << "\n  Tidak ada buku dengan judul mengandung \""
             << targetJudul << "\".\n";
    }
}
int main() {
    Buku dataBuku[] = {
        {105, "Bumi",                  "Tere Liye",       2014},
        {102, "Laskar Pelangi",        "Andrea Hirata",   2005},
        {108, "Negeri 5 Menara",       "Ahmad Fuadi",     2009},
        {101, "Sang Pemimpi",          "Andrea Hirata",   2006},
        {110, "Hujan",                 "Tere Liye",       2016},
        {103, "5 cm",                  "Donny Dhirgantoro",2005},
        {107, "Pulang",                "Tere Liye",       2015},
        {104, "Perahu Kertas",         "Dee Lestari",     2009},
        {106, "Supernova",             "Dee Lestari",     2001},
        {109, "Dilan 1990",            "Pidi Baiq",       2014},
    };

    int n = sizeof(dataBuku) / sizeof(dataBuku[0]);

    cout << "\n";
    cout << "  +================================================+\n";
    cout << "  |     SISTEM PENCARIAN DATA BUKU AA CLAN         |\n";
    cout << "  |  Binary Search (ID) | Linear Search (Judul)    |\n";
    cout << "  +================================================+\n";
    sortById(dataBuku, n);

    cout << "\n Data buku telah diurutkan berdasarkan ID.\n";
    tampilSemuaBuku(dataBuku, n);

    int pilihan;
    do {
        cout << "\n  +=============================+\n";
        cout << "  |          MENU               |\n";
        cout << "  +=============================+\n";
        cout << "  |  1. Cari berdasarkan ID     |  <- Binary Search\n";
        cout << "  |  2. Cari berdasarkan Judul  |  <- Linear Search\n";
        cout << "  |  3. Tampilkan semua buku    |\n";
        cout << "  |  4. Keluar                  |\n";
        cout << "  +=============================+\n";
        cout << "  Pilihan Anda: ";
        cin  >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1: {
            int idCari;
            cout << "\n  Masukkan ID buku yang dicari: ";
            cin  >> idCari;
            cin.ignore();

            int hasil = binarySearchId(dataBuku, n, idCari);

            if (hasil != -1) {
                cout << "\n  Sipp,Buku DITEMUKAN!\n";
                tampilHeader();
                tampilBuku(dataBuku[hasil]);
                cout << string(65, '=') << "\n";
            } else {
                cout << "\n   Buku dengan ID " << idCari << " TIDAK DITEMUKAN.\n";
            }
            break;
        }
        case 2: {
            string judulCari;
            cout << "\n  Masukkan judul (atau kata kunci) yang dicari: ";
            getline(cin, judulCari);

            linearSearchJudul(dataBuku, n, judulCari);
            break;
        }
        case 3:
            tampilSemuaBuku(dataBuku, n);
            break;

        case 4:
            cout << "\n  Terima kasih telah menggunakan programpencarian buku AA CLAN ini!\n\n";
            break;

        default:
            cout << "\n  [!] Pilihan tidak valid. Masukkan 1-4.\n";
        }

    } while (pilihan != 4);

    return 0;
}