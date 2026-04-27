#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>  

using namespace std;

#define MAX_STOK  100
#define MAX_KAT   4
#define MAX_AKUN  20


class TokoException : public exception {
protected:
    string pesan;
public:
    TokoException(const string& msg) : pesan(msg) {}
    const char* what() const noexcept override { return pesan.c_str(); }
};
class InputTidakValidException : public TokoException {
public:
    InputTidakValidException(const string& msg)
        : TokoException("[InputError] " + msg) {}
};
class KapasitasPenuhException : public TokoException {
public:
    KapasitasPenuhException(const string& msg)
        : TokoException("[KapasitasError] " + msg) {}
};
class DataTidakDitemukanException : public TokoException {
public:
    DataTidakDitemukanException(const string& msg)
        : TokoException("[NotFound] " + msg) {}
};
class AuthException : public TokoException {
public:
    AuthException(const string& msg)
        : TokoException("[AuthError] " + msg) {}
};
class KategoriTidakValidException : public TokoException {
public:
    KategoriTidakValidException(const string& msg)
        : TokoException("[KategoriError] " + msg) {}
};
class NilaiTidakValidException : public TokoException {
public:
    NilaiTidakValidException(const string& msg)
        : TokoException("[NilaiError] " + msg) {}
};

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
    {"admin123", "admin123", "admin"},
    {"user1",    "user111",  "user"},
    {"user2",    "user222",  "user"}
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
    if (!teks.empty() && teks[0] >= 'a' && teks[0] <= 'z')
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

bool usernameAda(Akun listAkun[], int jml, const string& u) {
    for (int i = 0; i < jml; i++)
        if (listAkun[i].username == u) return true;
    return false;
}
void validasiPanjang(const string& teks, int minPanjang, const string& namaField) {
    if ((int)teks.size() < minPanjang)
        throw InputTidakValidException(
            namaField + " minimal " + to_string(minPanjang) + " karakter.");
}
void validasiTidakKosong(const string& teks, const string& namaField) {
    if (teks.empty())
        throw InputTidakValidException(namaField + " tidak boleh kosong.");
}
void validasiPasswordKuat(const string& pw) {
    bool adaHuruf = false, adaAngka = false;
    for (char c : pw) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) adaHuruf = true;
        if (c >= '0' && c <= '9')                              adaAngka = true;
    }
    if (!adaHuruf || !adaAngka)
        throw InputTidakValidException(
            "Password harus mengandung huruf dan angka.");
}
void validasiPositif(int nilai, const string& namaField) {
    if (nilai <= 0)
        throw NilaiTidakValidException(
            namaField + " harus bernilai lebih dari 0.");
}
int bacaInteger(const string& prompt) {
    int nilai;
    cout << prompt;
    cin >> nilai;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        throw InputTidakValidException("Input harus berupa angka.");
    }
    cin.ignore();
    return nilai;
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

void tampilKategori(string kategori[], int jml) {
    cout << "\n  Kategori tersedia:\n";
    for (int i = 0; i < jml; i++)
        cout << "    - " << kategori[i] << "\n";
}

void tampilStok(AlatMusik arr[], int jumlah, bool adminMode) {
    if (adminMode) cetakJudul("Daftar Stok Alat Musik AA Clan [ADMIN]");
    else           cetakJudul("Daftar Stok Alat Musik AA Clan");

    if (jumlah == 0) { cout << "  (Belum ada data)\n"; return; }

    cetakHeaderTabel();
    for (int i = 0; i < jumlah; i++) cetakBarisTabel(arr[i]);
    cetakGarisTabel();
    cout << "  Total: " << jumlah << " item\n";
}

