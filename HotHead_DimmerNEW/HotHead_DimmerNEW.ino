
#include "TFT_eSPI.h"
#include "hothead.h"
unsigned colour = 0xFFFF;
TFT_eSPI tft = TFT_eSPI();

#define topbutton 0
#define lowerbutton 14
#define PIN_POWER_ON 15
#define PIN_LCD_BL 38



void setup() {

  pinMode(PIN_POWER_ON, OUTPUT);  //enables battery power and LCD backlight
  pinMode(PIN_LCD_BL, OUTPUT);    //controls the LCD backlight
  pinMode(lowerbutton, INPUT);  //Right button pulled up, push = 0
  pinMode(topbutton, INPUT);    //Left button  pulled up, push = 0
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
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextFont(2);
  tft.drawString("  HotHead!  ", 10, 40, 4);
  tft.setTextSize(1);
  tft.setTextDatum(4);
  tft.drawRect(5, 5, 60, 22, TFT_BLUE);    //"left"  text box
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("<  Dim", 30, 15, 2);
  Serial.println("In setup!");
  delay(500);
}

void loop() {
  if (!digitalRead(topbutton)) {  //pressed is off
    digitalWrite(PIN_LCD_BL, LOW);
    delayMicroseconds(200);
    digitalWrite(PIN_LCD_BL, HIGH);
  }
  delay(200);
}
