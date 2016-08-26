// include the SD library:
#include <SPI.h>
#include <SD.h>

// Include Wire, and LIS3DH Sensor libraries
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

// Set CS pin, for Feather this is Pin 4
const int chipSelect = 4;

// Define some pins
#define VBATPIN A9
#define LED1 13
#define LED2 8

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

File eggdrop;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  // initialize digital pin 8 as an output.
  pinMode(8, OUTPUT);
  //Setup Serial port for debugging
  Serial.begin(57600);
  Serial.println("\r\nEggDrop Datalogger");
  Serial.println("\r\nFW Rev: 0.1");
  Serial.println("\r\nChecking SD Card");
  delay(2000);
  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    error(2);
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.print("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  Serial.println("Testing LIS3DH Sensor.....");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    error(3);
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

}

float battery(void) {
   
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  Serial.print("VBat: " ); Serial.println(measuredvbat);
  return measuredvbat;
}

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(LED1, HIGH);
      delay(100);
      digitalWrite(LED1, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}



void loop() {
  //Turn on LED2
  digitalWrite(LED2, HIGH);
  //Read the acceldata and battery voltage, create a data string
  //Data string will have the follwoing format
  //AccelX,AccelY,AccelZ,Battery
  //m/s^2,m/s^2,m/s^2,voltage
  String dataString = "";
  dataString = lis.x + "," + lis.y + "," + lis.z + "," + battery();
  
  // Read the battery voltage
  battery();
  //Done, turn off LED
  digitalWrite(LEDD2, LOW);
  delay(1000);
  

}
