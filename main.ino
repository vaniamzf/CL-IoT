 /* 
 Koneksi pin LCD:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5 ==>10
 * LCD D5 pin to digital pin 4 ==> 9
 * LCD D6 pin to digital pin 3 ==> 8
 * LCD D7 pin to digital pin 2 ==> 7
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

// include the library code:
#include <LiquidCrystal.h>

const int pinMotor_kiri_A = 4; //menginisialisasi pin 6 sebagai motor kiri kaki A
const int pinMotor_kiri_B = 5; //menginisialisasi pin 7 sebagai motor kiri kaki B
const int pinMotor_kanan_A = 3; //menginisialisasi pin 3 sebagai motor kanan kaki A
const int pinMotor_kanan_B = 2; //menginisialisasi pin 2 sebagai motor kanan kaki B
const int pinLDR_kiri = A1; //menginisialisasi pin analog 1 sebagai input LDR kiri
const int pinLDR_kanan = A2; //menginisialisasi pin analog 2 sebagai input LDR kanan

int sensorValueLDRkiri=0; //variabel penampung nilai LDR kiri
int sensorValueLDRkanan=0; //variabel penampung nilai LDR kanan

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(RS, E, DB4, DB5, DB6, DB7);
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void setup()
{
  //Deklarasi status input dan output pin-pin yang digunakan
  pinMode(pinMotor_kiri_A, OUTPUT);
  pinMode(pinMotor_kiri_B, OUTPUT);
  pinMode(pinMotor_kanan_A, OUTPUT);
  pinMode(pinMotor_kanan_B, OUTPUT);
  pinMode(pinLDR_kiri, INPUT);
  pinMode(pinLDR_kanan, INPUT);
  
  lcd.begin(16, 2); // set up jumlah kolom dan baris LCD:
  // Tampilkan kalimat pembuka di LCD:
  lcd.setCursor(0, 0);
  lcd.print("Robot");
  lcd.setCursor(0, 1);
  lcd.print("Pengikut Cahaya");
  delay(500);

  //menentukan kecepatan kirim data ke serial monitor
  Serial.begin(9600);
}

void loop()
{     
  sensorValueLDRkiri = analogRead(pinLDR_kiri); //membaca nilai sensor LDR kiri
  sensorValueLDRkanan = analogRead(pinLDR_kanan); //membaca nilai sensor LDR kanan
  
  //Serial.print(sensorValueLDRkiri); //menampilkan nilai digital LDR kiri  
  //Serial.print("   ");
  //Serial.println(sensorValueLDRkanan); //menampilkan nilai digital LDR kanan
  
  //Tampilkan nilai LDR kiri dan kanan di LCD baris kedua
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(sensorValueLDRkiri);
  lcd.print(" ; ");
  lcd.print(sensorValueLDRkanan);
  delay(50);

  if(sensorValueLDRkiri>sensorValueLDRkanan){
    // jika intensitas cahaya kiri lebih besar dari kanan maka robot berbelok ke kiri
    // Belok Kiri
    digitalWrite(pinMotor_kiri_A, HIGH);
    digitalWrite(pinMotor_kiri_B, LOW);
    digitalWrite(pinMotor_kanan_A, HIGH);
    digitalWrite(pinMotor_kanan_B, LOW);
    
    //Tampilkan status gerak robot
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Belok Kiri");
    delay(50);
   }
  else if(sensorValueLDRkiri<sensorValueLDRkanan){
    // jika intensitas cahaya kiri lebih kecil dari kanan maka robot berbelok ke kanan
  // Belok Kanan
    digitalWrite(pinMotor_kiri_A, LOW);
    digitalWrite(pinMotor_kiri_B, HIGH);
    digitalWrite(pinMotor_kanan_A, LOW);
    digitalWrite(pinMotor_kanan_B, HIGH);

    //Tampilkan status gerak robot
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Belok Kanan");
    delay(50);
   } 
  else if(sensorValueLDRkiri==sensorValueLDRkanan){ 
    // jika intensitas cahaya kiri sama dengan kanan maka robot maju
  // Maju
    digitalWrite(pinMotor_kiri_A, LOW);
    digitalWrite(pinMotor_kiri_B, HIGH);
    digitalWrite(pinMotor_kanan_A, HIGH);
    digitalWrite(pinMotor_kanan_B, LOW);

    //Tampilkan status gerak robot
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Maju");
    delay(50);
   }
}