void sortNamaAscending(AlatMusik arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (toLower(arr[j].nama) > toLower(arr[j+1].nama)) {
                AlatMusik tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
}

void sortIdAscending(AlatMusik arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (arr[j].id > arr[j+1].id) {
                AlatMusik tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
}

void sortHargaDescending(AlatMusik arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (arr[j].harga < arr[j+1].harga) {
                AlatMusik tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
}

void sortStokAscending(AlatMusik arr[], int jumlah) {
    for (int i = 0; i < jumlah - 1; i++)
        for (int j = 0; j < jumlah - 1 - i; j++)
            if (arr[j].jumlah > arr[j+1].jumlah) {
                AlatMusik tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
}

void menuSorting(AlatMusik arr[], int jumlahData, bool adminMode) {
    AlatMusik temp[MAX_STOK];
    for (int i = 0; i < jumlahData; i++) temp[i] = arr[i];

    cetakJudul("Menu Sorting Alat Musik");
    cout << "||" << left << setw(58) << "  1. Nama   : A -> Z"             << "||\n";
    cout << "||" << left << setw(58) << "  2. Harga  : Mahal -> Murah"     << "||\n";
    cout << "||" << left << setw(58) << "  3. Stok   : Sedikit -> Banyak"  << "||\n";
    cout << "||" << left << setw(58) << "  4. Kembali"                     << "||\n";
    cout << LANTAI << "\n\n";

    try {
        string pilihan;
        cout << "  Pilih metode sorting (1-4): ";
        cin >> pilihan; cin.ignore();

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
            throw InputTidakValidException("Pilihan sorting harus 1-4.");
        }
    } catch (const TokoException& e) {
        cout << "\n  [!] " << e.what() << "\n";
    }
    pause();
}

int binarySearchById(AlatMusik arr[], int jumlah, int idDicari) {
    int low = 0, high = jumlah - 1, iterasi = 0;
    cout << "\n  Mencari ID: " << idDicari << "\n";
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
            cout << " --> cari ke KANAN\n"; low = mid + 1;
        } else {
            cout << " --> cari ke KIRI\n";  high = mid - 1;
        }
    }
    cout << "  ID tidak ditemukan setelah " << iterasi << " iterasi.\n";
    return -1;
}

void menuCariById(AlatMusik arr[], int jumlahData) {
    cetakJudul("Cari Alat Musik Berdasarkan ID");

    try {
        if (jumlahData == 0)
            throw DataTidakDitemukanException("Belum ada data stok.");

        AlatMusik temp[MAX_STOK];
        for (int i = 0; i < jumlahData; i++) temp[i] = arr[i];
        sortIdAscending(temp, jumlahData);

        cout << "  Data (diurutkan by ID untuk Binary Search):\n";
        cetakHeaderTabel();
        for (int i = 0; i < jumlahData; i++) cetakBarisTabel(temp[i]);
        cetakGarisTabel();

        int idDicari = bacaInteger("\n  Masukkan ID yang dicari: ");
        if (idDicari <= 0)
            throw NilaiTidakValidException("ID harus bernilai lebih dari 0.");

        int idx = binarySearchById(temp, jumlahData, idDicari);

        cout << "\n  " << string(54, '-') << "\n";
        if (idx == -1)
            throw DataTidakDitemukanException(
                "Item dengan ID " + to_string(idDicari) + " tidak ditemukan.");

        cout << "  HASIL — Item ditemukan:\n\n";
        cetakHeaderTabel();
        cetakBarisTabel(temp[idx]);
        cetakGarisTabel();
        cout << "  Metode: Binary Search | Kunci: ID\n";

    } catch (const TokoException& e) {
        cout << "\n  Upss.. " << e.what() << "\n";
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
             << (cocok ? " --> COCOK!" : "") << "\n";
        if (cocok) {
            if (!adaHasil) { cout << "\n  Hasil Pencarian:\n"; cetakHeaderTabel(); }
            cetakBarisTabel(arr[i]);
            adaHasil = true;
        }
    }

    if (adaHasil) {
        cetakGarisTabel();
    } else {
        throw DataTidakDitemukanException(
            "Tidak ada item dengan nama yang mengandung \"" + keyword + "\".");
    }

    cout << "  " << string(54, '-') << "\n";
    cout << "  Metode  : Sequential Search\n";
    cout << "  Iterasi : " << iterasi << " kali\n";
}

void menuCariByNama(AlatMusik arr[], int jumlahData) {
    cetakJudul("Cari Alat Musik Berdasarkan Nama");

    try {
        if (jumlahData == 0)
            throw DataTidakDitemukanException("Belum ada data stok.");

        cetakHeaderTabel();
        for (int i = 0; i < jumlahData; i++) cetakBarisTabel(arr[i]);
        cetakGarisTabel();

        string keyword;
        cout << "\n  Masukkan nama: ";
        getline(cin, keyword);

        validasiTidakKosong(keyword, "Keyword pencarian");

        sequentialSearchByNama(arr, jumlahData, keyword);

    } catch (const TokoException& e) {
        cout << "\n  Upss.. " << e.what() << "\n";
    }
    pause();
}

void menuSearching(AlatMusik arr[], int jumlahData, bool adminMode) {
    while (true) {
        cetakJudul("Menu Searching Alat Musik");
        cout << "||" << left << setw(58) << "  1. Cari Berdasarkan ID   (Binary Search)"     << "||\n";
        cout << "||" << left << setw(58) << "  2. Cari Berdasarkan Nama (Sequential Search)" << "||\n";
        cout << "||" << left << setw(58) << "  3. Kembali"                                   << "||\n";
        cout << LANTAI << "\n\n";

        try {
            string pilihan;
            cout << "  Pilih (1-3): ";
            cin >> pilihan; cin.ignore();

            if      (pilihan == "1") menuCariById(arr, jumlahData);
            else if (pilihan == "2") menuCariByNama(arr, jumlahData);
            else if (pilihan == "3") return;
            else throw InputTidakValidException("Pilihan harus 1-3.");

        } catch (const TokoException& e) {
            cout << "\n  Upss.. " << e.what() << "\n";
            pause();
        }
    }
}

bool prosesRegister(Akun listAkun[], int& jmlAkun) {
    cetakJudul("REGISTER - Buat Akun Baru");

    cout << "  Ketentuan akun:\n";
    cout << "    - Username minimal 4 karakter\n";
    cout << "    - Password minimal 6 karakter\n";
    cout << "    - Password harus mengandung huruf dan angka\n";
    cout << "    - Akun baru otomatis terdaftar sebagai User\n";
    cout << GARIS << "\n\n";

    try {
        if (jmlAkun >= MAX_AKUN)
            throw KapasitasPenuhException(
                "Kapasitas akun penuh (" + to_string(MAX_AKUN) + "). Tidak dapat mendaftar.");

        Akun akunBaru;
        while (true) {
            try {
                cout << "  Username baru  : ";
                getline(cin, akunBaru.username);
                validasiPanjang(akunBaru.username, 4, "Username");
                if (usernameAda(listAkun, jmlAkun, akunBaru.username))
                    throw InputTidakValidException(
                        "Username \"" + akunBaru.username + "\" sudah dipakai.");
                break;
            } catch (const InputTidakValidException& e) {
                cout << "  Upss.. " << e.what() << " Coba lagi.\n\n";
            }
        }
        string konfirmasi;
        while (true) {
            try {
                cout << "  Password baru  : ";
                getline(cin, akunBaru.password);
                validasiPanjang(akunBaru.password, 6, "Password");
                validasiPasswordKuat(akunBaru.password);
                cout << "  Konfirmasi pw  : ";
                getline(cin, konfirmasi);
                if (akunBaru.password != konfirmasi)
                    throw InputTidakValidException("Password tidak cocok.");
                break;
            } catch (const InputTidakValidException& e) {
                cout << "  Upss.. " << e.what() << " Ulangi.\n\n";
            }
        }

        akunBaru.role = "user";
        listAkun[jmlAkun] = akunBaru;
        jmlAkun++;

        cout << "\n   Alamat jumlahAkun : " << &jmlAkun
             << " | Nilai sekarang : " << jmlAkun << "\n";
        cout << "\n" << GARIS << "\n";
        cout << "  Registrasi berhasil!\n";
        cout << "  Username : " << akunBaru.username << "\n";
        cout << "  Role     : " << akunBaru.role << "\n";

    } catch (const KapasitasPenuhException& e) {
        cout << "\n  Upss.. " << e.what() << "\n";
        pause();
        return false;
    } catch (const TokoException& e) {
        // fallback
        cout << "\n  Ups.. " << e.what() << "\n";
        pause();
        return false;
    }

    pause();
    return true;
}

Akun* prosesLogin(Akun listAkun[], int jmlAkun) {
    cetakJudul("LOGIN - Toko Alat Musik AA Clan");

    string inputUsername, inputPassword;
    const int BATAS_COBA = 3;

    for (int percobaan = 1; percobaan <= BATAS_COBA; percobaan++) {
        try {
            cout << "  Username : ";
            getline(cin, inputUsername);
            cout << "  Password : ";
            getline(cin, inputPassword);

            // Validasi tidak kosong dulu
            validasiTidakKosong(inputUsername, "Username");
            validasiTidakKosong(inputPassword, "Password");

            // Cari akun
            for (int i = 0; i < jmlAkun; i++) {
                if (listAkun[i].username == inputUsername &&
                    listAkun[i].password == inputPassword) {
                    cout << "\n" << GARIS << "\n";
                    cout << "  Login berhasil! Selamat datang, "
                         << listAkun[i].username << ".\n";
                    cout << "  Role : " << listAkun[i].role << "\n";
                    pause();
                    return &listAkun[i];
                }
            }
            int sisa = BATAS_COBA - percobaan;
            if (sisa > 0)
                throw AuthException(
                    "Username atau password salah! Sisa percobaan: " + to_string(sisa));
            else
                throw AuthException("Username atau password salah! Tidak ada sisa percobaan.");

        } catch (const InputTidakValidException& e) {
            cout << "\n Upss.. " << e.what() << "\n\n";
            percobaan--;
        } catch (const AuthException& e) {
            cout << "\n  Upss.. " << e.what() << "\n\n";
        }
    }

    cout << "  Akun dikunci. Terlalu banyak percobaan login gagal.\n";
    pause();
    return nullptr;
}

void tambahItem(AlatMusik arr[], int& jumlahData,
                string kategori[], int jumlahKategori) {
    cetakJudul("Tambah Item Baru");

    try {
        if (jumlahData >= MAX_STOK)
            throw KapasitasPenuhException(
                "Maaf stok penuh! Maksimal " + to_string(MAX_STOK) + " item.");

        AlatMusik itemBaru;
        itemBaru.id = nextId(arr, jumlahData);

        cout << "  Nama alat musik : ";
        getline(cin, itemBaru.nama);
        validasiTidakKosong(itemBaru.nama, "Nama alat musik");

        itemBaru.harga  = bacaInteger("  Harga (Rp)      : ");
        validasiPositif(itemBaru.harga, "Harga");

        itemBaru.jumlah = bacaInteger("  Jumlah stok     : ");
        validasiPositif(itemBaru.jumlah, "Jumlah stok");

        tampilKategori(kategori, jumlahKategori);
        cout << "  Pilih kategori  : ";
        getline(cin, itemBaru.kategori);
        itemBaru.kategori = capitalize(itemBaru.kategori);

        if (!kategoriValid(itemBaru.kategori))
            throw KategoriTidakValidException(
                "Kategori \"" + itemBaru.kategori + "\" tidak valid.");

        arr[jumlahData] = itemBaru;
        jumlahData++;

        cout << "\n  Item \"" << itemBaru.nama
             << "\" berhasil ditambahkan (ID: " << itemBaru.id << ").\n";
        cout << "  Alamat jumlahData : " << &jumlahData
             << " | Nilai sekarang : " << jumlahData << "\n";

    } catch (const KapasitasPenuhException& e) {
        cout << "\n  Upss.. " << e.what() << "\n";
    } catch (const KategoriTidakValidException& e) {
        cout << "\n  Upss.. " << e.what() << "\n";
    } catch (const NilaiTidakValidException& e) {
        cout << "\n  Upss.. " << e.what() << "\n";
    } catch (const InputTidakValidException& e) {
        cout << "\n  Upss.." << e.what() << "\n";
    } catch (const TokoException& e) {
        cout << "\n  Upss.. " << e.what() << "\n";
    }
    pause();
}

void ubahStok(AlatMusik arr[], int jumlahData) {
    try {
        if (jumlahData == 0)
            throw DataTidakDitemukanException("Stok kosong! Tidak ada item.");

        tampilStok(arr, jumlahData, true);

        int idDicari = bacaInteger("\n  ID item yang ingin diubah stoknya: ");

        for (int i = 0; i < jumlahData; i++) {
            if (arr[i].id == idDicari) {
                int stokBaru = bacaInteger(
                    "  Stok baru untuk \"" + arr[i].nama +
                    "\" (saat ini: " + to_string(arr[i].jumlah) + "): ");
                if (stokBaru < 0)
                    throw NilaiTidakValidException("Stok tidak boleh negatif.");
                arr[i].jumlah = stokBaru;
                cout << "  Stok berhasil diubah!\n";
                pause();
                return;
            }
        }
        throw DataTidakDitemukanException(
            "ID " + to_string(idDicari) + " tidak ditemukan.");

    } catch (const TokoException& e) {
        cout << "\n  [!] " << e.what() << "\n";
        pause();
    }
}

void hapusItem(AlatMusik arr[], int& jumlahData) {
    try {
        if (jumlahData == 0)
            throw DataTidakDitemukanException("Stok kosong! Tidak ada item.");

        tampilStok(arr, jumlahData, true);

        string namaHapus;
        cout << "\n  Nama item yang ingin dihapus: ";
        getline(cin, namaHapus);
        validasiTidakKosong(namaHapus, "Nama item");

        for (int i = 0; i < jumlahData; i++) {
            if (toLower(arr[i].nama) == toLower(namaHapus)) {
                string namaSementara = arr[i].nama;
                for (int j = i; j < jumlahData - 1; j++)
                    arr[j] = arr[j + 1];
                jumlahData--;
                cout << "  Item \"" << namaSementara << "\" berhasil dihapus!\n";
                cout << "   Alamat jumlahData : " << &jumlahData
                     << " | Nilai sekarang : " << jumlahData << "\n";
                pause();
                return;
            }
        }
        throw DataTidakDitemukanException(
            "Item dengan nama \"" + namaHapus + "\" tidak ditemukan.");

    } catch (const TokoException& e) {
        cout << "\n  Upss.. " << e.what() << "\n";
        pause();
    }
}

void ubahHargaViaPointer(int* ptrHarga, const string& namaItem) {
    cout << "  Harga saat ini \"" << namaItem << "\": Rp " << *ptrHarga << "\n";
    int hargaBaru = bacaInteger("  Harga baru (Rp)  : ");
    validasiPositif(hargaBaru, "Harga");
    *ptrHarga = hargaBaru;
    cout << "  Alamat harga : " << ptrHarga
         << " | Nilai baru : Rp " << *ptrHarga << "\n";
}

AlatMusik* cariItemById(AlatMusik arr[], int jumlahData, int idDicari) {
    for (int i = 0; i < jumlahData; i++)
        if (arr[i].id == idDicari) return &arr[i];
    return nullptr;
}

void menuUbahHarga(AlatMusik arr[], int jumlahData) {
    try {
        if (jumlahData == 0)
            throw DataTidakDitemukanException("Stok kosong! Tidak ada item.");

        tampilStok(arr, jumlahData, true);

        int idDicari = bacaInteger("\n  ID item yang ingin diubah harganya: ");

        AlatMusik* ptrItem = cariItemById(arr, jumlahData, idDicari);
        if (ptrItem == nullptr)
            throw DataTidakDitemukanException(
                "ID " + to_string(idDicari) + " tidak ditemukan.");

        cout << "\n  Item ditemukan:\n";
        cetakHeaderTabel();
        cetakBarisTabel(*ptrItem);
        cetakGarisTabel();
        cout << "   Alamat item : " << ptrItem << "\n\n";

        ubahHargaViaPointer(&ptrItem->harga, ptrItem->nama);
        cout << "\n  Harga berhasil diubah!\n";

    } catch (const NilaiTidakValidException& e) {
        cout << "\n Uoss.. " << e.what() << "\n";
    } catch (const TokoException& e) {
        cout << "\n Ups.." << e.what() << "\n";
    }
    pause();
}

void cariKategori(AlatMusik arr[], int jumlahData,
                  string kategori[], int jumlahKategori) {
    try {
        tampilKategori(kategori, jumlahKategori);

        string kategoriDicari;
        cout << "\n  Masukkan kategori: ";
        getline(cin, kategoriDicari);
        validasiTidakKosong(kategoriDicari, "Kategori");

        kategoriDicari = capitalize(kategoriDicari);

        if (!kategoriValid(kategoriDicari))
            throw KategoriTidakValidException(
                "Kategori \"" + kategoriDicari + "\" tidak ada dalam daftar.");

        bool ditemukan = false;
        for (int i = 0; i < jumlahData; i++) {
            if (arr[i].kategori == kategoriDicari) {
                if (!ditemukan) { cout << "\n"; cetakHeaderTabel(); ditemukan = true; }
                cetakBarisTabel(arr[i]);
            }
        }

        if (ditemukan) {
            cetakGarisTabel();
        } else {
            throw DataTidakDitemukanException(
                "Tidak ada item di kategori \"" + kategoriDicari + "\".");
        }

    } catch (const TokoException& e) {
        cout << "\n  Ups.." << e.what() << "\n";
    }
    pause();
}

void menuUser(AlatMusik arr[], int& jumlahData,
              string kategori[], int jumlahKategori,
              const string& namaUser) {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left << ("  MENU USER | " + namaUser)      << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58) << "  1. Tampilkan Stok"              << "||\n";
        cout << "||" << left << setw(58) << "  2. Cari Item Berdasarkan Kategori" << "||\n";
        cout << "||" << left << setw(58) << "  3. Sorting Alat Musik"          << "||\n";
        cout << "||" << left << setw(58) << "  4. Searching Alat Musik"        << "||\n";
        cout << "||" << left << setw(58) << "  5. Logout"                      << "||\n";
        cout << LANTAI << "\n\n";

        try {
            string pilihan;
            cout << "  Pilih menu (1-5): ";
            cin >> pilihan; cin.ignore();

            if      (pilihan == "1") { tampilStok(arr, jumlahData, false); pause(); }
            else if (pilihan == "2") cariKategori(arr, jumlahData, kategori, jumlahKategori);
            else if (pilihan == "3") menuSorting(arr, jumlahData, false);
            else if (pilihan == "4") menuSearching(arr, jumlahData, false);
            else if (pilihan == "5") {
                cout << "\n  Logout berhasil. Sampai jumpa, " << namaUser << "!\n";
                pause();
                break;
            }
            else throw InputTidakValidException("Pilihan menu harus 1-5.");

        } catch (const TokoException& e) {
            cout << "\n  [Upss.. " << e.what() << "\n";
            pause();
        }
    }
}
void menuAdmin(AlatMusik arr[], int& jumlahData,
               string kategori[], int jumlahKategori,
               const string& namaAdmin) {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left << ("  MENU ADMIN | " + namaAdmin)    << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58) << "  1. Tampilkan Stok"              << "||\n";
        cout << "||" << left << setw(58) << "  2. Tambah Item Baru"            << "||\n";
        cout << "||" << left << setw(58) << "  3. Ubah Stok Item"              << "||\n";
        cout << "||" << left << setw(58) << "  4. Hapus Item"                  << "||\n";
        cout << "||" << left << setw(58) << "  5. Cari Item Berdasarkan Kategori" << "||\n";
        cout << "||" << left << setw(58) << "  6. Ubah Harga Item"             << "||\n";
        cout << "||" << left << setw(58) << "  7. Sorting Alat Musik"          << "||\n";
        cout << "||" << left << setw(58) << "  8. Searching Alat Musik"        << "||\n";
        cout << "||" << left << setw(58) << "  9. Logout"                      << "||\n";
        cout << LANTAI << "\n\n";

        try {
            string pilihan;
            cout << "  Pilih menu (1-9): ";
            cin >> pilihan; cin.ignore();

            if      (pilihan == "1") { tampilStok(arr, jumlahData, true); pause(); }
            else if (pilihan == "2") tambahItem(arr, jumlahData, kategori, jumlahKategori);
            else if (pilihan == "3") ubahStok(arr, jumlahData);
            else if (pilihan == "4") hapusItem(arr, jumlahData);
            else if (pilihan == "5") cariKategori(arr, jumlahData, kategori, jumlahKategori);
            else if (pilihan == "6") menuUbahHarga(arr, jumlahData);
            else if (pilihan == "7") menuSorting(arr, jumlahData, true);
            else if (pilihan == "8") menuSearching(arr, jumlahData, true);
            else if (pilihan == "9") {
                cout << "\n  Logout berhasil. Sampai jumpa, " << namaAdmin << "!\n";
                pause();
                break;
            }
            else throw InputTidakValidException("Pilihan menu harus 1-9.");

        } catch (const TokoException& e) {
            cout << "\n  Ups.. " << e.what() << "\n";
            pause();
        }
    }
}


