
//AUTOMATIC BATTERY SHIFTING CIRCUIT FOR EV-VEHICLES
#include <Adafruit_LiquidCrystal.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip
#include <LiquidCrystal_I2C.h>
#define BAT1_ADC A0     //BATTER 1 side voltage divider is connected to pin A0 
#define BAT2_ADC A1    // Battery 2 side voltage divider is connected to pin A1
//#define CURRENT_ADC A2  // ACS 712 current sensor is connected to pin A2
#define AVG_NUM 10    // number of iterations of the adc routine to average the adc readings
#define BAT1_MIN 3.0  // minimum battery voltage for 12V system
#define BAT1_MAX 8.0 // maximum battery voltage for 12V system
#define BAT2_MIN 3.0  // minimum battery voltage for 12V system
#define BAT2_MAX 7.5 // maximum battery voltage for 12V system
//#define REALY1_PIN 3         // pin-3 is used to control the charging BATTERY1 //the default frequency is 490.20Hz
//#define RELAY2_PIN 5       // pin-2 is used to control the BATTERY 1 ON AND OFF
const int LCD_COLS = 20;  // 20 columns
const int LCD_ROWS = 4;   // 4 Rows
const int RELAY1_PIN = 3;  
const int RELAY2_PIN= 5;
int BATTERY1_voltage;
//--------------------------------------------------------------------------------------------------------------------------
///////////////////////DECLARATION OF ALL GLOBAL VARIABLES//////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------------------------------------------------------
float bat1_volt=0;
float bat2_volt=0;
float Battery1_status=0;
float battery2_status=0;
float status;
//******************************************************* MAIN PROGRAM START ************************************************
/*char array1[]="AUTOMATIC BATTERY SHIFTING CKT";
char array2[]="BATTERY1 VOLTAGE=";
char array3[]="BATTERY2 VOLTAGE=";
char array4[]="BATTERY 1";
char array5[]="BATTERY 2";*/
void setup()
{
lcd.begin(20,4);
lcd.init();
lcd.clear();         
lcd.backlight();   
Serial.begin(9600);
pinMode(RELAY1_PIN,OUTPUT);
pinMode(RELAY2_PIN,OUTPUT);
/*status = lcd.begin(LCD_COLS, LCD_ROWS);
 if(status) // non zero status means it was unsuccesful
 {
 status = -status; // convert negative status value to positive number

 // begin() failed so blink error code using the onboard LED if possible
 hd44780::fatalError(status); // does not return
 }*/
}
//************************************************************ PROGRAM END *************************************************


//------------------------------------------------------------------------------------------------------
////////////////// READS AND AVERAGES THE ANALOG INPUTS (BATTERY 1 VOLTAGE,BATTERY 2 VOLTAGE)////////////////
//------------------------------------------------------------------------------------------------------
int read_adc(int adc_parameter)
{
  
  int sum = 0;
  int sample ;
  for (int i=0; i<AVG_NUM; i++) 
  {                                        // loop through reading raw adc values AVG_NUM number of times  
    sample = analogRead(adc_parameter);    // read the input pin  
    sum += sample;                        // store sum for averaging
    delayMicroseconds(50);              // pauses for 50 microseconds  
  }
  return(sum / AVG_NUM);                // divide sum by AVG_NUM to get average and return it
}
//-------------------------------------------------------------------------------------------------------------
////////////////////////////////////READ THE DATA//////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------------------
 void read_data(void) 
 {
    //12V = ADC value 1024 => 1 ADC value = (7.5/1024)Volt= 0.00732Volt
    // Vout=Vin*R2/(R1+R2) => Vin = Vout*(R1+R2)/R2   R1=110 and R2=10//
bat1_volt =read_adc(BAT1_ADC)*0.007324*(110/10);
bat2_volt=read_adc(BAT2_ADC)*0.006835*(110/10);       
    
  }
 
//------------------------------------------------------------------------------------------------------------
/////////////////////////////////PRINT DATA IN SERIAL MONITOR/////////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------------
  void print_data(void) 
  {
   Serial.print("AUTOMATIC BATTERY SHIFING CIRCUIT FOR EV: ");
   Serial.print("Battery 1 voltage:");
   Serial.print(bat1_volt);
   Serial.println("V");
   Serial.print("Battery 2 Voltage: ");
   Serial.print(bat2_volt);
   Serial.println("V");
  }
//----------------------------------------------------------------------------------------------------------------------
//////////////////////////////////SYSTEM VOLTAGE AUTO DETECT ///////////////////////////////////////////////////////////
//----------------------------------------------------------------------------------------------------------------------
void system_voltage(void)
{
  if ((bat1_volt<BAT1_MIN))
  {
  digitalWrite(RELAY1_PIN,LOW);  // default value of pwm duty cycle
  digitalWrite(RELAY2_PIN,HIGH);  // default load state is OFFF
  lcd.setCursor(0,2);
  lcd.print(" BATTERY 1");
  }
  else 
  {
  digitalWrite(RELAY1_PIN,HIGH);
  digitalWrite(RELAY2_PIN,LOW);
  lcd.setCursor(0,2);
  lcd.print(" BATTERY 2");
  }
}
//------------------------------------------------------------------------------------------------------
//////////////////////// LCD DISPLAY///////////////////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------
void loop()
{
lcd.setCursor(0, 1);
lcd.print("AUTOMATIC BATT SHIFT");
lcd.setCursor(0,0);
lcd.print(" BATT1 VOLTAGE:");
lcd.print(bat1_volt);
lcd.print("V");
lcd.setCursor(0,3);
lcd.print(" BATT2 VOLTAGE:");
lcd.print(bat2_volt);
lcd.print("V");
}
