#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define MAX_STOK  100
#define MAX_KAT   4
#define MAX_AKUN  20

struct AlatMusik {
    int    id;
    string nama;
    int    harga;
    int    jumlah;
    string kategori;
};

struct Akun {
    string username;
    string password;
    string role;    
};

AlatMusik stok[MAX_STOK] = {
    {1, "Gitar",     1500000, 5, "Senar"},
    {2, "Piano",     5000000, 2, "Keyboard"},
    {3, "Drum",      3000000, 3, "Perkusi"},
    {4, "Saxophone", 2500000, 1, "Tiup"}
};
int jumlahStok = 4;

Akun daftarAkun[MAX_AKUN] = {
    {"admin 123",  "admin123", "admin"},  
    {"user1",  "user111",  "user"},
    {"user2",  "user222",  "user"}
};
int jumlahAkun = 3;

string daftarKategori[MAX_KAT] = {"Senar", "Tiup", "Perkusi", "Keyboard"};

const string ATAP   =        string(62, '_');
const string LANTAI = "||" + string(58, '_') + "||";
const string SPASI  = "||" + string(58, ' ') + "||";
const string GARIS  = "  " + string(58, '-');
void cls() {
    for (int i = 0; i < 50; i++) cout << "\n";
}

void pause() {
    cout << "\nEnter untuk lanjut...";
    cin.ignore();
    cin.get();
}

string toLower(string teks) {
    for (int i = 0; i < (int)teks.size(); i++)
        if (teks[i] >= 'A' && teks[i] <= 'Z')
            teks[i] = teks[i] + 32;
    return teks;
}

string capitalize(string teks) {
    if (!teks.empty())
        if (teks[0] >= 'a' && teks[0] <= 'z')
            teks[0] = teks[0] - 32;
    return teks;
}

bool kategoriValid(const string& namaKategori) {
    for (int i = 0; i < MAX_KAT; i++)
        if (daftarKategori[i] == namaKategori) return true;
    return false;
}

int nextId(AlatMusik arr[], int jumlah) {
    int idTerbesar = 0;
    for (int i = 0; i < jumlah; i++)
        if (arr[i].id > idTerbesar) idTerbesar = arr[i].id;
    return idTerbesar + 1;
}

bool usernameAda(Akun listAkun[], int jumlahAkun, const string& usernameInput) {
    for (int i = 0; i < jumlahAkun; i++)
        if (listAkun[i].username == usernameInput) return true;
    return false;
}

bool panjangValid(const string& teks, int minPanjang) {
    return (int)teks.size() >= minPanjang;
}

