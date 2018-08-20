/* Eggdrop Firmware
 *  By:  Matthew E. Nelson
 *  SW Version 2.5
 *  Compatible HW Rev - Rev E
 *  Updated - July 2017
 *  New firmware for Eggdrop for AerE 160 using new Feather HW and LIS3DH Sensor
 *  This firmware is used for the Eggdrop exercise in AerE 160 at Iowa State University
 *  The purpose of this program is to record acceleration data that determines if an
 *  egg "broke" or not.  Students will also use this data in future Matlab exercises
 *  
 */

 /*Acknowledgements
  * Portions of this code was from the SD Datalogger example and from Adafruit's 
  * LIS3DH example code
  */

/* Hardware
 *  The following hardware was used for this hardware
 *  Adafruit Feather Datalogger
 *  Adafruit LIS3DH Breakout board
 *  3.7 VDC Li-Ion battery
 *  4GB SD Card
 */

 /* Error codes
  *  2 blinks - No SD Card present
  *  3 blinks - No LIS3DH sensor present
  *  4 blinks - Battery below 3.3 VDC
  *  5 blinks - Could not create file on SD Card
  */

// include the SD library:
#include <SPI.h>
#include <SD.h>

// Include Wire, and LIS3DH Sensor libraries
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Set CS pin, for Feather this is Pin 4 on feather
const int chipSelect = 4;

// Define some pins
#define VBATPIN A9
//This is the Red LED, Error and if the egg break
#define LED1 11
//Operation LED - Green, lights up during data recording
#define LED2 12
// The following LEDs are on the feather board and are used mostly for debugging
#define DEBUG1 13
#define DEBUG2 8

//This defines at what level the egg is "broken:
#define EGG_LIMIT 10

// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

File logfile;

//Functions
//This reads the battery voltage on the feather
float battery(void) {
   
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  Serial.print("VBat: " ); Serial.println(measuredvbat);
  return measuredvbat;
}

// blink out an error code
// When we have an error, we will sit here forever since there is a problem that needs to be addressed
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(LED1, HIGH);
      digitalWrite(DEBUG1, HIGH);
      delay(200);
      digitalWrite(LED1, LOW);
      digitalWrite(DEBUG1, LOW);
      delay(300);
    }
    for (i=errno; i<10; i++) {
      delay(500);
    }
  }
}


void setup() {
  // initialize digital pins 8,11,12,13 as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  //Setup Serial port for debugging
  Serial.begin(57600);
  Serial.println("\r\nEggDrop Datalogger");
  Serial.println("\r\nFW Rev: 0.1");
  Serial.println("\r\nChecking SD Card");
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!SD.begin(chipSelect)) {
    //This flashes the error LED 2 times
    Serial.println("Card init. failed!");
    error(2);
  }
  delay(2000);
  Serial.println("\nInitializing SD card...");

  // create a new file
  char filename[15];
  strcpy(filename, "EGG00.TXT");
  for (uint8_t i = 0; i < 100; i++) {
    filename[3] = '0' + i/10;
    filename[4] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  logfile = SD.open(filename, FILE_WRITE);
  if( ! logfile ) {
    Serial.print("Could not create "); 
    Serial.println(filename);
    error(5);
  }
  Serial.print("Writing to "); 
  Serial.println(filename);

  //Now let's print a header to identify the columns
  logfile.println("Acceleration is in m/s^2");
  logfile.println("Accel_X,ACCEL_Y,ACCEL_Z,Voltage");
  logfile.flush();
  

  Serial.println("Testing LIS3DH Sensor.....");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Could not talk to LIS3DH Sensor!");
    //Flashes the error LED 3 times for bad sensor
    error(3);
    while (1);
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");

  //Check battery voltage
  Serial.print("Checking battery voltage...");
  float check_batt;
  check_batt = battery();
  Serial.println(check_batt);
  if (check_batt < 3.3) {
    Serial.println("BATTERY LOW!  RECHARGE!");
    error(4);
  }
}

//Main Loop
void loop() {
  float eggbreak;
  //Turn on LED2
  digitalWrite(LED2, HIGH);
  //Read the acceldata and battery voltage, create a data string
  //Data string will have the follwoing format
  //AccelX,AccelY,AccelZ,Battery
  //m/s^2,m/s^2,m/s^2,voltage
  sensors_event_t event;
  lis.getEvent(&event);
  
  logfile.print(event.acceleration.x);
  logfile.print(",");
  logfile.print(event.acceleration.y);
  logfile.print(",");
  logfile.print(event.acceleration.z);
  logfile.print(",");
  logfile.println(battery());
  logfile.flush();
  int span = 5;
  bool looped = false;
  //Calculate the square sum of the X, Y and Z direction
  eggbreak = sqrt((event.acceleration.x*event.acceleration.x)+(event.acceleration.y*event.acceleration.y)+(event.acceleration.z*event.acceleration.z));
  // Running Average
  // read from the sensor:
  readings[readIndex] = eggbreak;
  // add the reading to the total:
  total = 0.0; // best to just start at zero
  // now get the last span worth of values
  for(int i=0;i<span;i++){
    if(readIndex>=span){//make sure there is enough data to care
      total = total + readings[readIndex-i];
    }
  }
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
    looped = true;
  }

  // calculate the average:
  average = total / numReadings;

  //For debugging we are going to print the average Accel and battery level
  float battv = battery();
  Serial.print("VBat: " ); Serial.println(battv);
  Serial.print("Avg Accel: " ); Serial.println(average);
  
  if (average > EGG_LIMIT) {
    digitalWrite(LED1,HIGH);
    logfile.println("EGGBREAK,EGGBREAK,EGGBREAK,EGGBREAK");
    logfile.flush();
    Serial.print("EGGBREAK DETECTED!!!");
  }
  //Done, turn off LED
  digitalWrite(LED2, LOW);
  delay(100);
  
}
