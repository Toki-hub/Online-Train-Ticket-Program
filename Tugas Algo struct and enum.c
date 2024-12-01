#include <stdio.h>
#include <string.h>

enum Hari { MINGGU, SENIN, SELASA, RABU, KAMIS, JUMAT, SABTU };
enum KelasKereta { EKONOMI, EKSEKUTIF };

struct Jadwal {
    char waktu[20];
};

struct Tanggal {
    int tanggal, bulan, tahun;
    enum Hari hari;
};

struct Tiket {
    char asal[30];
    char tujuan[30];
    struct Jadwal jadwalBerangkat;
    struct Jadwal jadwalPulang;
    struct Tanggal tanggalBerangkat;
    struct Tanggal tanggalPulang;
    enum KelasKereta kelas;
    double harga;
    int pulangPergi; // 0 untuk sekali jalan, 1 untuk pulang-pergi
};

// Fungsi untuk mendapatkan nama hari dari enum Hari
const char* getNamaHari(enum Hari hari) {
    const char* namaHari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    return namaHari[hari];
}

// Fungsi untuk menghitung harga tiket
double hitungHarga(enum KelasKereta kelas, double baseHarga, int pulangPergi) {
    double total = (kelas == EKSEKUTIF) ? baseHarga * 1.3 : baseHarga;
    if (pulangPergi) {
        total *= 2;
    }
    return total;
}

// Fungsi untuk menampilkan jadwal berdasarkan rute
void tampilkanJadwal(const char* asal, const char* tujuan) {
    printf("Pilih jadwal keberangkatan:\n");
    if (strcmp(asal, "Bandung") == 0 && strcmp(tujuan, "Jakarta") == 0) {
        printf("1. 07.00-09.50\n");
        printf("2. 11.00-13.50\n");
        printf("3. 14.00-16.50\n");
        printf("4. 20.00-22.50\n");
    } else if (strcmp(asal, "Jakarta") == 0 && strcmp(tujuan, "Bandung") == 0) {
        printf("1. 08.00-10.50\n");
        printf("2. 12.00-14.50\n");
        printf("3. 13.00-15.50\n");
        printf("4. 19.00-21.50\n");
    } else if (strcmp(asal, "Bandung") == 0 && strcmp(tujuan, "Yogyakarta") == 0) {
        printf("1. 07.00-14.30\n");
        printf("2. 16.30-24.00\n");
    } else if (strcmp(asal, "Yogyakarta") == 0 && strcmp(tujuan, "Bandung") == 0) {
        printf("1. 08.00-15.30\n");
        printf("2. 15.30-22.30\n");
    }
}

void pilihJadwal(struct Jadwal* jadwal, const char* asal, const char* tujuan) {
    tampilkanJadwal(asal, tujuan);
    int pilihan;
    printf("Masukkan pilihan jadwal: ");
    scanf("%d", &pilihan);
    
    if (strcmp(asal, "Bandung") == 0 && strcmp(tujuan, "Jakarta") == 0) {
        if (pilihan == 1) strcpy(jadwal->waktu, "07.00-09.50");
        else if (pilihan == 2) strcpy(jadwal->waktu, "11.00-13.50");
        else if (pilihan == 3) strcpy(jadwal->waktu, "14.00-16.50");
        else strcpy(jadwal->waktu, "20.00-22.50");
    } else if (strcmp(asal, "Jakarta") == 0 && strcmp(tujuan, "Bandung") == 0) {
        if (pilihan == 1) strcpy(jadwal->waktu, "08.00-10.50");
        else if (pilihan == 2) strcpy(jadwal->waktu, "12.00-14.50");
        else if (pilihan == 3) strcpy(jadwal->waktu, "13.00-15.50");
        else strcpy(jadwal->waktu, "19.00-21.50");
    } else if (strcmp(asal, "Bandung") == 0 && strcmp(tujuan, "Yogyakarta") == 0) {
        if (pilihan == 1) strcpy(jadwal->waktu, "07.00-14.30");
        else strcpy(jadwal->waktu, "16.30-24.00");
    } else if (strcmp(asal, "Yogyakarta") == 0 && strcmp(tujuan, "Bandung") == 0) {
        if (pilihan == 1) strcpy(jadwal->waktu, "08.00-15.30");
        else strcpy(jadwal->waktu, "15.30-22.30");
    }
}

