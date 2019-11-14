#include "DHT.h"
#define DHTPIN1 11     // what digital pin we're connected to
#define DHTPIN2 5     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
#include <DS3231.h>
  // defined which Relay is connected to which port
  int Relay_Rain = 8;
  int Relay_Light = 7;
  int Relay_Heat = 4;
  int Relay_HotSpot = 12;
DS3231  rtc(SDA, SCL);
Time t;

 // defined array for t.hour
  const int OnHour[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
  const int OffHour[] = {0, 1, 2, 3, 4, 5, 6, 7, 18, 19, 20, 21, 22, 23, 24};

    //
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  int i;
  
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

void setup() {
  Serial.begin(115200);
  rtc.begin();
  pinMode(Relay_Rain, OUTPUT); digitalWrite(Relay_Rain, HIGH);
  pinMode(Relay_Light, OUTPUT); digitalWrite(Relay_Light, HIGH);
  pinMode(Relay_Heat, OUTPUT); digitalWrite(Relay_Heat, HIGH);
  pinMode(Relay_HotSpot, OUTPUT); digitalWrite(Relay_HotSpot, HIGH);
  dht1.begin(); dht2.begin();
  lcd.begin(16, 2);
  lcd.print("TerraForm V2");
  lcd.setBacklight(GREEN);
}
void SaftyHotSpotOff_DHT1(){
  if (isnan(h1) || isnan(t1)) {
  // Serial.println("Failed to read from DHT1 sensor!");
  lcd.print("fail DHT1");
  digitalWrite(Relay_HotSpot, HIGH);
}
}

void SaftyHeatAndRainOff_DHT2(){
  if (isnan(h2) || isnan(t2)) {
  // Serial.println("Failed to read from DHT2 sensor!");
  digitalWrite(Relay_Heat, HIGH);
  digitalWrite(Relay_Rain, HIGH);
}
}
void TurnOnOffHotSpot(){
  for(i=0; i<25; i=i+1){
    if (t1 > 32 || OffHour[i] == t.hour) {
      digitalWrite(Relay_HotSpot, HIGH);
      i = 25;
    }
    else if (t1 <= 32 && OnHour[i] == t.hour) {
      digitalWrite(Relay_HotSpot, LOW);
      i = 25;
    }
  }
}

void TurnOnOffHeat(){
  if (t2 >= 26) {
    digitalWrite(Relay_Heat, HIGH);
  }
  else if (t2 <= 25) {
    digitalWrite(Relay_Heat, LOW);
  }
}

void TurnOnOffRain(){
  if (h2 >= 77) {
    digitalWrite(Relay_Rain, HIGH);
  }
  else if (h2 < 77) {
    digitalWrite(Relay_Rain, LOW);
  }
}

void TurnOnOffLight(){
  for(i=0; i<25; i=i+1){
    if (OnHour[i] == t.hour) {
      digitalWrite(Relay_Light, LOW);
      i = 25;
    }
    else if (OffHour[i] == t.hour) {
      digitalWrite(Relay_Light, HIGH);
      i = 25;
    }
  }
}
void ButtonControl(){
  lcd.setCursor(0, 1);
  uint8_t ReadButtons = lcd.readButtons();

  if (ReadButtons) {
    lcd.clear();
    lcd.setCursor(0, 0);
    
    if (ReadButtons & BUTTON_UP) {
      digitalWrite(Relay_Light, LOW);
    }
    
    if (ReadButtons & BUTTON_DOWN) {
      digitalWrite(Relay_Light, HIGH);
    }
    if (ReadButtons & BUTTON_LEFT) {
      lcd.print("LEFT ");
    }
    
    if (ReadButtons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");
    }
    
    if (ReadButtons & BUTTON_SELECT) {
      lcd.print("SELECT ");
    }
  }}
  
void loop(){
  // display time and do nothing for 1000
  t = rtc.getTime();
  lcd.clear(); lcd.setCursor(0, 0);
  lcd.print(t.hour); lcd.print(":"); lcd.print(t.min); lcd.print(":"); lcd.print(t.sec);
  delay (1000);
  
  // display humidity1 and temp1, do nothing for 1000
  lcd.clear(); lcd.setCursor(0, 0);
  lcd.print("Humi1:"); lcd.print(h1); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp1:"); lcd.print(t1); lcd.print("*C");
  delay(1000);

  // display humidity2 and temp2, do nothing for 1000
  lcd.clear(); lcd.setCursor(0, 0);
  lcd.print("Humi2:"); lcd.print(h2); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp2:"); lcd.print(t2); lcd.print("*C");
  delay(1000);
  
  SaftyHotSpotOff_DHT1();
  SaftyHeatAndRainOff_DHT2();
  TurnOnOffHotSpot();
  TurnOnOffHeat();
  TurnOnOffRain();
  ButtonControl();
}
