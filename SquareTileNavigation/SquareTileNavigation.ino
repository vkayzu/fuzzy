#include <Servo.h>              // Include servo library

Servo servoLeft;                // Declare left & right servos
Servo servoRight;

void setup()                    // Built-in initialization
{
  Serial.begin(9600);           // Buka komunikasi serial
  Serial.println("Mulai program...");

  servoLeft.attach(11);         // Attach left signal to pin 11
  servoRight.attach(10);        // Attach right signal to pin 10

  Serial.println("Servo sudah di-attach.");
}

void loop()
{
  for (int sisi = 1; sisi <= 4; sisi++)
  {
    Serial.print("Sisi ke-");
    Serial.println(sisi);

    // ---- Maju 40 cm ----
    Serial.println("  Maju...");
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1300);
    delay(3950);

    // ---- Pivot forward-right, putar 90 derajat ----
    Serial.println("  Pivot 90 derajat...");
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1500);
    delay(1600);
  }

  Serial.println("Satu putaran selesai. Ulang lagi dari sisi 1...");
}