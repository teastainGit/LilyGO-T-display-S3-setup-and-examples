#include "TFT_eSPI.h"
#include "hothead.h"
unsigned colour = 0xFFFF;
TFT_eSPI tft = TFT_eSPI();
#define topbutton 0
#define PIN_POWER_ON 15
#define PIN_LCD_BL 38
#define analogPin 4. //for internal battery voltage monitor
// for external measurements use a voltage divider
// will require calibration and scaling!
float val = 1.23; //my default value for sanity check
float scaling = 0.0017; // to read voltage on USB as 5.00
void setup() {
  pinMode(PIN_POWER_ON, OUTPUT);  //enables battery power and LCD backlight
  pinMode(PIN_LCD_BL, OUTPUT);    //controls the LCD backlight
  pinMode(topbutton, INPUT);      //Left button  pulled up, push = 0
  digitalWrite(PIN_POWER_ON, HIGH);
  digitalWrite(PIN_LCD_BL, HIGH);
  Serial.begin(115200);  // be sure to set USB CDC On Boot: "Enabled"
  //(Serial print slows progress bar Demo)
  delay(100);
  tft.init();
  tft.setRotation(3);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);  //horiz / vert<> position/dimension
  tft.pushImage(165, 0, 155, 170, hothead);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextFont(2);
  tft.drawString("HotHead!", 10, 50, 4);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextFont(2);
  tft.drawString("Battery Voltage", 10, 80, 2);
  Serial.println("In setup!");
  delay(500);
}

void loop() {
  val = analogRead(analogPin);  // read the input pin
  Serial.println(val*scaling); //must use a voltage divider and calibrated    
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.setCursor(30, 110);  
  tft.print(val*scaling);  //must use a voltage divider and be calibrated   
  tft.setTextSize(1);
  tft.println(" VDC");
  delay(1000);
}
