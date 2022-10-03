# LillyGO-T-display-S3-setup-and-examples
LilyGO T-Display S3 setup and examples for Arduino IDE.
The setup of the brand new LilyGO T-Display S3 is not well documented!
Here is what I found that works, with help from watching Youtuber Volos.
Included in this GitHub repository are detailed setup instructions and several
 working, tested, examples.
Installation is "easy" if you know "exactly what to do!"

Step 1, requires that you have already installed the ESP32 board definitions and
are using the latest version. 
(This is covered in many tutorials online, so I will be brief)
If your Arduino IDE does not already have "ESP32 Arduino" as shown paste this:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
into Arduino Preferences, Additional Boards Manager and wait for it to load...
From Arduino Tools, Board: select ESP32 Arduino, ESP32S3 Dev Module. Right at the top!
Please see attached screenshot, "Select Board.png"
Make sure that you change Flash Size to 8M and Partition Scheme to 8M with spiffs.
To enable serial monitor function for debugging, etc, be sure to also set USB CDC On Boot "Enabled".
All settings shown, run on my computer just as shown.
My HotHead.h logo needs to be in the same folder as each sketch.
#include "TFT_eSPI.h" is in with a bunch of files on LilyGO's GitHub. 
You need to download the Zip file from
https://github.com/Xinyuan-LilyGO/T-Display-S3 by pressing
the green button "Code" and after downloading, expand the Zip, placing 
the file folder "T-Display-S3-main; into your Arduino libraries folder...
then find the file "TFT_eSPI" and MOVE it from the folder into the libraries folder.
Don't ask why!
My repository contains two examples of simple documented easy to understand program code. 
The first one to try is "LilyGO_hothead.ino" which demos most of the common things you need to program this board:
1) Include an image
2) Demonstrate the very high speed graphics made possible by an old school 8 bit 
parrallel interface to the LCD instead of SPI or I2C. 50 year old concept, lost and forgotten.
3) The left button higlights the pin number and the right button...the right.
Open the code and read and understand it and you're good to go. 
Try pushing both buttons at once!
The rest of the code is simple and helps you make your own programs.
The second program is :LilyGO_tempsensor_hothead.ino" which just substitutes
a I2C temerature sensor in place of the progress bar.
The sensor is an M5Stack ENV type, but both Adafruit and DFRobot make a 
similar board, but possibly a different I2C address. This is 0x44, but some
are 0x45.
Instead of a library to try and find, I put the sensor code right in line
with the sketch. This also helps you understand how I2C works!!!
You can email me at teastain911@gmail.com.
I'm open to suggestions!
