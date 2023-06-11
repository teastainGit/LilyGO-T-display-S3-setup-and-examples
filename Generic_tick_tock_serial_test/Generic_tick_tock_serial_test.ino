bool ticktock = true;

void setup() {
Serial.begin (115200);
}

void loop() {
ticktock = !ticktock;
  if (ticktock) {
    Serial.println("tick");  
  } else {
    Serial.println("tock");
  }
delay (1000);
}