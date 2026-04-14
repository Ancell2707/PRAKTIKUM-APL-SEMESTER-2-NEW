#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define MAX_STOK 100
#define MAX_KAT  4

struct AlatMusik {
    int    id;
    string nama;
    int    harga;
    int    jumlah;
    string kategori;
};

AlatMusik stok[MAX_STOK] = {
    {1, "Gitar",     1500000, 5, "Senar"},
    {2, "Piano",     5000000, 2, "Keyboard"},
    {3, "Drum",      3000000, 3, "Perkusi"},
    {4, "Saxophone", 2500000, 1, "Tiup"}
};
int jumlahStok = 4;

string daftarKategori[MAX_KAT] = {"Senar", "Tiup", "Perkusi", "Keyboard"};

const string ATAP   =        string(62, '_');
const string LANTAI = "||" + string(58, '_') + "||";
const string SPASI  = "||" + string(58, ' ') + "||";


void cls() {
    for (int i = 0; i < 50; i++) cout << "\n";
}

void pause() {
    cout << "\nEnter untuk lanjut...";
    cin.ignore();
    cin.get();
}

string toLower(string s) {
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + 32;
    return s;
}

string capitalize(string s) {
    if (!s.empty())
        if (s[0] >= 'a' && s[0] <= 'z')
            s[0] = s[0] - 32;
    return s;
}

bool kategoriValid(const string& kat) {
    for (int i = 0; i < MAX_KAT; i++)
        if (daftarKategori[i] == kat) return true;
    return false;
}

int nextId(AlatMusik arr[], int n) {
    int maxId = 0;
    for (int i = 0; i < n; i++)
        if (arr[i].id > maxId) maxId = arr[i].id;
    return maxId + 1;
}

void cetakGarisTabel() {
    cout << "+" << string(6,  '-')
         << "+" << string(20, '-')
         << "+" << string(14, '-')
         << "+" << string(8,  '-')
         << "+" << string(12, '-')
         << "+\n";
}

void cetakHeaderTabel() {
    cetakGarisTabel();
    cout << "| " << left
         << setw(5)  << "ID"         << "| "
         << setw(19) << "Nama"       << "| "
         << setw(13) << "Harga (Rp)" << "| "
         << setw(7)  << "Stok"       << "| "
         << setw(11) << "Kategori"
         << "|\n";
    cetakGarisTabel();
}

void cetakBarisTabel(const AlatMusik& item) {
    cout << "| " << left
         << setw(5)  << item.id       << "| "
         << setw(19) << item.nama     << "| "
         << setw(13) << item.harga    << "| "
         << setw(7)  << item.jumlah   << "| "
         << setw(11) << item.kategori
         << "|\n";
}

void cetakJudul(const string& judul) {
    cls();
    cout << ATAP << "\n";
    cout << "||" << setw(58) << left << ("  " + judul) << "||\n";
    cout << LANTAI << "\n\n";
}

void tampilKategori(string kategori[], int jumlah) {
    cout << "\n  Kategori tersedia:\n";
    for (int i = 0; i < jumlah; i++)
        cout << "    - " << kategori[i] << "\n";
}

void tampilStok(AlatMusik arr[], int n, bool adminMode) {
    if (adminMode)
        cetakJudul("Daftar Stok Alat Musik [ADMIN]");
    else
        cetakJudul("Daftar Stok Alat Musik (Hanya Lihat)");

    if (n == 0) {
        cout << "  (Belum ada data)\n";
        return;
    }

    cetakHeaderTabel();
    for (int i = 0; i < n; i++)
        cetakBarisTabel(arr[i]);
    cetakGarisTabel();

    cout << "  Total: " << n << " item\n";
}

void tambahItem(AlatMusik arr[], int& n, string kategori[], int jmlKat) {
    if (n >= MAX_STOK) {
        cout << "\n  Array penuh! Maksimal " << MAX_STOK << " item.\n";
        pause();
        return;
    }

    cetakJudul("Tambah Item Baru");

    AlatMusik baru;
    baru.id = nextId(arr, n);

    cout << "  Nama alat musik : "; getline(cin, baru.nama);
    cout << "  Harga (Rp)      : "; cin  >> baru.harga;
    cout << "  Jumlah stok     : "; cin  >> baru.jumlah;
    cin.ignore();

    tampilKategori(kategori, jmlKat);

    cout << "  Pilih kategori  : ";
    getline(cin, baru.kategori);
    baru.kategori = capitalize(baru.kategori);

    if (kategoriValid(baru.kategori)) {
        arr[n] = baru;
        n++;
        cout << "\n  Item \"" << baru.nama
             << "\" ditambahkan (ID: " << baru.id << ").\n";
    } else {
        cout << "\n  Kategori tidak valid!\n";
    }
    pause();
}

