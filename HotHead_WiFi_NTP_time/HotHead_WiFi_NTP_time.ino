//This sketch is an example of reading time from NTP
#define CUSTOM_TIMEZONE "CST-8" China time zone
#include <TFT_eSPI.h>
#include "hothead.h"
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <WiFi.h>
#include "Free_Fonts.h"  //free fonts must be included in the folder and in quotes
const char *ssid = "nnnn";
const char *password = "nnnn";
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -18000;
const int daylightOffset_sec = 3600;
int Hours;
int Minutes;
bool ticktock;
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
#define PIN_POWER_ON 15  //power enable pin for LCD and use battery
#define PIN_LCD_BL 38    // BackLight enable pin (see Dimming.txt)
String jsonBuffer;
struct tm timeinfo;

void setup() {
  pinMode(PIN_POWER_ON, OUTPUT);  //enables the LCD and to run on battery
  pinMode(PIN_LCD_BL, OUTPUT);    //triggers the LCD backlight
  digitalWrite(PIN_POWER_ON, HIGH);
  digitalWrite(PIN_LCD_BL, HIGH);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.begin(115200);  // be sure to set USB CDC On Boot: "Enabled"
  WiFi.mode(WIFI_STA);
  tft.fillRect(0, 165, 130, 60, TFT_CYAN);  //horiz, vert
  tft.setFreeFont(FSS9);
  tft.setTextColor(TFT_RED);
  tft.setCursor(30, 50);
  tft.print("in setup");
  tft.init();
  Serial.println("          in setup");
  Serial.println("  ");
  delay(500);
  tft.setRotation(3);
  tft.setSwapBytes(true);
  tft.fillScreen(TFT_BLACK);  //horiz / vert<> position/dimension
  tft.pushImage(165, 0, 155, 170, hothead);
  tft.setTextColor(TFT_RED);
  tft.setFreeFont(FSB12);
  tft.setCursor(5, 25);
  tft.println("HOTHEAD!");
}

void loop() {
  tft.setFreeFont(FSS9);
  Serial.println("In loop!");
  ticktock = !ticktock;
  if (ticktock) {
    Serial.println("tick");
  } else {
    Serial.println("tock");
  }
  printLocalTime();
  tft.fillRect(10, 32, 130, 25, TFT_BLACK);  //horiz, vert
  tft.setTextColor(TFT_GREEN);
  tft.setCursor(30, 50);
  tft.println("looping");
  delay(1000);
}

void printLocalTime() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("!= WL_CONNECTED in printlocalTime");
    Hours = 0;
    Minutes = 0;
    initWiFi();
    delay(1000);
  }
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    Hours = 0;
    Minutes = 0;
    delay(1000);
  }
  //print actual integers
  Serial.println("   ");
  Hours = timeinfo.tm_hour;
  if (Hours >= 13) {
    Hours = Hours - 12;
  }
  if (Hours < 1) {
    Hours = 12;
  }
  Serial.print("Hours = ");
  Serial.println(Hours);
  Minutes = timeinfo.tm_min;
  Serial.print("Minutes = ");
  Serial.println(Minutes);
  tft.setFreeFont(FSS9);
  tft.setTextColor(TFT_CYAN);
  tft.setCursor(30, 80);
  tft.fillRect(0, 63, 170, 70, TFT_BLACK);  //horiz, vert
  tft.print("Hours = ");
  tft.println(Hours);
  tft.setCursor(15, 100);
  tft.print("Minutes = ");
  tft.println(Minutes);
  Serial.println("   ");
  delay(1000);
}

void initWiFi() {
  Serial.println("    Start func init WiFi");
  tft.setFreeFont(FSS9);
  tft.fillRect(10, 32, 130, 25, TFT_BLACK);  //horiz, vert
  tft.setTextColor(TFT_RED);
  tft.setCursor(30, 50);
  tft.println("init WiFi");
  Serial.println("init WiFi");
  delay(500);
  WiFi.begin(ssid, password);
  delay(1000);
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WL  CONNECTED in initWiFi");
    //WiFi.begin(ssid, password);
    tft.fillRect(10, 32, 130, 25, TFT_BLACK);  //horiz, vert
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(30, 50);
    tft.println("connected");
    delay(1000);
  } else {
    Serial.println("WL not CONNECTED in initWiFi");
    tft.fillRect(10, 32, 130, 25, TFT_BLACK);  //horiz, vert
    tft.setTextColor(TFT_GREEN);
    tft.setCursor(30, 50);
    tft.println("No WiFi");
    Hours = 0;
    Minutes = 0;
    delay(1000);
  }
  delay(500);
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  printLocalTime();
}
