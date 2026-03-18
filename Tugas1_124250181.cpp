#include <iostream>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

struct Produk {
    char nama[50];
    float harga;
    char kategori[30];
    int stok;
};

Produk arr[100];
int n = 0;

void garis() {
    cout << "========================================\n";
}

void loadFile() {
    FILE *file = fopen("lelele.csv", "r");
    if (file == NULL) return;

    n = 0;
    while (fscanf(file, " %[^,],%f,%[^,],%d\n",
        arr[n].nama,
        &arr[n].harga,
        arr[n].kategori,
        &arr[n].stok) != EOF) {
        n++;
    }
    fclose(file);
}

void saveFile() {
    FILE *file = fopen("lelele.csv", "w");
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s,%.1f,%s,%d\n",
            arr[i].nama,
            arr[i].harga,
            arr[i].kategori,
            arr[i].stok);
    }
    fclose(file);
}

void tambahProduk() {
    if (n >= 100) {
        cout << "Kapasitas data penuh.\n";
        return;
    }

    cin.ignore();
    cout << "\n=== Tambah Produk ===\n";

    cout << "Nama Produk : ";
    cin.getline(arr[n].nama, 50);

    cout << "Harga       : ";
    cin >> arr[n].harga;

    while (true) {
        cout << "Kategori (makanan/minuman): ";
        cin >> arr[n].kategori;

        if (strcmp(arr[n].kategori, "makanan") == 0 ||
            strcmp(arr[n].kategori, "minuman") == 0) {
            break;
        } else {
            cout << "Kategori tidak valid. Silakan ulangi.\n";
        }
    }

    cout << "Stok        : ";
    cin >> arr[n].stok;

    n++;
    saveFile();

    cout << "Data produk berhasil ditambahkan.\n";
}

void tampil() {
    if (n == 0) {
        cout << "Data produk masih kosong.\n";
        return;
    }

    garis();
    cout << left << setw(5) << "No"
         << setw(20) << "Nama"
         << setw(10) << "Harga"
         << setw(15) << "Kategori"
         << setw(5) << "Stok" << endl;
    garis();

    for (int i = 0; i < n; i++) {
        cout << left << setw(5) << i+1
             << setw(20) << arr[i].nama
             << setw(10) << fixed << setprecision(1) << arr[i].harga
             << setw(15) << arr[i].kategori
             << setw(5) << arr[i].stok << endl;
    }
    garis();
}

void bubbleSort() {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].nama, arr[j+1].nama) > 0) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
    cout << "Data berhasil diurutkan berdasarkan nama (A-Z).\n";
}

void quickSort(int low, int high) {
    int i = low, j = high;
    float pivot = arr[(low+high)/2].harga;

    while (i <= j) {
        while (arr[i].harga > pivot) i++;   // DESC
        while (arr[j].harga < pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++; j--;
        }
    }

    if (low < j) quickSort(low, j);
    if (i < high) quickSort(i, high);
}

void sequentialSearch(char cari[]) {
    bool found = false;

    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].nama, cari) == 0) {
            garis();
            cout << "Data produk ditemukan:\n";
            cout << "Nama     : " << arr[i].nama << endl;
            cout << "Harga    : " << arr[i].harga << endl;
            cout << "Kategori : " << arr[i].kategori << endl;
            cout << "Stok     : " << arr[i].stok << endl;
            garis();
            found = true;
        }
    }

    if (!found) {
        cout << "Data produk tidak ditemukan.\n";
    }
}

void binarySearch(char cari[]) {
    int l = 0, r = n - 1;

    while (l <= r) {
        int mid = (l + r) / 2;
        int cmp = strcmp(arr[mid].nama, cari);

        if (cmp == 0) {
            garis();
            cout << "Data produk ditemukan:\n";
            cout << "Nama     : " << arr[mid].nama << endl;
            cout << "Harga    : " << arr[mid].harga << endl;
            cout << "Kategori : " << arr[mid].kategori << endl;
            cout << "Stok     : " << arr[mid].stok << endl;
            garis();
            return;
        } else if (cmp < 0) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << "Data produk tidak ditemukan.\n";
}

void menu() {
    cout << "==============================\n";
    cout << "           MENU\n";
    cout << "==============================\n";
    cout << "1. Tambah Produk\n";
    cout << "2. Tampilkan Produk\n";
    cout << "3. Sort Nama (Bubble)\n";
    cout << "4. Sort Harga (Quick)\n";
    cout << "5. Search Sequential\n";
    cout << "6. Search Binary\n";
    cout << "0. Keluar\n";
    cout << "==============================\n";
    cout << "Pilih: ";
}

int main() {
    int pilih;
    char cari[50];

    loadFile();

    do {
        menu();
        cin >> pilih;

        switch (pilih) {
        case 1:
            tambahProduk();
            break;

        case 2:
            tampil();
            break;

        case 3:
            bubbleSort();
            tampil();
            break;

        case 4:
            quickSort(0, n-1);
            cout << "Data berhasil diurutkan berdasarkan harga (tertinggi ke terendah).\n";
            tampil();
            break;

        case 5:
            cin.ignore();
            cout << "Masukkan nama produk: ";
            cin.getline(cari, 50);
            sequentialSearch(cari);
            break;

        case 6:
            cin.ignore();
            cout << "Masukkan nama produk: ";
            cin.getline(cari, 50);
            bubbleSort();
            binarySearch(cari);
            break;

        case 0:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }

    } while (pilih != 0);

    return 0;
}
