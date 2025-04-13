//2025 changes:
//radically redesigned 'progess' bar
//include a tft.print() GFX 'Arduino' style print example
// on the HotHead/BoneHead section
#include <TFT_eSPI.h>
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

  pinMode(PIN_POWER_ON, OUTPUT);  //triggers the LCD backlight power
  //and allows run on battery
  pinMode(PIN_LCD_BL, OUTPUT);  // BackLight enable pin
  pinMode(lowerbutton, INPUT);  //Right button pulled up, push = 0
  pinMode(topbutton, INPUT);    //Left button  pulled up, push = 0
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

  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 50);
  //GFX 'Arduino' style print example
  if (!digitalRead(topbutton) && !digitalRead(lowerbutton)) {
    tft.print("BoneHead! ");
  } else {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.print(" HotHead!  ");
  }
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.fillRect(20, 71, 60, 25, TFT_BLACK);
  tft.drawString(String(progress) + "% ", 60, 85, 2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString(" Demo ", 90, 85, 2);
  delay(100);
  tft.drawRoundRect(15, 110, 115, 18, 3, TFT_GREEN);  //the frame

  progress++;  //progress is the 0-100% progression of bulding
  if (progress >= 100) {
    progress = 0;
    tft.fillRect(18, 114, 110, 10, TFT_BLACK);
  }

  if (progress >= 0 && progress < 37) {
    colour = 0x001F;  //BLUE
  }
  if (progress > 37 && progress < 72) {
    colour = 0x07E0;  //GREEN
  }
  if (progress > 72 && progress <= 100) {
    colour = 0xF800;  //RED
  }

  tft.fillRect(progress + 20, 114, 1, 10, colour);

  tft.drawRect(5, 5, 95, 22, TFT_BLUE);     //"Top"  text box
  tft.drawRect(5, 146, 110, 22, TFT_BLUE);  // "Bottom" text box
  if (digitalRead(topbutton)) {             //  normally open sw, pulled up.
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
  } else {
    tft.setTextColor(TFT_RED, TFT_BLACK);
  }
  tft.drawString("< Top pin 0", 45, 15, 2);

  if (digitalRead(lowerbutton)) {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
  } else {
    tft.setTextColor(TFT_RED, TFT_BLACK);
  }
  tft.drawString("< Bottom p14", 55, 157, 2);
}
