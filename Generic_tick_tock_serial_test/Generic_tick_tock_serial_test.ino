//words preceded by "//"" are comments and are not executed
bool ticktock;  //declare ticktock as a boolean flag

void setup() {           //runs once on start up
  Serial.begin(115200);  //open the serial port for USB cable
  delay(500);
}

void loop() {            //runs in circles!
  ticktock = !ticktock;  //every pass through reverse the flag
  if (ticktock) {        //test current value of the ticktock flag
    Serial.println("tick");
  } else {  //prints one or the other to the USB port
    Serial.println("tock");
  }
  delay(1000);  //wait for a second and run again!
}