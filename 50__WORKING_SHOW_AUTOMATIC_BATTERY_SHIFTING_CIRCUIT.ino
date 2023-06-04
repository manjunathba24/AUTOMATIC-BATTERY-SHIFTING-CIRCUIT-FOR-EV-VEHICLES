#include <Adafruit_LiquidCrystal.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

#include <LiquidCrystal_I2C.h>
const int RELAY_PIN1 = 3;  
const int RELAY_PIN2 = 5;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  lcd.begin(20,4);
  lcd.init();
  lcd.backlight();
  lcd.clear();  
pinMode(RELAY_PIN1, OUTPUT);
pinMode(RELAY_PIN2, OUTPUT);
 
}
// the loop routine runs over and over again forever:
void loop() {
  int Battery1 = analogRead(A0);
  int Battery2 = analogRead(A1);
  float voltageA = Battery1 * (15/ 1024.0);
  Serial.println("BATT 1 VOLTAGE : ");
  Serial.print(voltageA);
  float voltageB = Battery2 * (30/ 1024.0);
  Serial.println("BATT 2 VOLTAGE : ");
  Serial.print(voltageB);
  lcd.setCursor(0,0);
  lcd.print(" BATT1 VOLTAGE:");
  lcd.print(voltageA);
  lcd.print("V");
  lcd.print(" ");
  lcd.setCursor(0,3);
  lcd.print(" BATT2 VOLTAGE:");
  lcd.print(voltageB);
  lcd.print("V");
  lcd.print(" ");
 lcd.setCursor(0, 1);
  lcd.print("AUTOMATIC BATT SHIFT");
 lcd.setCursor(0,2);
 lcd.print(" BATTERY 1");
 digitalWrite(RELAY_PIN1, HIGH);
 float voltageA1= Battery1 * (30/ 1024.0);
  delay(50000);
    digitalWrite(RELAY_PIN1, LOW);
  lcd.setCursor(0,2);
  lcd.print(" BATTERY 2");
  digitalWrite(RELAY_PIN2, HIGH);
  delay(100000);
}
