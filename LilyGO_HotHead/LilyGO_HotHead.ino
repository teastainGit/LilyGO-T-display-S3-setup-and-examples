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
unsigned  colour = 0xFFFF;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

void setup() {
  Serial.begin(115200);  // be sure to set USB CDC On Boot: "Enabled"
  //(Serial print slows progres bar Demo)
  tft.init();
  tft.setRotation(3);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_WHITE);  //horiz / vert<> position/dimension
  tft.pushImage(165, 0, 155, 170, hothead);
  tft.setTextSize(1);
  sprite.createSprite(165, 170);

  sprite.setTextColor(TFT_BLACK, TFT_WHITE);
  sprite.setTextDatum(4);
  delay(500);
  Serial.println("In setup!");
  delay(1000);
  pinMode(14, INPUT); //Right button proven to be pulled up, push = 0
  pinMode(0, INPUT); //Left button proven to be pulled up, push = 0
}

//progress bar variables
int progress = 0;
int x;
int y = 94;
int blocks = 0;

void loop() {
  //Serial.println("In loop!"); //(Serial print slows progres bar Demo)
  sprite.setTextColor(TFT_BLACK, TFT_WHITE);
  sprite.fillSprite(TFT_WHITE);   // left side background colour
  sprite.setFreeFont(&Orbitron_Light_24);
  if (!digitalRead(0) && !digitalRead(14))  //reverse logic push for "0"
  {
    sprite.drawString(" BoneHead!", 74, 16);
  }
  else {
    sprite.drawString("HotHead!", 75, 16);
  }
  sprite.setFreeFont(&Orbitron_Light_32);
  sprite.setTextColor(TFT_BLUE, TFT_WHITE);
  sprite.drawString(String(progress) + "%", 75, 54);

  progress++;
  if (progress >= 100)
    progress = 0;
  sprite.setTextColor(TFT_BLACK, TFT_WHITE);  //text colour
  blocks = progress / 5;
  sprite.drawRoundRect(15, 90, 125, 18, 3, TFT_BLACK); //rectangle colour
  // progress blocks below here
  for (int i = 0; i < blocks; i++) {
    x = i * 5 + i + 20;//x location i is increment 20 is a location offset
    if (progress < 40) {
      colour = 0x001F;  //RGB, "TFT_BLUE"
    }
    else if (progress > 40 && progress < 75) {
      colour = 0x07E0;  //GREEN
    }
    else {
      colour = 0xF800;  //RED
    }
    sprite.fillRect(x, y, 5, 10, colour);
  }

  sprite.drawRect(5, 124, 70, 22, TFT_BLACK);//"left" and "right" text boxes
  sprite.drawRect(85, 124, 70, 22, TFT_BLACK);
  if (digitalRead(0)) {  //  normally open sw, pulled up.
    sprite.drawString("left pin 0", 40, 134, 2);
  }
  else {
    sprite.drawString("LEFT", 40, 134, 2);
  }

  if (digitalRead(14)) {
    sprite.drawString("right p14", 120, 134, 2);
  }
  else {
    sprite.drawString("RIGHT", 120, 134, 2);
  }
  sprite.setTextColor(TFT_RED, TFT_WHITE);
  sprite.setTextFont(2);
  sprite.drawString("Own it!!!", 80, 158);//learn the board and take control!
  sprite.pushSprite(0, 0);
  delay(100);
}