void ubahStok(AlatMusik arr[], int n) {
    if (n == 0) {
        cout << "\n  Stok kosong!\n";
        pause();
        return;
    }

    tampilStok(arr, n, true);

    int idCari;
    cout << "\n  ID item yang ingin diubah stoknya: ";
    cin >> idCari;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        if (arr[i].id == idCari) {
            cout << "  Stok baru untuk \"" << arr[i].nama
                 << "\" (saat ini: " << arr[i].jumlah << "): ";
            cin >> arr[i].jumlah;
            cin.ignore();
            cout << "  Stok berhasil diubah!\n";
            pause();
            return;
        }
    }
    cout << "  ID tidak ditemukan!\n";
    pause();
}

void hapusItem(AlatMusik arr[], int& n) {
    if (n == 0) {
        cout << "\n  Stok kosong!\n";
        pause();
        return;
    }

    tampilStok(arr, n, true);

    string namaHapus;
    cout << "\n  Nama item yang ingin dihapus: ";
    getline(cin, namaHapus);

    for (int i = 0; i < n; i++) {
        if (toLower(arr[i].nama) == toLower(namaHapus)) {
            string namaTemp = arr[i].nama;
            for (int j = i; j < n - 1; j++)
                arr[j] = arr[j + 1];
            n--;

            cout << "  Item \"" << namaTemp << "\" berhasil dihapus!\n";
            pause();
            return;
        }
    }

    cetakJudul("Item Tidak Ditemukan");
    pause();
}

void cariKategori(AlatMusik arr[], int n, string kategori[], int jmlKat) {
    tampilKategori(kategori, jmlKat);

    string cari;
    cout << "\n  Masukkan kategori: ";
    getline(cin, cari);
    cari = capitalize(cari);

    bool ada = false;
    for (int i = 0; i < n; i++) {
        if (arr[i].kategori == cari) {
            if (!ada) {
                cout << "\n";
                cetakHeaderTabel();
                ada = true;
            }
            cetakBarisTabel(arr[i]);
        }
    }

    if (ada)
        cetakGarisTabel();
    else
        cout << "\n  Tidak ada item di kategori \"" << cari << "\".\n";

    pause();
}

void menuUser(AlatMusik arr[], int& n, string kategori[], int jmlKat) {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left << "  MENU USER (Pengguna)"               << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58) << "  1. Tampilkan Stok"                  << "||\n";
        cout << "||" << left << setw(58) << "  2. Cari Item Berdasarkan Kategori"  << "||\n";
        cout << "||" << left << setw(58) << "  3. Kembali ke Menu Utama"           << "||\n";
        cout << LANTAI << "\n\n";

        string pilihan;
        cout << "  Pilih menu (1-3): ";
        cin >> pilihan;
        cin.ignore();

        if      (pilihan == "1") { tampilStok(arr, n, false); pause(); }
        else if (pilihan == "2") { cariKategori(arr, n, kategori, jmlKat); }
        else if (pilihan == "3") { break; }
        else { cout << "\n  Pilihan tidak valid!\n"; pause(); }
    }
}

void menuAdmin(AlatMusik arr[], int& n, string kategori[], int jmlKat) {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left << "  MENU ADMIN"                         << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58) << "  1. Tampilkan Stok"                  << "||\n";
        cout << "||" << left << setw(58) << "  2. Tambah Item Baru"                << "||\n";
        cout << "||" << left << setw(58) << "  3. Ubah Stok Item"                  << "||\n";
        cout << "||" << left << setw(58) << "  4. Hapus Item"                      << "||\n";
        cout << "||" << left << setw(58) << "  5. Cari Item Berdasarkan Kategori"  << "||\n";
        cout << "||" << left << setw(58) << "  6. Kembali ke Menu Utama"           << "||\n";
        cout << LANTAI << "\n\n";

        string pilihan;
        cout << "  Pilih menu (1-6): ";
        cin >> pilihan;
        cin.ignore();

        if      (pilihan == "1") { tampilStok(arr, n, true); pause(); }
        else if (pilihan == "2") { tambahItem(arr, n, kategori, jmlKat); }
        else if (pilihan == "3") { ubahStok(arr, n); }
        else if (pilihan == "4") { hapusItem(arr, n); }
        else if (pilihan == "5") { cariKategori(arr, n, kategori, jmlKat); }
        else if (pilihan == "6") { break; }
        else { cout << "\n  Pilihan tidak valid!\n"; pause(); }
    }
}


int main() {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left << "       SELAMAT DATANG DI TOKO ALAT MUSIK" << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58) << "  1. Masuk sebagai User  - Akses Terbatas" << "||\n";
        cout << "||" << left << setw(58) << "  2. Masuk sebagai Admin - Akses Penuh"    << "||\n";
        cout << "||" << left << setw(58) << "  3. Keluar"                               << "||\n";
        cout << LANTAI << "\n\n";

        string role;
        cout << "  Pilih role (1-3): ";
        cin >> role;
        cin.ignore();

        if      (role == "1") { menuUser(stok, jumlahStok, daftarKategori, MAX_KAT); }
        else if (role == "2") { menuAdmin(stok, jumlahStok, daftarKategori, MAX_KAT); }
        else if (role == "3") {
            cout << "\n  Terima kasih telah mengunjungi Toko Alat Musik!\n\n";
            break;
        } else {
            cout << "\n  Pilihan tidak valid!\n";
            pause();
        }
    }
    return 0;
}