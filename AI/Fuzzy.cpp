#include <math.h>
#include <iostream>

using namespace std;

//fuzzifikasi Input suhu
float suhuDingin(float suhu) {
  float uDingin;
  if (suhu <= 10) {
    uDingin = 1;
  } else if (suhu > 10 && suhu <= 20) {
    uDingin = (20 - suhu) / 10;
  } else {
    uDingin = 0;
  }
  return uDingin;
}

float suhuHangat (float suhu) {
    float uHangat;
    if (suhu <= 15) {
        uHangat = 0;
    } else if (suhu >= 15 && suhu <= 22.5) {
        uHangat = (30 - suhu) / 15;
    } else {
        uHangat = 0;
    }
    return uHangat;
}

float suhuPanas(float suhu) {
  float uPanas;
  if (suhu >= 45) {
    uPanas = 1;
  } else if (suhu > 30 && suhu < 45) {
    uPanas = (suhu - 30) / 15;
  } else {
    uPanas = 0;
  }
  return uPanas;
}

//fuzzikasi Input jumlah orang
float jumlorangS(float orang) {
  float uorgsedikit;
  if (orang <= 15) {
    uorgsedikit = 1;
  } else if (orang > 15 && orang <= 35) {
    uorgsedikit = (35 - orang) / 20;
  } else {
    uorgsedikit = 0;
  }
  return uorgsedikit;
}

float jumlorangB(float orang) {
  float uorgbanyak;
  if (orang >= 45) {
    uorgbanyak = 1;
  } else if (orang > 35 && orang < 45) {
    uorgbanyak = (orang - 35) / 10;
  } else {
    uorgbanyak = 0;
  }
  return uorgbanyak;
}

//Penentuan Rule based antacedent dan consequence
int main() {
    float suhu, orang;
    cout << "Masukkan suhu: ";
    cin >> suhu;

    cout << "Masukkan jumlah orang: ";
    cin >> orang;   

//rule based antacedent
float a1 = max(suhuDingin(suhu), jumlorangS(orang));
float a2 = max(suhuDingin(suhu), jumlorangB(orang));
float a3 = max(suhuHangat(suhu), jumlorangS(orang));
float a4 = max(suhuHangat(suhu), jumlorangB(orang));
float a5 = max(suhuPanas(suhu), jumlorangS(orang));
float a6 = max(suhuPanas(suhu), jumlorangB(orang));

//rule based consequence
float z1 = 200 - 200 * a1;
float z2 = 200 - 200 * a2;
float z3 = 50 + 200 * a3;
float z4 = 450 - 200 * a4;   
float z5 = 300 + 200 * a5;   
float z6 = 300 + 200 * a6;

//defuzzifikasi 
float total = a1 + a2 + a3 + a4 + a5 + a6;
float zout = (total > 0)
  ? (a1 * z1 + a2 * z2 + a3 * z3 + a4 * z4 + a5 * z5 + a6 * z6) / total
  : 0;
cout << "Hasil defuzzifikasi: " << zout << endl;
return 0;
}




