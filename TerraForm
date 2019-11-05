#include "DHT.h"
#define DHTPIN1 11     // what digital pin we're connected to
#define DHTPIN2 5     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
#include <DS3231.h>
int Relay1 = 8;
int Relay2 = 7;
int Relay3 = 4;
int Relay4 = 12;
DS3231  rtc(SDA, SCL);
Time t;

const int OnHour[] = {8, 9, 10, 11, 12, 13, 14, 15, 16, 17}; // whatever will be on when the time will be bettwen 8 and 17, number will increase i = i + 1
const int OffHour[] = {0, 1, 2, 3, 4, 5, 6, 7, 18, 19, 20, 21, 22, 23, 24}; // whatever will be off when the t.hour will be in specifid range of values

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
  pinMode(Relay1, OUTPUT); digitalWrite(Relay1, HIGH);
  pinMode(Relay2, OUTPUT); digitalWrite(Relay2, HIGH);
  pinMode(Relay3, OUTPUT); digitalWrite(Relay3, HIGH);
  pinMode(Relay4, OUTPUT); digitalWrite(Relay4, HIGH);
  dht1.begin(); dht2.begin();
  lcd.begin(16, 2);
  lcd.print("TerraForm");
  lcd.setBacklight(GREEN);
}

void loop() {
  int i;
  t = rtc.getTime();
  
  // Serial.print(OffHour[t.hour]);
  // Serial.print(":"); Serial.print(t.min); Serial.print(":"); Serial.print(t.sec); Serial.println(" ");
  // delay (1000);
  lcd.clear(); lcd.setCursor(0, 0);
  lcd.print(t.hour); lcd.print(":"); lcd.print(t.min); lcd.print(":"); lcd.print(t.sec);
  delay (1000);

  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  if (isnan(h1) || isnan(t1)) {
  // Serial.println("Failed to read from DHT1 sensor!");
  lcd.print("fail DHT1");
  digitalWrite(Relay4, HIGH); //turn HOT SPOT OFF
  }

  // Serial.print("Humidity1:"); Serial.print(h1); Serial.print("%");
  // Serial.print("Temperature1:"); Serial.print(t1); Serial.println("*C ");
  // delay(1000);

  lcd.clear(); lcd.setCursor(0, 0);
  lcd.print("Humi1:"); lcd.print(h1); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp1:"); lcd.print(t1); lcd.print("*C");
  delay(1000);

  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  if (isnan(h2) || isnan(t2)) {
  // Serial.println("Failed to read from DHT2 sensor!");
  // lcd.print("fail DHT2");
  digitalWrite(Relay3, HIGH); // turn HEAT OFF
  digitalWrite(Relay1, HIGH); // turn RAIN OFF
    
  }

  // Serial.print("Humidity2:"); Serial.print(h2); Serial.print("%");
  // Serial.print("Temperature2:"); Serial.print(t2); Serial.println("*C ");
  // delay(1000);

  lcd.clear(); lcd.setCursor(0, 0);
  lcd.print("Humi2:"); lcd.print(h2); lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp2:"); lcd.print(t2); lcd.print("*C");
  delay(1000);

  for(i=0; i<25; i=i+1){
  if (t1 > 32 || OffHour[i] == t.hour) {
    digitalWrite(Relay4, HIGH);
    i = 25;
    //Serial.println("HOT SPOT OFF");
    //lcd.clear(); lcd.setCursor(0, 0);
    //lcd.print("HOT SPOT OFF");
    //delay (1000);
  }
  else if (t1 <= 32 && OnHour[i] == t.hour) {
    digitalWrite(Relay4, LOW);
    i = 25;
    // Serial.println("HOT SPOT ON");
    // lcd.clear(); lcd.setCursor(0, 0);
    // lcd.print("HOT SPOT ON");
    // delay (1000);
  }
  }

  if (t2 >= 26) {
    digitalWrite(Relay3, HIGH);
    // Serial.println("HEAT OFF");
    // lcd.clear(); lcd.setCursor(0, 0);
    // lcd.print("HEAT OFF");
    // delay (1000);
  }
  else if (t2 <= 25) {
    digitalWrite(Relay3, LOW);
   // Serial.println("HEAT ON");
   // lcd.clear(); lcd.setCursor(0, 0);
   // lcd.print("HEAT ON");
   // delay (1000);
  }
  
  if (h2 >= 77) {
    digitalWrite(Relay1, HIGH);
    // Serial.println("RAIN OFF");
    // lcd.clear(); lcd.setCursor(0, 0);
    // lcd.print("RAIN OFF");
    // delay (1000);
  }
  else if (h2 < 77) {
    digitalWrite(Relay1, LOW);
    // Serial.println("RAIN ON");
    // lcd.clear(); lcd.setCursor(0, 0);
    // lcd.print("RAIN ON");
    // delay (1000);
  }
  for(i=0; i<25; i=i+1){
    if (OnHour[i] == t.hour) {
    digitalWrite(Relay2, LOW);
    i = 25;
    }
  else if (OffHour[i] == t.hour) {
    digitalWrite(Relay2, HIGH);
    i = 25;
    }
}
  lcd.setCursor(0, 1);
  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0, 0);
    if (buttons & BUTTON_UP) {
    digitalWrite(Relay2, LOW);
    }
    if (buttons & BUTTON_DOWN) {
    digitalWrite(Relay2, HIGH);
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("LEFT ");
    
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");

    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");

    }
  }
}
