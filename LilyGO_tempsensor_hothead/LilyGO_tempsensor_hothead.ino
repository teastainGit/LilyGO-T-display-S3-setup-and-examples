/*BN: ESP32S3 Dev Module
  VID: 303a
  PID: 1001
  SN: 68:B6:B3:21:63:18
  Flash Size 8M
  Partition Scheme 8M with SPIFFS
  Display specs
  Horiz     Vert
  <320>----^v170
  SHT3X temp and humiditysensor @addr 0x44
  (also sold as M5Stack ENV series)
*/
#include <Wire.h>
#include "TFT_eSPI.h"
#include "hothead.h"

float cTemp = 12.3;
unsigned int data[2];

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
#define LCDpin 15

void setup() {
  pinMode(LCDpin, OUTPUT);  //triggers the LCD backlight
  digitalWrite(LCDpin, HIGH);
	Serial.begin(115200);  // be sure to set USB CDC On Boot: "Enabled"
  Wire.begin(43, 44);  //SDA, SCL
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

  sprite.fillSprite(TFT_WHITE);   // left side background colour
  sprite.setFreeFont(&Orbitron_Light_24);
  if (!digitalRead(0) && !digitalRead(14))  // reverse logic push for "0"
  {
    sprite.drawString(" BoneHead!", 75, 16);
  }
  else {
    sprite.drawString("HotHead!", 75, 16);
  }
  sprite.setFreeFont(&Orbitron_Light_32);
  sprite.setTextColor(TFT_BLUE, TFT_WHITE);
  sprite.drawString(String(cTemp, 1) + "C", 75, 54);

  sprite.drawRect(5, 124, 65, 22, TFT_BLACK);  //"left" and "right" text boxes
  sprite.drawRect(80, 124, 65, 22, TFT_BLACK);
  if (digitalRead(0)) {                      //  normally "on" level "true".
    sprite.drawString("left pin0", 35, 134, 2);//"Push" is active, level "false"
  }
  else {
    sprite.drawString("LEFT", 30, 134, 2);
  }
  if (digitalRead(14)) {
    sprite.drawString("right p14", 113, 134, 2);
  }
  else {
    sprite.drawString("RIGHT", 113, 134, 2);
  }
  sprite.setTextFont(2);
  sprite.drawString("Own it!!!", 80, 158);//learn the board and take control!
  sprite.setTextFont(2);
  sprite.drawString("SHT3X @addr 0x44", 80, 100);
  sprite.pushSprite(0, 0);
  delay(100);
}
