#include <Wire.h>
#include "TFT_eSPI.h"
#include "hothead.h"

float cTemp = 12.3;
unsigned int data[2];

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
#define PIN_POWER_ON 15 //power enable pin for LCD and use battery if installed
#define PIN_LCD_BL 38   // BackLight enable pin (see Dimming.txt)

void setup() {

  pinMode(PIN_POWER_ON, OUTPUT);  //triggers the LCD backlight
  pinMode(PIN_LCD_BL, OUTPUT);  //triggers the LCD backlight
  digitalWrite(PIN_POWER_ON, HIGH);
  digitalWrite(PIN_LCD_BL, HIGH);
  Serial.begin(115200);  // be sure to set USB CDC On Boot: "Enabled"
  Wire.begin(43, 44);  //SDA, SCL
  Serial.print("In setup");
  tft.init();
  tft.setRotation(3);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);  //horiz / vert<> position/dimension
  tft.pushImage(165, 0, 155, 170, hothead);
  tft.setTextSize(1);
  sprite.createSprite(146, 170);

  sprite.setTextColor(TFT_BLACK, TFT_WHITE);
  sprite.setTextDatum(4);
  delay(500);
  Serial.println("In setup!");
  pinMode(14, INPUT); //Right button proven to be pulled up, push = 0
  pinMode(0, INPUT); //Left button proven to be pulled up, push = 0
}

void loop() {
  Serial.println("In loop!");
  Wire.beginTransmission(0x44);  //0x44 for M5Stack ENV  (0x45 is DFRobot)
  Wire.write(0x2C);               //show all the "wheels and gears"
  Wire.write(0x06);
  if (Wire.endTransmission() != 0) {
  }
  delay(50);
  Wire.requestFrom(0x44, 2);
  data[0] = Wire.read();
  data[1] = Wire.read();
  delay(50);
  cTemp = ((((data[0] * 256.0) + data[1]) * 175) / 65535.0) - 45;
  Serial.println(cTemp);
  sprite.fillSprite(TFT_WHITE);   // left side background colour
  sprite.setFreeFont(&Orbitron_Light_24);
  sprite.drawString("HotHead!", 75, 16);
  sprite.setTextColor(TFT_BLUE, TFT_WHITE);
  sprite.drawString(String(cTemp, 1) + " degC", 76, 54);
  sprite.setTextColor(TFT_BLACK, TFT_WHITE);

  sprite.setTextFont(2);
  sprite.drawString("SHT3X @addr 0x44", 80, 100);
  sprite.pushSprite(0, 0);
  delay(500);
}
