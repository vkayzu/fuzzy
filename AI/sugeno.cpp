#include <math.h>
#include <iostream>

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
    uorgsedikit = (35 - orang) / 20;
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
    uorgbanyak = (orang - 15) / 20;
  } else {
    uorgbanyak = 1.0;
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
float z1 = 200;
float z2 = 200;
float z3 = 350;
float z4 = 350;   
float z5 = 500;   
float z6 = 500;

//defuzzifikasi 
float total = a1 + a2 + a3 + a4 + a5 + a6;
float zout =  (a1 * z1 + a2 * z2 + a3 * z3 + a4 * z4 + a5 * z5 + a6 * z6) / total;
cout << "Hasil defuzzifikasi: " << zout << endl;
return 0;
}