void pilihTanggal(struct Tanggal* tanggal) {
    printf("Masukkan tanggal (DD MM YYYY): ");
    scanf("%d %d %d", &tanggal->tanggal, &tanggal->bulan, &tanggal->tahun);
    printf("Masukkan hari (0=Minggu, 1=Senin, ... , 6=Sabtu): ");
    int hari;
    scanf("%d", &hari);
    tanggal->hari = (enum Hari)hari;
}

int main() {
    struct Tiket tiket;
    double baseHarga = 0; 
    
    puts("Selamat Datang di Pemesanan Tiket Kereta Api\n");

    // Pilihan destinasi terbatas
    printf("Pilihan kota: Bandung, Jakarta, Yogyakarta\n");

    printf("Masukkan kota asal: ");
    scanf("%s", tiket.asal);
    printf("Masukkan kota tujuan: ");
    scanf("%s", tiket.tujuan);

    if ((strcmp(tiket.asal, "Bandung") == 0 && strcmp(tiket.tujuan, "Jakarta") == 0) ||
        (strcmp(tiket.asal, "Jakarta") == 0 && strcmp(tiket.tujuan, "Bandung") == 0)) {
        baseHarga = 150000;
    } else if ((strcmp(tiket.asal, "Bandung") == 0 && strcmp(tiket.tujuan, "Yogyakarta") == 0) ||
               (strcmp(tiket.asal, "Yogyakarta") == 0 && strcmp(tiket.tujuan, "Bandung") == 0)) {
        baseHarga = 300000;
    } else {
        printf("Rute tidak tersedia!\n");
        return 1;
    }

    pilihJadwal(&tiket.jadwalBerangkat, tiket.asal, tiket.tujuan);
    pilihTanggal(&tiket.tanggalBerangkat);

    printf("Pilih kelas kereta (0=Ekonomi, 1=Eksekutif): ");
    int kelasIndex;
    scanf("%d", &kelasIndex);
    tiket.kelas = (enum KelasKereta)kelasIndex;

    printf("Apakah pulang-pergi? (0=Tidak, 1=Ya): ");
    scanf("%d", &tiket.pulangPergi);

    if (tiket.pulangPergi) {
        pilihJadwal(&tiket.jadwalPulang, tiket.tujuan, tiket.asal);
        pilihTanggal(&tiket.tanggalPulang);
    }

    tiket.harga = hitungHarga(tiket.kelas, baseHarga, tiket.pulangPergi);

    printf("\nDetail Tiket Anda:\n");
printf("%-20s: %s\n", "Asal", tiket.asal);
printf("%-20s: %s\n", "Tujuan", tiket.tujuan);
printf("%-20s: %02d/%02d/%04d (%s)\n", "Tanggal Berangkat", tiket.tanggalBerangkat.tanggal,
       tiket.tanggalBerangkat.bulan, tiket.tanggalBerangkat.tahun,
       getNamaHari(tiket.tanggalBerangkat.hari));
printf("%-20s: %s\n", "Jadwal Keberangkatan", tiket.jadwalBerangkat.waktu);

if (tiket.pulangPergi) {
    printf("%-20s: %02d/%02d/%04d (%s)\n", "Tanggal Pulang", tiket.tanggalPulang.tanggal,
           tiket.tanggalPulang.bulan, tiket.tanggalPulang.tahun,
           getNamaHari(tiket.tanggalPulang.hari));
    printf("%-20s: %s\n", "Jadwal Pulang", tiket.jadwalPulang.waktu);
}

printf("%-20s: %s\n", "Kelas Kereta", tiket.kelas == EKONOMI ? "Ekonomi" : "Eksekutif");
printf("%-20s: %.2f\n", "Harga Tiket", tiket.harga);


    return 0;
}
