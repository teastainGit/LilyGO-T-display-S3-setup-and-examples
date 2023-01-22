
#include "TFT_eSPI.h"
#include "hothead.h"
unsigned  colour = 0xFFFF;
TFT_eSPI tft = TFT_eSPI();

#define topbutton 0
#define lowerbutton 14
#define PIN_POWER_ON 15
#define PIN_LCD_BL  38

int x;
int blocks = 0;
int percentdim = 0;

const int freq = 1000;
const int ledChannel = 0;
const int resolution = 8;
int dim = 255;

void setup() {

  pinMode(PIN_POWER_ON, OUTPUT);  //triggers the LCD backlight
  pinMode(lowerbutton, INPUT);     //Right button pulled up, push = 0
  pinMode(topbutton, INPUT);      //Left button  pulled up, push = 0
  delay(100);
  digitalWrite(PIN_POWER_ON, LOW);
  delay(100);
  digitalWrite(PIN_POWER_ON, HIGH);
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
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(PIN_LCD_BL, ledChannel);

  delay(2000);
}

void loop() {
  //Serial.println("In loop!"); //(Serial print slows progres bar Demo)
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextFont(2);
  if (!digitalRead(topbutton) && !digitalRead(lowerbutton))
  {
    tft.drawString(" BoneHead!", 77, 55, 4);
  }
  else {
    tft.drawString("  HotHead!  ", 80, 55, 4);
  }
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.drawString(String(dim) + " Bright   ", 90, 85, 4);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
  percentdim = map(dim, 0, 255, 0, 100);
  tft.drawString(String ("    ") + (percentdim) + "  %  ", 75, 115, 4);

  ledcWrite(ledChannel, dim);

  tft.drawRect(5, 5, 60, 22, TFT_BLUE);  //"left"  text boxe
  tft.drawRect(5, 146, 65, 22, TFT_BLUE); // "right" text boxe
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("<  Dim", 30, 15, 2);
  if (dim < 255) {
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
  }
  else if (dim = 255) {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    dim = 255;
  }
  tft.drawString("<  Bright", 35, 157, 2);

  if (!digitalRead(topbutton) && dim > 0) { //normally open sw, pulled up.
    dim = dim - 5;
    delay(50);
  }

  if (!digitalRead(lowerbutton) && dim < 255) {
    dim = dim + 5;
    delay(50);
  }
  delay(30);
}
