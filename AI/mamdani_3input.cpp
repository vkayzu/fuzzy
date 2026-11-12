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

// TAMBAHAN: orang sedang (segitiga 15 - 25 - 35)
float jumlorangSd(int orang) {
  float uorgsedang;
  if (orang <= 15) {
    uorgsedang = 0.0;
  } else if (orang >= 15 && orang <= 25) {
    uorgsedang = (orang - 15) / 10.0;
  } else if (orang >= 25 && orang <= 35) {
    uorgsedang = (35 - orang) / 10.0;
  } else {
    uorgsedang = 0.0;
  }
  return uorgsedang;
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

// TAMBAHAN: fuzzifikasi Input kelembapan (%RH)
float lembapKering(float rh) {
  float uKering;
  if (rh <= 30) {
    uKering = 1.0;
  } else if (rh >= 30 && rh <= 50) {
    uKering = (50 - rh) / 20.0;
  } else {
    uKering = 0.0;
  }
  return uKering;
}

float lembapNormal(float rh) {
  float uNormal;
  if (rh <= 30) {
    uNormal = 0.0;
  } else if (rh >= 30 && rh <= 50) {
    uNormal = (rh - 30) / 20.0;
  } else if (rh >= 50 && rh <= 70) {
    uNormal = (70 - rh) / 20.0;
  } else {
    uNormal = 0.0;
  }
  return uNormal;
}

float lembapBasah(float rh) {
  float uBasah;
  if (rh <= 50) {
    uBasah = 0.0;
  } else if (rh >= 50 && rh <= 70) {
    uBasah = (rh - 50) / 20.0;
  } else {
    uBasah = 1.0;
  }
  return uBasah;
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
  } else if (kecepatan >= 250 && kecepatan <= 450) {
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

float agregasi(float a1,  float a2,  float a3,  float a4,  float a5,  float a6,
               float a7,  float a8,  float a9,  float a10, float a11, float a12,
               float a13, float a14, float a15, float a16, float a17, float a18,
               float a19, float a20, float a21, float a22, float a23, float a24,
               float a25, float a26, float a27, float kecepatan) {
    float c1, c2, c3, c4, c5, c6, c7, c8, c9;
    float c10, c11, c12, c13, c14, c15, c16, c17, c18;
    float c19, c20, c21, c22, c23, c24, c25, c26, c27;
    float aggregationResult;

    // suhu dingin
    c1  = min(a1,  kecepatanPelan(kecepatan));
    c2  = min(a2,  kecepatanPelan(kecepatan));
    c3  = min(a3,  kecepatanSedang(kecepatan));
    c4  = min(a4,  kecepatanPelan(kecepatan));
    c5  = min(a5,  kecepatanPelan(kecepatan));
    c6  = min(a6,  kecepatanSedang(kecepatan));
    c7  = min(a7,  kecepatanPelan(kecepatan));
    c8  = min(a8,  kecepatanPelan(kecepatan));
    c9  = min(a9,  kecepatanSedang(kecepatan));

    // suhu hangat
    c10 = min(a10, kecepatanSedang(kecepatan));
    c11 = min(a11, kecepatanSedang(kecepatan));
    c12 = min(a12, kecepatanCepat(kecepatan));
    c13 = min(a13, kecepatanSedang(kecepatan));
    c14 = min(a14, kecepatanSedang(kecepatan));
    c15 = min(a15, kecepatanCepat(kecepatan));
    c16 = min(a16, kecepatanSedang(kecepatan));
    c17 = min(a17, kecepatanSedang(kecepatan));
    c18 = min(a18, kecepatanCepat(kecepatan));

    // suhu panas
    c19 = min(a19, kecepatanCepat(kecepatan));
    c20 = min(a20, kecepatanCepat(kecepatan));
    c21 = min(a21, kecepatanCepat(kecepatan));
    c22 = min(a22, kecepatanCepat(kecepatan));
    c23 = min(a23, kecepatanCepat(kecepatan));
    c24 = min(a24, kecepatanCepat(kecepatan));
    c25 = min(a25, kecepatanCepat(kecepatan));
    c26 = min(a26, kecepatanCepat(kecepatan));
    c27 = min(a27, kecepatanCepat(kecepatan));

    aggregationResult = max({c1,  c2,  c3,  c4,  c5,  c6,  c7,  c8,  c9,
                             c10, c11, c12, c13, c14, c15, c16, c17, c18,
                             c19, c20, c21, c22, c23, c24, c25, c26, c27});
    return aggregationResult;
}

//Penentuan Rule based antacedent dan consequence
int main() {
    float suhu, orang, rh;
    float sumA = 0 , sumB = 0;
    cout << "Masukkan suhu: ";
    cin >> suhu;

    cout << "Masukkan jumlah orang: ";
    cin >> orang;

    cout << "Masukkan kelembapan (%): ";
    cin >> rh;

//rule based antacedent
// suhu dingin
float a1  = max({suhuDingin(suhu), jumlorangS(orang),  lembapKering(rh)});
float a2  = max({suhuDingin(suhu), jumlorangS(orang),  lembapNormal(rh)});
float a3  = max({suhuDingin(suhu), jumlorangS(orang),  lembapBasah(rh)});
float a4  = max({suhuDingin(suhu), jumlorangSd(orang), lembapKering(rh)});
float a5  = max({suhuDingin(suhu), jumlorangSd(orang), lembapNormal(rh)});
float a6  = max({suhuDingin(suhu), jumlorangSd(orang), lembapBasah(rh)});
float a7  = max({suhuDingin(suhu), jumlorangB(orang),  lembapKering(rh)});
float a8  = max({suhuDingin(suhu), jumlorangB(orang),  lembapNormal(rh)});
float a9  = max({suhuDingin(suhu), jumlorangB(orang),  lembapBasah(rh)});

// suhu hangat
float a10 = max({suhuHangat(suhu), jumlorangS(orang),  lembapKering(rh)});
float a11 = max({suhuHangat(suhu), jumlorangS(orang),  lembapNormal(rh)});
float a12 = max({suhuHangat(suhu), jumlorangS(orang),  lembapBasah(rh)});
float a13 = max({suhuHangat(suhu), jumlorangSd(orang), lembapKering(rh)});
float a14 = max({suhuHangat(suhu), jumlorangSd(orang), lembapNormal(rh)});
float a15 = max({suhuHangat(suhu), jumlorangSd(orang), lembapBasah(rh)});
float a16 = max({suhuHangat(suhu), jumlorangB(orang),  lembapKering(rh)});
float a17 = max({suhuHangat(suhu), jumlorangB(orang),  lembapNormal(rh)});
float a18 = max({suhuHangat(suhu), jumlorangB(orang),  lembapBasah(rh)});

// suhu panas
float a19 = max({suhuPanas(suhu), jumlorangS(orang),  lembapKering(rh)});
float a20 = max({suhuPanas(suhu), jumlorangS(orang),  lembapNormal(rh)});
float a21 = max({suhuPanas(suhu), jumlorangS(orang),  lembapBasah(rh)});
float a22 = max({suhuPanas(suhu), jumlorangSd(orang), lembapKering(rh)});
float a23 = max({suhuPanas(suhu), jumlorangSd(orang), lembapNormal(rh)});
float a24 = max({suhuPanas(suhu), jumlorangSd(orang), lembapBasah(rh)});
float a25 = max({suhuPanas(suhu), jumlorangB(orang),  lembapKering(rh)});
float a26 = max({suhuPanas(suhu), jumlorangB(orang),  lembapNormal(rh)});
float a27 = max({suhuPanas(suhu), jumlorangB(orang),  lembapBasah(rh)});

cout << "kecepatan"<<","<<"uHasil"<<endl;
for (int kecepatan = 0; kecepatan <= 500; kecepatan++) {
    float uHasil;
    uHasil = agregasi(a1,  a2,  a3,  a4,  a5,  a6,  a7,  a8,  a9,
                      a10, a11, a12, a13, a14, a15, a16, a17, a18,
                      a19, a20, a21, a22, a23, a24, a25, a26, a27,
                      kecepatan);
    sumA = sumA + (uHasil * kecepatan)*1;
    sumB = sumB + uHasil;
    cout << kecepatan << "," << uHasil << endl;
}
float zOutput = (sumB == 0) ? 0 : sumA / sumB;
cout << "Hasil Akhir: " << zOutput << endl;

return 0;
}