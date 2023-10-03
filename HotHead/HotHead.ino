
#include "TFT_eSPI.h"
#include "hothead.h"
unsigned colour = 0xFFFF;
TFT_eSPI tft = TFT_eSPI();
#define topbutton 0
#define lowerbutton 14
#define PIN_POWER_ON 15  // LCD and battery Power Enable
#define PIN_LCD_BL 38    // BackLight enable pin (see Dimming.txt)
int progress = 0;
int x;
int blocks = 0;
int i = 0;
bool ticktock = true;

void setup() {

  pinMode(PIN_POWER_ON, OUTPUT);  //enables the LCD and to run on battery
  pinMode(PIN_LCD_BL, OUTPUT);    // BackLight enable pin
  pinMode(lowerbutton, INPUT);    //Right button pulled up, push = 0
  pinMode(topbutton, INPUT);      //Left button  pulled up, push = 0
  delay(100);
  digitalWrite(PIN_POWER_ON, HIGH);
  digitalWrite(PIN_LCD_BL, HIGH);
  Serial.begin(115200);  // be sure to set USB CDC On Boot: "Enabled"
  //(Serial print slows progres bar Demo)
  delay(100);
  tft.init();
  tft.setRotation(3);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);  //horiz / vert<> position/dimension
  tft.pushImage(165, 0, 155, 170, hothead);
  tft.setTextSize(1);
  tft.setTextDatum(4);

  delay(100);
  Serial.println("In setup!");

  delay(2000);
}

void loop() {
  ticktock = !ticktock;
  if (ticktock) {
    Serial.println("tick");  //(Serial print slows progress bar Demo)
  } else {
    Serial.println("tock");
  }

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  if (!digitalRead(topbutton) && !digitalRead(lowerbutton)) {
    tft.drawString(" BoneHead!", 77, 55, 4);
  } else {
    tft.drawString("  HotHead!  ", 80, 55, 4);
  }
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRect(39, 78, 70, 13, TFT_BLACK);
  tft.drawString(String(progress) + "% Demo", 75, 85, 2);
  progress++;
  if (progress >= 100)
    progress = 0;
  blocks = progress / 5;
  tft.drawRoundRect(15, 110, 125, 18, 3, TFT_GREEN);  //rectangle colour
  // progress blocks below here
  for (i = 0; i < blocks; i++) {
    x = i * 5 + i + 20;  //x location i is increment 20 is a location offset
    if (progress > 0 && progress < 40) {
      colour = 0x001F;  //BLUE
    }
    if (progress > 40 && progress < 75) {
      colour = 0x07E0;  //GREEN
    }
    if (progress > 75 && progress < 99) {
      colour = 0xF800;  //RED
    }
    if (progress > 98) {
      colour = 0x0000;  //BLACK
    }
    tft.fillRect(x, 114, 5, 10, colour);
  }
  tft.drawRect(5, 5, 95, 22, TFT_BLUE);     //"Top"  text box
  tft.drawRect(5, 146, 110, 22, TFT_BLUE);  // "Bottom" text box
  if (digitalRead(0)) {                     //  normally open sw, pulled up.
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
  } else {
    tft.setTextColor(TFT_RED, TFT_BLACK);
  }
  tft.drawString("< Top pin 0", 45, 15, 2);
  if (digitalRead(14)) {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
  } else {
    tft.setTextColor(TFT_RED, TFT_BLACK);
  }
  tft.drawString("< Bottom p14", 55, 157, 2);
  delay(100);
}
