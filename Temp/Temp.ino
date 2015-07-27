#include <LiquidCrystal.h>
#include <avr/sleep.h>

// Temp sensor input
int tmp = 5;
double tmpVal;

// Voltage monitor input
int batt = 4;
double battVal;

// Display PWR
int displayPWR = 12;

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(7, 4, 3, 2, 1, 0);

void setup() {
  
  UCSR0B = 0;
  
  pinMode(displayPWR, OUTPUT);
  
  // set analog ref to 1.1V
  analogReference(INTERNAL);
  
  // Turn on Display
  digitalWrite(displayPWR, 1);
}

void loop() {
  /*  
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);
  */
    // initialize the library with the numbers of the interface pins
  LiquidCrystal lcd(7, 4, 3, 2, 1, 0);
  
  lcd.begin(16, 2);
  
  tmpVal = analogRead(tmp);
  tmpVal = (tmpVal/1024*11/10-0.5)*100;
  tmpVal = tmpVal;
  
  battVal = analogRead(batt);
  battVal = (battVal/1024);
  
  // Value Calibration
  battVal = battVal*554/100;
  
  // Let LCD power on
  delay(100);
  
  // Display Temperature
  lcd.setCursor(0,0);
  lcd.print("Amb Temp: ");
  lcd.print(tmpVal);
  lcd.print("C");
  
  // Display Battery Voltage
  lcd.setCursor(0,1);
  lcd.print("Voltage: ");
  lcd.print(battVal);
  lcd.print("V");
  
  // Hold Display
  delay(10000);
  
  digitalWrite(displayPWR, 0);  
  
  // disable ADC
  ADCSRA = 0;  
  
  // Hush hush little one...
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS);
  sleep_cpu (); 
}
