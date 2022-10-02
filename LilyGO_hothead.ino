/*BN: ESP32S3 Dev Module
  VID: 303a
  PID: 1001
  SN: 68:B6:B3:21:63:18
  Flash Size 8M
  Partition Scheme 8M with SPIFFS
  Horiz     Vert
  <320>----^v170
*/
#include "TFT_eSPI.h"
#include "hothead.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void setup() {
  Serial.begin(115200); // be sure to set USB CDC On Boot: "Enabled"
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
  delay(2000);
  pinMode(14, INPUT); //Right button proven to be pulled up, push = 0
  pinMode(0, INPUT); //Left button proven to be pulled up, push = 0
}

//progress bar variables
int progress = 0;
int w = 120;
int h = 18;
int x = 12;
int y = 90;
int blocks = 0;

void loop() {
  Serial.println("In loop!");

  sprite.fillSprite(TFT_WHITE);   // left side background colour
  sprite.setFreeFont(&Orbitron_Light_24);
  if (!digitalRead(0) && !digitalRead(14))  // that old reverse logic push for "0"
  {
    sprite.drawString(" BoneHead!", 75, 16);
  }
  else {
    sprite.drawString("HotHead!", 75, 16);
  }
  sprite.setFreeFont(&Orbitron_Light_32);
  sprite.setTextColor(TFT_BLUE, TFT_WHITE);
  sprite.drawString(String(progress) + "%", 75, 54);

  progress++;
  if (progress == 101)
    progress = 0;
  sprite.setTextColor(TFT_BLACK, TFT_WHITE);  //text colour
  blocks = progress / 5;
  sprite.drawRoundRect(x, y, w, h, 3, TFT_RED); //rectangle colour
  // progress blocks below here
  for (int i = 0; i < blocks; i++)
    if (progress < 33) {
      sprite.fillRect(i * 5 + (x + 2) + (i * 1), y + 4, 5, 10, TFT_BLUE);
    }
    else if (progress >= 33 && progress < 66) {
      sprite.fillRect(i * 5 + (x + 2) + (i * 1), y + 4, 5, 10, TFT_GREEN);
    }
    else {
      sprite.fillRect(i * 5 + (x + 2) + (i * 1), y + 4, 5, 10, TFT_RED);
    }
  sprite.drawRect(5, 124, 65, 22, TFT_BLACK);  //"left" and "right" text boxes
  sprite.drawRect(80, 124, 65, 22, TFT_BLACK);  
  if (digitalRead(0)) {                        //  normally "on" level "true". 
    sprite.drawString("left pin0", 35, 134, 2);  // "Push" is active, level "false"
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
  sprite.drawString("Own it!!!", 80, 158);  //learn the board and take control!

  sprite.pushSprite(0, 0);
  delay(100);
}