int main() {
    while (true) {
        cls();
        cout << ATAP << "\n";
        cout << "||" << setw(58) << left
             << "       SELAMAT DATANG DI TOKO ALAT MUSIK AA Clan" << "||\n";
        cout << SPASI << "\n";
        cout << "||" << left << setw(58) << "  1. Login"              << "||\n";
        cout << "||" << left << setw(58) << "  2. Register Akun Baru" << "||\n";
        cout << "||" << left << setw(58) << "  3. Keluar"             << "||\n";
        cout << LANTAI << "\n\n";

        try {
            string pilihanUtama;
            cout << "  Pilih (1-3): ";
            cin >> pilihanUtama; cin.ignore();

            if (pilihanUtama == "3") {
                cout << "\n  Terima kasih telah mengunjungi Toko Alat Musik AA Clan\n\n";
                break;
            } else if (pilihanUtama == "2") {
                prosesRegister(daftarAkun, jumlahAkun);
            } else if (pilihanUtama == "1") {
                Akun* akunLogin = prosesLogin(daftarAkun, jumlahAkun);
                if (akunLogin == nullptr) continue;

                string roleAktif = akunLogin->role;
                string namaAktif = akunLogin->username;

                if (roleAktif == "admin")
                    menuAdmin(stok, jumlahStok, daftarKategori, MAX_KAT, namaAktif);
                else
                    menuUser(stok, jumlahStok, daftarKategori, MAX_KAT, namaAktif);
            } else {
                throw InputTidakValidException("Pilihan menu utama harus 1, 2, atau 3.");
            }

        } catch (const TokoException& e) {
            cout << "\n  Upss.. " << e.what() << "\n";
            pause();
        } catch (const exception& e) {
            cout << "\n   Terjadi kesalahan sistem: " << e.what() << "\n";
            pause();
        }
    }

    return 0;
} 