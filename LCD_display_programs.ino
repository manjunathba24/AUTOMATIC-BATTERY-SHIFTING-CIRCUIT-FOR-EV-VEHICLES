#include <Adafruit_LiquidCrystal.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

#include <LiquidCrystal_I2C.h>
char array1[]="AUTOMATIC BATTERY SHIFTING CKT";
char array2[]="BATTERY1 VOLTAGE=";
char array3[]="BATTERY2 VOLTAGE=";
char array4[]="BATTERY 1";
char array5[]="BATTERY 2";

void setup() {
  lcd.begin(20,4);
  lcd.init();
  lcd.clear();         
  lcd.backlight();      
  lcd.setCursor(0,1);
  lcd.print(array1);
  lcd.setCursor(0,0);
  lcd.print(array2);
  lcd.setCursor(0,3);
  lcd.print(array3);
  lcd.setCursor(0,2);
  lcd.print(array4);
 delay(500);
 lcd.setCursor(0,2);
  lcd.print(array5);
}


void loop() {
}