bool passwordKuat(const string& kataSandi) {
    bool adaHuruf = false, adaAngka = false;
    for (int i = 0; i < (int)kataSandi.size(); i++) {
        if ((kataSandi[i] >= 'a' && kataSandi[i] <= 'z') ||
            (kataSandi[i] >= 'A' && kataSandi[i] <= 'Z'))
            adaHuruf = true;
        if (kataSandi[i] >= '0' && kataSandi[i] <= '9')
            adaAngka = true;
    }
    return adaHuruf && adaAngka;
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

void tampilKategori(string kategori[], int jumlahKategori) {
    cout << "\n  Kategori tersedia:\n";
    for (int i = 0; i < jumlahKategori; i++)
        cout << "    - " << kategori[i] << "\n";
}

void tampilStok(AlatMusik arr[], int jumlah, bool adminMode) {
    if (adminMode)
        cetakJudul("Daftar Stok Alat Musik AA Clan");
    else
        cetakJudul("Daftar Stok Alat Musik AA Clan ");

    if (jumlah == 0) {
        cout << "  (Belum ada data)\n";
        return;
    }

    cetakHeaderTabel();
    for (int i = 0; i < jumlah; i++)
        cetakBarisTabel(arr[i]);
    cetakGarisTabel();
    cout << "  Total: " << jumlah << " item\n";
}
void sortNamaAscending(AlatMusik arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (toLower(arr[j].nama) > toLower(arr[j + 1].nama)) {
                AlatMusik temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
}

void sortIdAscending(AlatMusik arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (arr[j].id > arr[j + 1].id) {
                AlatMusik temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
}

void sortHargaDescending(AlatMusik arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (arr[j].harga < arr[j + 1].harga) {
                AlatMusik temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
}

void sortStokAscending(AlatMusik arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (arr[j].jumlah > arr[j + 1].jumlah) {
                AlatMusik temp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = temp;
            }
}

void menuSorting(AlatMusik arr[], int jumlahData, bool adminMode) {
    AlatMusik temp[MAX_STOK];
    for (int i = 0; i < jumlahData; i++) temp[i] = arr[i];

    cetakJudul("Menu Sorting Alat Musik");
    cout << "||" << left << setw(58) << "  1.  Nama   : A -> Z "            << "||\n";
    cout << "||" << left << setw(58) << "  2.  Harga  : Mahal -> Murah "    << "||\n";
    cout << "||" << left << setw(58) << "  3.  Stok   : Sedikit -> Banyak " << "||\n";
    cout << "||" << left << setw(58) << "  4. Kembali"                      << "||\n";
    cout << LANTAI << "\n\n";

    string pilihan;
    cout << "  Pilih metode sorting (1-4): ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == "1") {
        sortNamaAscending(temp, jumlahData);
        cetakJudul("Hasil Sort: Nama A -> Z (Ascending)");
        cetakHeaderTabel();
        for (int i = 0; i < jumlahData; i++) cetakBarisTabel(temp[i]);
        cetakGarisTabel();
        cout << "  Metode: Bubble Sort | Kunci: Nama | Urutan: Ascending\n";
    } else if (pilihan == "2") {
        sortHargaDescending(temp, jumlahData);
        cetakJudul("Hasil Sort: Harga Mahal -> Murah (Descending)");
        cetakHeaderTabel();
        for (int i = 0; i < jumlahData; i++) cetakBarisTabel(temp[i]);
        cetakGarisTabel();
        cout << "  Metode: Bubble Sort | Kunci: Harga | Urutan: Descending\n";
    } else if (pilihan == "3") {
        sortStokAscending(temp, jumlahData);
        cetakJudul("Hasil Sort: Stok Sedikit -> Banyak (Ascending)");
        cetakHeaderTabel();
        for (int i = 0; i < jumlahData; i++) cetakBarisTabel(temp[i]);
        cetakGarisTabel();
        cout << "  Metode: Bubble Sort | Kunci: Stok | Urutan: Ascending\n";
    } else if (pilihan == "4") {
        return;
    } else {
        cout << "\n  Pilihan tidak ada!\n";
    }
    pause();
}
int binarySearchById(AlatMusik arr[], int jumlah, int idDicari) {
    int low  = 0;
    int high = jumlah - 1;
    int iterasi = 0;

    cout << "\n   Mencari ID: " << idDicari << "\n";
    cout << "  " << string(54, '-') << "\n";

    while (low <= high) {
        iterasi++;
        int mid = (low + high) / 2;

        cout << "  Iterasi " << iterasi
             << " | low=" << low << " mid=" << mid << " high=" << high
             << " | arr[mid].id=" << arr[mid].id;

        if (arr[mid].id == idDicari) {
            cout << " --> DITEMUKAN!\n";
            return mid;                
        } else if (arr[mid].id < idDicari) {
            cout << " --> cari ke KANAN\n";
            low = mid + 1;
        } else {
            cout << " --> cari ke KIRI\n";
            high = mid - 1;
        }
    }
    cout << "  ID tidak ditemukan setelah " << iterasi << " iterasi.\n";
    return -1;                         
}

void menuCariById(AlatMusik arr[], int jumlahData) {
    cetakJudul("Cari Alat Musik Berdasarkan ID ");

    if (jumlahData == 0) {
        cout << "  Belum ada data.\n";
        pause();
        return;
    }
    AlatMusik temp[MAX_STOK];
    for (int i = 0; i < jumlahData; i++) temp[i] = arr[i];
    sortIdAscending(temp, jumlahData);
    cout << "  Data (sudah diurutkan by ID untuk Binary Search):\n";
    cetakHeaderTabel();
    for (int i = 0; i < jumlahData; i++) cetakBarisTabel(temp[i]);
    cetakGarisTabel();

    int idDicari;
    cout << "\n  Masukkan ID yang dicari: ";
    cin >> idDicari;
    cin.ignore();

    int idx = binarySearchById(temp, jumlahData, idDicari);

    cout << "\n  " << string(54, '-') << "\n";
    if (idx != -1) {
        cout << "  HASIL — Item ditemukan:\n\n";
        cetakHeaderTabel();
        cetakBarisTabel(temp[idx]);
        cetakGarisTabel();
        cout << "  Metode : Binary Search\n";
        cout << "  Kunci  : ID (angka)\n";
    } else {
        cout << "  Item dengan ID " << idDicari << " tidak ditemukan.\n";
    }
    pause();
}
void sequentialSearchByNama(AlatMusik arr[], int jumlah, const string& keyword) {
    string keyLower = toLower(keyword);
    bool   adaHasil = false;
    int    iterasi  = 0;

    cout << "\n  [Sequential Search] Keyword: \"" << keyword << "\"\n";
    cout << "  " << string(54, '-') << "\n";

    for (int i = 0; i < jumlah; i++) {
        iterasi++;
        string namaLower = toLower(arr[i].nama);
        bool cocok = (namaLower.find(keyLower) != string::npos);

        cout << "  Iterasi " << iterasi
             << " | Periksa: \"" << arr[i].nama << "\""
             << (cocok ? " --> COCOK!" : "");
        cout << "\n";

        if (cocok) {
            if (!adaHasil) {
                cout << "\n  Hasil Pencarian:\n";
                cetakHeaderTabel();
            }
            cetakBarisTabel(arr[i]);
            adaHasil = true;
        }
    }

    if (adaHasil) {
        cetakGarisTabel();
    } else {
        cout << "\n  Tidak ada item dengan nama yang mengandung \""
             << keyword << "\".\n";
    }

    cout << "  " << string(54, '-') << "\n";
    cout << "  Metode  : Sequential Search (Linear Search)\n";
    cout << "  Kunci   : Nama (kata/huruf)  case-insensitive\n";
    cout << "  Iterasi : " << iterasi << " kali\n";
}

void menuCariByNama(AlatMusik arr[], int jumlahData) {
    cetakJudul("Cari Alat Musik Berdasarkan Nama ");

    if (jumlahData == 0) {
        cout << "  Belum ada data.\n";
        pause();
        return;
    }

    cout << "  Data saat ini:\n";
    cetakHeaderTabel();
    for (int i = 0; i < jumlahData; i++) cetakBarisTabel(arr[i]);
    cetakGarisTabel();

    string keyword;
    cout << "\n  Masukkan nama : \"\"): ";
    getline(cin, keyword);

    if (keyword.empty()) {
        cout << "\n  Keyword tidak boleh kosong!\n";
        pause();
        return;
    }

    sequentialSearchByNama(arr, jumlahData, keyword);
    pause();
}
void menuSearching(AlatMusik arr[], int jumlahData, bool adminMode) {
    while (true) {
        cetakJudul("Menu Searching Alat Musik");
        cout << "||" << left << setw(58)
             << "  1. Cari Berdasarkan ID   (Binary Search)"         << "||\n";
        cout << "||" << left << setw(58)
             << "  2. Cari Berdasarkan Nama (Sequential Search)"     << "||\n";
        cout << "||" << left << setw(58)
             << "  3. Kembali"                                       << "||\n";
        cout << LANTAI << "\n\n";

        string pilihan;
        cout << "  Pilih (1-3): ";
        cin >> pilihan;
        cin.ignore();

        if      (pilihan == "1") menuCariById(arr, jumlahData);
        else if (pilihan == "2") menuCariByNama(arr, jumlahData);
        else if (pilihan == "3") return;
        else { cout << "\n  Pilihan tidak ada!\n"; pause(); }
    }
}

bool prosesRegister(Akun listAkun[], int& jumlahAkun) {
    cetakJudul("REGISTER - Buat Akun Baru");

    if (jumlahAkun >= MAX_AKUN) {
        cout << "  Kapasitas akun penuh! Tidak dapat mendaftar wle.\n";
        pause();
        return false;
    }

    cout << "  Ketentuan akun:\n";
    cout << "    - Username minimal 4 karakter\n";
    cout << "    - Password minimal 6 karakter\n";
    cout << "    - Password harus mengandung huruf dan angka\n";
    cout << "    - Akun baru otomatis terdaftar sebagai User\n";
    cout << GARIS << "\n\n";

    Akun akunBaru;

    while (true) {
        cout << "  Username baru  : ";
        getline(cin, akunBaru.username);
        if (!panjangValid(akunBaru.username, 4)) {
            cout << "  Username minimal 4 karakter. Coba lagi.\n\n";
            continue;
        }
        if (usernameAda(listAkun, jumlahAkun, akunBaru.username)) {
            cout << "   Username \"" << akunBaru.username
                 << "\" sudah dipakai. Pilih username lain.\n\n";
            continue;
        }
        break;
    }

    string konfirmasiPassword;
    while (true) {
        cout << "  Password baru  : ";
        getline(cin, akunBaru.password);
        if (!panjangValid(akunBaru.password, 6)) {
            cout << "  Password minimal 6 karakter. Coba lagi.\n\n";
            continue;
        }
        if (!passwordKuat(akunBaru.password)) {
            cout << "  Password harus mengandung huruf dan angka.\n\n";
            continue;
        }
        cout << "  Konfirmasi pw  : ";
        getline(cin, konfirmasiPassword);
        if (akunBaru.password != konfirmasiPassword) {
            cout << "   Password tidak cocok. Ulangi dari password.\n\n";
            continue;
        }
        break;
    }

    akunBaru.role = "user";
    listAkun[jumlahAkun] = akunBaru;
    jumlahAkun++;

    cout << "\n  [INFO & ] Alamat jumlahAkun : " << &jumlahAkun
         << " | Nilai sekarang : " << jumlahAkun << "\n";
    cout << "\n" << GARIS << "\n";
    cout << "  Registrasi berhasil!\n";
    cout << "  Username : " << akunBaru.username << "\n";
    cout << "  Role     : " << akunBaru.role << "\n";
    cout << "  Silakan login dengan akun baru Anda.\n";
    pause();
    return true;
}

Akun* prosesLogin(Akun listAkun[], int jumlahAkun) {
    cetakJudul("LOGIN - Toko Alat Musik");

    string inputUsername, inputPassword;
    int    jumlahPercobaan = 0;
    const int BATAS_COBA   = 3;

    while (jumlahPercobaan < BATAS_COBA) {
        cout << "  Username : ";
        getline(cin, inputUsername);
        cout << "  Password :  ";
        getline(cin, inputPassword);

        for (int i = 0; i < jumlahAkun; i++) {
            if (listAkun[i].username == inputUsername &&
                listAkun[i].password == inputPassword) {
                cout << "\n" << GARIS << "\n";
                cout << "  Login berhasil! Welcome To toko Musik AA Clan "
                     << listAkun[i].username << ".\n";
                cout << "  Role     : " << listAkun[i].role << "\n";
                pause();
                return &listAkun[i];
            }
        }
        jumlahPercobaan++;
        int sisaPercobaan = BATAS_COBA - jumlahPercobaan;
        cout << "\n  [!] Username atau password salah!";
        if (sisaPercobaan > 0)
            cout << " Sisa percobaan: " << sisaPercobaan << "\n\n";
        else
            cout << "\n";
    }

    cout << "\n  SUDAH DIBILANGI SALAH NGOTOT. Kutolak Pokonya.\n";
    pause();
    return nullptr;
}
void tambahItem(AlatMusik arr[], int& jumlahData,
                string kategori[], int jumlahKategori) {
    if (jumlahData >= MAX_STOK) {
        cout << "\n  Array penuh! Maksimal " << MAX_STOK << " item.\n";
        pause();
        return;
    }

    cetakJudul("Tambah Item Baru");

    AlatMusik itemBaru;
    itemBaru.id = nextId(arr, jumlahData);

    cout << "  Nama alat musik : "; getline(cin, itemBaru.nama);
    cout << "  Harga (Rp)      : "; cin  >> itemBaru.harga;
    cout << "  Jumlah stok     : "; cin  >> itemBaru.jumlah;
    cin.ignore();

    tampilKategori(kategori, jumlahKategori);
    cout << "  Pilih kategori  : ";
    getline(cin, itemBaru.kategori);
    itemBaru.kategori = capitalize(itemBaru.kategori);

    if (kategoriValid(itemBaru.kategori)) {
        arr[jumlahData] = itemBaru;
        jumlahData++;
        cout << "\n  Item \"" << itemBaru.nama
             << "\" berhasil ditambahkan (ID: " << itemBaru.id << ").\n";
        cout << "  [INFO & ] Alamat jumlahData : " << &jumlahData
             << " | Nilai sekarang : " << jumlahData << "\n";
    } else {
        cout << "\n  Kategori tidak ditemukan!\n";
    }
    pause();
}

void ubahStok(AlatMusik arr[], int jumlahData) {
    if (jumlahData == 0) { cout << "\n  Stok HABISS!\n"; pause(); return; }

    tampilStok(arr, jumlahData, true);

    int idDicari;
    cout << "\n  ID item yang ingin diubah stoknya: ";
    cin >> idDicari;
    cin.ignore();

    for (int i = 0; i < jumlahData; i++) {
        if (arr[i].id == idDicari) {
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

void hapusItem(AlatMusik arr[], int& jumlahData) {
    if (jumlahData == 0) { cout << "\n  Stok Habis!\n"; pause(); return; }

    tampilStok(arr, jumlahData, true);

    string namaYangDihapus;
    cout << "\n  Nama item yang ingin dihapus: ";
    getline(cin, namaYangDihapus);

    for (int i = 0; i < jumlahData; i++) {
        if (toLower(arr[i].nama) == toLower(namaYangDihapus)) {
            string namaSementara = arr[i].nama;
            for (int j = i; j < jumlahData - 1; j++)
                arr[j] = arr[j + 1];
            jumlahData--;
            cout << "  Item \"" << namaSementara << "\" berhasil dihapus!\n";
            cout << "  [INFO & ] Alamat jumlahData : " << &jumlahData
                 << " | Nilai sekarang : " << jumlahData << "\n";
            pause();
            return;
        }
    }
    cout << "\n  Item tidak ditemukan!\n";
    pause();
}

void ubahHargaViaPointer(int* ptrHarga, const string& namaItem) {
    cout << "  Harga saat ini \"" << namaItem
         << "\" : Rp " << *ptrHarga << "\n";
    cout << "  Harga baru (Rp)  : ";
    int nilaiHargaBaru;
    cin >> nilaiHargaBaru;
    cin.ignore();
    *ptrHarga = nilaiHargaBaru;
    cout << "  [INFO *] Alamat harga : " << ptrHarga
         << " | Nilai baru : Rp " << *ptrHarga << "\n";
}

AlatMusik* cariItemById(AlatMusik arr[], int jumlahData, int idDicari) {
    for (int i = 0; i < jumlahData; i++)
        if (arr[i].id == idDicari) return &arr[i];
    return nullptr;
}

void menuUbahHarga(AlatMusik arr[], int jumlahData) {
    if (jumlahData == 0) { cout << "\n  Stok Habis!\n"; pause(); return; }

    tampilStok(arr, jumlahData, true);

    int idDicari;
    cout << "\n  ID item yang ingin diubah harganya: ";
    cin >> idDicari;
    cin.ignore();

    AlatMusik* ptrItem = cariItemById(arr, jumlahData, idDicari);

    if (ptrItem == nullptr) {
        cout << "  ID tidak ditemukan!\n";
    } else {
        cout << "\n  Item ditemukan:\n";
        cetakHeaderTabel();
        cetakBarisTabel(*ptrItem);
        cetakGarisTabel();
        cout << "  [INFO *] Alamat item : " << ptrItem << "\n\n";
        ubahHargaViaPointer(&ptrItem->harga, ptrItem->nama);
        cout << "\n  Harga berhasil diubah!\n";
    }
    pause();
}

void cariKategori(AlatMusik arr[], int jumlahData,
                  string kategori[], int jumlahKategori) {
    tampilKategori(kategori, jumlahKategori);

    string kategoriDicari;
    cout << "\n  Masukkan kategori: ";
    getline(cin, kategoriDicari);
    kategoriDicari = capitalize(kategoriDicari);

    bool ditemukan = false;
    for (int i = 0; i < jumlahData; i++) {
        if (arr[i].kategori == kategoriDicari) {
            if (!ditemukan) { cout << "\n"; cetakHeaderTabel(); ditemukan = true; }
            cetakBarisTabel(arr[i]);
        }
    }

    if (ditemukan) cetakGarisTabel();
    else cout << "\n  Tidak ada item di kategori \"" << kategoriDicari << "\".\n";
    pause();
}
void menuUser(AlatMusik arr[], int& jumlahData,
              string kategori[], int jumlahKategori,
              const string& namaUser) {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left
             << ("  MENU USER | " + namaUser)                 << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58)
             << "  1. Tampilkan Stok"                         << "||\n";
        cout << "||" << left << setw(58)
             << "  2. Cari Item Berdasarkan Kategori"          << "||\n";
        cout << "||" << left << setw(58)
             << "  3. Sorting Alat Musik"                     << "||\n";
        cout << "||" << left << setw(58)
             << "  4. Searching Alat Musik"                   << "||\n";
        cout << "||" << left << setw(58)
             << "  5. Logout"                                  << "||\n";
        cout << LANTAI << "\n\n";

        string pilihan;
        cout << "  Pilih menu (1-5): ";
        cin >> pilihan;
        cin.ignore();

        if      (pilihan == "1") { tampilStok(arr, jumlahData, false); pause(); }
        else if (pilihan == "2") { cariKategori(arr, jumlahData, kategori, jumlahKategori); }
        else if (pilihan == "3") { menuSorting(arr, jumlahData, false); }
        else if (pilihan == "4") { menuSearching(arr, jumlahData, false); }
        else if (pilihan == "5") {
            cout << "\n  Logout berhasil. Sampai jumpa Dan jangan kembali lagi WKKWKW " << namaUser << "!\n";
            pause();
            break;
        }
        else { cout << "\n  Pilihan tidak ada!\n"; pause(); }
    }
}
void menuAdmin(AlatMusik arr[], int& jumlahData,
               string kategori[], int jumlahKategori,
               const string& namaAdmin) {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left
             << ("  MENU ADMIN | " + namaAdmin)               << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58)
             << "  1. Tampilkan Stok"                         << "||\n";
        cout << "||" << left << setw(58)
             << "  2. Tambah Item Baru"                       << "||\n";
        cout << "||" << left << setw(58)
             << "  3. Ubah Stok Item"                         << "||\n";
        cout << "||" << left << setw(58)
             << "  4. Hapus Item"                             << "||\n";
        cout << "||" << left << setw(58)
             << "  5. Cari Item Berdasarkan Kategori"         << "||\n";
        cout << "||" << left << setw(58)
             << "  6. Ubah Harga Item"                        << "||\n";
        cout << "||" << left << setw(58)
             << "  7. Sorting Alat Musik"                     << "||\n";
        cout << "||" << left << setw(58)
             << "  8. Searching Alat Musik"                   << "||\n";
        cout << "||" << left << setw(58)
             << "  9. Logout"                                 << "||\n";
        cout << LANTAI << "\n\n";

        string pilihan;
        cout << "  Pilih menu (1-9): ";
        cin >> pilihan;
        cin.ignore();

        if      (pilihan == "1") { tampilStok(arr, jumlahData, true); pause(); }
        else if (pilihan == "2") { tambahItem(arr, jumlahData, kategori, jumlahKategori); }
        else if (pilihan == "3") { ubahStok(arr, jumlahData); }
        else if (pilihan == "4") { hapusItem(arr, jumlahData); }
        else if (pilihan == "5") { cariKategori(arr, jumlahData, kategori, jumlahKategori); }
        else if (pilihan == "6") { menuUbahHarga(arr, jumlahData); }
        else if (pilihan == "7") { menuSorting(arr, jumlahData, true); }
        else if (pilihan == "8") { menuSearching(arr, jumlahData, true); }
        else if (pilihan == "9") {
            cout << "\n  Logout berhasil. Sampai jumpa Dan janga Kembali lagi wkwkw " << namaAdmin << "!\n";
            pause();
            break;
        }
        else { cout << "\n  Pilihan tidak ada!\n"; pause(); }
    }
}

int main() {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left
             << "       SELAMAT DATANG DI TOKO ALAT MUSIK AA Clan"    << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58)
             << "  1. Login"                                   << "||\n";
        cout << "||" << left << setw(58)
             << "  2. Register Akun Baru"                      << "||\n";
        cout << "||" << left << setw(58)
             << "  3. Keluar"                                  << "||\n";
        cout << LANTAI << "\n\n";

        string pilihanUtama;
        cout << "  Pilih (1-3): ";
        cin >> pilihanUtama;
        cin.ignore();

        if (pilihanUtama == "3") {
            cout << "\n  Terima kasih telah mengunjungi Toko Alat Musik AA Clan\n\n";
            break;
        }
        else if (pilihanUtama == "2") {
            prosesRegister(daftarAkun, jumlahAkun);
        }
        else if (pilihanUtama == "1") {
            Akun* akunLogin = prosesLogin(daftarAkun, jumlahAkun);
            if (akunLogin == nullptr) continue;

            string roleAktif = (*akunLogin).role;
            string namaAktif = (*akunLogin).username;

            if (roleAktif == "admin")
                menuAdmin(stok, jumlahStok, daftarKategori, MAX_KAT, namaAktif);
            else if (roleAktif == "user")
                menuUser(stok, jumlahStok, daftarKategori, MAX_KAT, namaAktif);
        }
        else {
            cout << "\n  Pilihan tidak ada!\n";
            pause();
        }
    }

    return 0;
}