//words preceded by "//"" are comments and are not executed
bool ticktock; //declare ticktock as a boolean flag

void setup() {          //runs once on start up
pinMode(15, OUTPUT); 
delay (500); 
digitalWrite(15, HIGH);
Serial.begin (115200); //open the serial port for USB cable
}

void loop() {         //runs in circles!
ticktock = !ticktock; //every pass through reverse the flag
  if (ticktock) {     //test current value of the ticktock flag
    Serial.println("tick");  
  } else {             //prints one or the other to the USB port
    Serial.println("tock");
  }
delay (1000);           //wait for a second and run again!
}