#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

//fuzzifikasi Input suhu
float suhuDingin(float suhu) {
  float uDingin;
  if (suhu <= 10) {
    uDingin = 1.0;
  } else if (suhu >= 10 && suhu <= 20) {
    uDingin = (20 - suhu) / 10;
  } else {
    uDingin = 0.0;
  }
  return uDingin;
}

float suhuHangat (float suhu) {
    float uHangat;
    if (suhu <= 15) {
        uHangat = 0.0;
    } else if (suhu >= 15 && suhu <= 22.5) {
        uHangat = (suhu - 15) / (22.5 - 15);
    } else if  (suhu >= 22.5 && suhu <= 30) {
        uHangat = (30-suhu) / (30 - 22.5);
    }
    else  {
      uHangat = 0.0;
    }

    return uHangat;
}

float suhuPanas(float suhu) {
  float uPanas;
  if (suhu <= 25) {
    uPanas = 0.0;
  } else if (suhu >= 25 && suhu <= 35) {
    uPanas = (suhu - 25) / (35 - 25);
  } else {
    uPanas = 1.0;
  }
  return uPanas;
}

//fuzzikasi Input jumlah orang
float jumlorangS(int orang) {
  float uorgsedikit;
  if (orang <= 15) {
    uorgsedikit = 1.0;
  } else if (orang >= 15 && orang <= 35) {
    uorgsedikit = (35 - orang) / 20.0;
  } else {
    uorgsedikit = 0.0;
  }
  return uorgsedikit;
}

float jumlorangB(int orang) {
  float uorgbanyak;
  if (orang <= 15) {
    uorgbanyak = 0.0;
  } else if (orang >= 15 && orang <= 35) {
    uorgbanyak = (orang - 15) / 20.0;
  } else {
    uorgbanyak = 1.0;
  }
  return uorgbanyak;
}

//fuzzifikasi sisi output 
float kecepatanPelan(float kecepatan) {
  float uPelan;
  if (kecepatan <= 0) {
    uPelan = 1.0;
  } else if (kecepatan >= 0 && kecepatan <= 200) {
    uPelan = (200 - kecepatan) / 200;
  } else {
    uPelan = 0.0;
  }
  return uPelan;
}

float kecepatanSedang(float kecepatan) {
  float uSedang;
  if (kecepatan <= 50) {
    uSedang = 0.0;
  } else if (kecepatan >= 50 && kecepatan <= 250) {
    uSedang = (kecepatan - 50) / (250 - 50);
  } else if (kecepatan >= 200 && kecepatan <= 450) {
    uSedang = (450 - kecepatan) / (450 - 250);
  } else {
    uSedang = 0.0;
  }
  return uSedang;
} 

float kecepatanCepat(float kecepatan) {
  float uCepat;
  if (kecepatan <= 300) {
    uCepat = 0.0;
  } else if (kecepatan >= 300 && kecepatan <= 500) {
    uCepat = (kecepatan - 300) / (500 - 300);
  } else {
    uCepat = 1.0;
  }
  return uCepat;
}

float agregasi(float a1, float a2, float a3, float a4, float a5, float a6, float kecepatan) {
    float c1, c2, c3, c4, c5, c6;
    float aggregationResult;
    c1 = min(a1, kecepatanPelan(kecepatan));
    c2 = min(a2, kecepatanPelan(kecepatan));
    c3 = min(a3, kecepatanSedang(kecepatan));
    c4 = min(a4, kecepatanSedang(kecepatan));
    c5 = min(a5, kecepatanCepat(kecepatan));
    c6 = min(a6, kecepatanCepat(kecepatan)); 

    aggregationResult =max({c1, c2, c3, c4, c5, c6});
    return aggregationResult;
}

//Penentuan Rule based antacedent dan consequence
int main() {
    float suhu, orang;
    float sumA = 0 , sumB = 0;
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

cout << "kecepatan"<<","<<"uHasil"<<endl;
for (int kecepatan = 0; kecepatan <= 500; kecepatan++) {
    float uHasil;
    uHasil = agregasi(a1, a2, a3, a4, a5, a6, kecepatan);
    sumA = sumA + (uHasil * kecepatan)*1;
    sumB = sumB + uHasil;
    cout << kecepatan << "," << uHasil << endl;
}
float zOutput = sumA / sumB;
cout << "Hasil Akhir: " << zOutput << endl;

return 0;
}