//demonstrates ESP+NOW for LilyGO T-Dislay S3
//there are no LCD graphics on this one! The response is via Serial.print()
#include <esp_now.h>
#include <WiFi.h>
#define topbutton 0
#define PIN_POWER_ON 15  // LCD and battery Power Enable !
#define PIN_LCD_BL 38    // BackLight enable pin

//Address of OTHER board         68:   b6:   b3:   21:   63:   18
uint8_t broadcastAddress[] = { 0x68, 0xB6, 0xB3, 0x21, 0x63, 0x18 };//of OTHER
String success;
//Structure example to send data
//Must match the receiver structure  Button.State
//example "digitalWrite (LED, RxButton.State);"
//example "TxButton.State = !M5.BtnA.wasPressed();"
typedef struct struct_message {
  bool State;     //I chose bool for simplicity, it can be any variable type!
} struct_message;

// Create a struct_message to hold outgoing button
struct_message TxButton;
// Create a struct_message to hold incoming button (to turn on this LED)
struct_message RxButton;  //I.E. = incomingReadings

// Register peer
esp_now_peer_info_t peerInfo;

void setup() {
  pinMode(PIN_POWER_ON, OUTPUT);  //triggers the LCD backlight if you add graphics!
  pinMode(PIN_LCD_BL, OUTPUT);    // BackLight enable pin if you add graphics!
  pinMode(topbutton, INPUT);      //Left button  pulled up, push = 0
  delay(100);
  digitalWrite(PIN_POWER_ON, HIGH);
  digitalWrite(PIN_LCD_BL, HIGH);
  Serial.begin(115200);  // be sure to set USB CDC On Boot: "Enabled"
  //(Serial print slows progres bar Demo)
  delay(100);
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("A- Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
  delay(100);
  Serial.println("In setup!");
  delay(1000);
}

void loop() {
  TxButton.State = digitalRead(topbutton);  //***this is where you tramsmit this units button state
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&TxButton, sizeof(TxButton));
  if (result == ESP_OK) {
    //Serial.println("Sent with success");  //un-comment for debugging!
  } else {
    Serial.println("Error sending the data");
  }
  delay(100);
}

// OnDataRecv when data is received, LED is controlled here
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&RxButton, incomingData, sizeof(RxButton));
  //Serial.print("Bytes received: ");   //un-comment for debugging!
  //Serial.println(len);
  Serial.print("RxButton.State=");
  Serial.println(RxButton.State);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //Serial.print("\r\nA- Last Packet Send Status:\t");   //un-comment for debugging!
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0) {
    success = "Delivery Success :)";
  } else {
    success = "Delivery Fail :(";
  }
}
