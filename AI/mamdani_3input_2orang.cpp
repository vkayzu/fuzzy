// Fuzzy Mamdani 3 input
// Input 1 : Suhu (C)           -> Dingin, Hangat, Panas
// Input 2 : Jumlah orang       -> Sedikit, Banyak
// Input 3 : Kelembapan (%)     -> Kering, Lembab
// Output  : Kecepatan kipas    -> Pelan, Sedang, Cepat  (0 - 500)
// Total rule = 3 x 2 x 2 = 12 rule

#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

// ================= Fuzzifikasi input suhu =================
float suhuDingin(float suhu) {
  if (suhu <= 10) return 1.0;
  else if (suhu <= 20) return (20 - suhu) / 10.0;
  else return 0.0;
}

float suhuHangat(float suhu) {
  if (suhu <= 15) return 0.0;
  else if (suhu <= 22.5) return (suhu - 15) / (22.5 - 15);
  else if (suhu <= 30) return (30 - suhu) / (30 - 22.5);
  else return 0.0;
}

float suhuPanas(float suhu) {
  if (suhu <= 25) return 0.0;
  else if (suhu <= 35) return (suhu - 25) / (35 - 25);
  else return 1.0;
}

// ============ Fuzzifikasi input jumlah orang (2 himpunan) ============
float orangSedikit(float orang) {
  if (orang <= 15) return 1.0;
  else if (orang <= 35) return (35 - orang) / 20.0;
  else return 0.0;
}

float orangBanyak(float orang) {
  if (orang <= 15) return 0.0;
  else if (orang <= 35) return (orang - 15) / 20.0;
  else return 1.0;
}

// ================= Fuzzifikasi input kelembapan =================
float lembabKering(float rh) {
  if (rh <= 40) return 1.0;
  else if (rh <= 70) return (70 - rh) / 30.0;
  else return 0.0;
}

float lembabLembab(float rh) {
  if (rh <= 40) return 0.0;
  else if (rh <= 70) return (rh - 40) / 30.0;
  else return 1.0;
}

// ================= Himpunan output kecepatan =================
float kecepatanPelan(float k) {
  if (k <= 0) return 1.0;
  else if (k <= 200) return (200 - k) / 200.0;
  else return 0.0;
}

float kecepatanSedang(float k) {
  if (k <= 50) return 0.0;
  else if (k <= 250) return (k - 50) / (250.0 - 50);
  else if (k <= 450) return (450 - k) / (450.0 - 250);
  else return 0.0;
}

float kecepatanCepat(float k) {
  if (k <= 300) return 0.0;
  else if (k <= 500) return (k - 300) / (500.0 - 300);
  else return 1.0;
}

// ================= Rule base =================
// 0 = Pelan, 1 = Sedang, 2 = Cepat
const int JUMLAH_RULE = 12;
const char* namaOutput[] = {"Pelan", "Sedang", "Cepat"};

//  No | Suhu   | Orang   | Kelembapan | Kecepatan
//  R1 | Dingin | Sedikit | Kering     | Pelan
//  R2 | Dingin | Sedikit | Lembab     | Pelan
//  R3 | Dingin | Banyak  | Kering     | Pelan
//  R4 | Dingin | Banyak  | Lembab     | Sedang
//  R5 | Hangat | Sedikit | Kering     | Pelan
//  R6 | Hangat | Sedikit | Lembab     | Sedang
//  R7 | Hangat | Banyak  | Kering     | Sedang
//  R8 | Hangat | Banyak  | Lembab     | Cepat
//  R9 | Panas  | Sedikit | Kering     | Sedang
// R10 | Panas  | Sedikit | Lembab     | Cepat
// R11 | Panas  | Banyak  | Kering     | Cepat
// R12 | Panas  | Banyak  | Lembab     | Cepat
const int konsekuen[JUMLAH_RULE] = {0, 0, 0, 1, 0, 1, 1, 2, 1, 2, 2, 2};

float derajatOutput(int himpunan, float k) {
  if (himpunan == 0) return kecepatanPelan(k);
  if (himpunan == 1) return kecepatanSedang(k);
  return kecepatanCepat(k);
}

// Implikasi (MIN) tiap rule lalu agregasi (MAX)
float agregasi(const float alpha[], float k) {
  float hasil = 0.0;
  for (int i = 0; i < JUMLAH_RULE; i++) {
    float c = min(alpha[i], derajatOutput(konsekuen[i], k));
    hasil = max(hasil, c);
  }
  return hasil;
}

int main() {
  float suhu, orang, rh;
  cout << "Masukkan suhu (C): ";
  cin >> suhu;
  cout << "Masukkan jumlah orang: ";
  cin >> orang;
  cout << "Masukkan kelembapan (%): ";
  cin >> rh;

  // Fuzzifikasi
  float uSuhu[3]  = {suhuDingin(suhu), suhuHangat(suhu), suhuPanas(suhu)};
  float uOrang[2] = {orangSedikit(orang), orangBanyak(orang)};
  float uRH[2]    = {lembabKering(rh), lembabLembab(rh)};

  cout << "\n--- Fuzzifikasi ---" << endl;
  cout << "Suhu      : Dingin=" << uSuhu[0] << " Hangat=" << uSuhu[1] << " Panas=" << uSuhu[2] << endl;
  cout << "Orang     : Sedikit=" << uOrang[0] << " Banyak=" << uOrang[1] << endl;
  cout << "Kelembapan: Kering=" << uRH[0] << " Lembab=" << uRH[1] << endl;

  // Inferensi: alpha-predikat tiap rule (operator AND = MIN)
  float alpha[JUMLAH_RULE];
  int r = 0;
  cout << "\n--- Alpha predikat ---" << endl;
  for (int s = 0; s < 3; s++) {
    for (int o = 0; o < 2; o++) {
      for (int h = 0; h < 2; h++) {
        alpha[r] = min({uSuhu[s], uOrang[o], uRH[h]});
        cout << "R" << r + 1 << " (" << namaOutput[konsekuen[r]] << ") = " << alpha[r] << endl;
        r++;
      }
    }
  }

  // Defuzzifikasi centroid (diskrit)
  float sumA = 0, sumB = 0;
  cout << "\nkecepatan,uHasil" << endl;
  for (int k = 0; k <= 500; k++) {
    float uHasil = agregasi(alpha, k);
    sumA += uHasil * k;
    sumB += uHasil;
    cout << k << "," << uHasil << endl;
  }

  if (sumB == 0) {
    cout << "Tidak ada rule yang aktif." << endl;
    return 0;
  }
  float zOutput = sumA / sumB;
  cout << "Hasil Akhir (kecepatan): " << zOutput << endl;
  return 0;
}
