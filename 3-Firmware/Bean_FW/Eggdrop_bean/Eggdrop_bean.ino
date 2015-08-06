/* 
  Egg Drop Firmware
  Matthew E. Nelson
  Iowa State University

  Code based from the GetAcceleration demo program.
  
  This program reads the Bean's acceleration data and battery voltage, it then sends this data
  out over the Bluetooth serial line for logging and real-time monitoring.  In addition, if the values
  exceed a preset limit, then it will turn the LED red, otherwise it does a short flash green

*/

//Defines the threshold for a "broken" egg
#define THRESHOLD 400
//Set's the Acceleration range, choices are 2,4,8, or 16 +/- g
#define RANGE 4

void setup() {
  // Setup the Bean serial port
  Serial.begin();
  // Set the acceleration range on the bean to +/- 4g
  Bean.setAccelerationRange(4);
}

void loop() {
  // Turn the Bean's LED green  
  Bean.setLed(0, 255, 0);
  Bean.sleep(20);
  Bean.setLed(0, 0, 0);
  //Grabs the battery voltage and formats the string for printing
  uint16_t batteryReading =  Bean.getBatteryVoltage();
  String stringToPrintBatt = String();
  stringToPrintBatt = stringToPrintBatt + batteryReading/100 + "." + batteryReading%100;

  //This grabs the x,y,z acceleration data and we put together a string for printing
  AccelerationReading acceleration = Bean.getAcceleration();
  uint32_t magnitude = abs(acceleration.xAxis) + abs(acceleration.yAxis) + abs(acceleration.zAxis);
  int16_t xaxis = abs(convertToMg(acceleration.xAxis,acceleration.sensitivity));
  int16_t yaxis = abs(convertToMg(acceleration.yAxis,acceleration.sensitivity));
  int16_t zaxis = abs(convertToMg(acceleration.zAxis,acceleration.sensitivity));

  // Format the serial output like this: "mag,x-axis,yaxis,zaxis,battery_voltage"
  String stringToPrintAcc = String();
  stringToPrintAcc = stringToPrintAcc + magnitude + "," + xaxis/1000 + "." + xaxis%1000 + "," + yaxis/1000 + "." + yaxis%1000 + "," + zaxis/1000 + "." + zaxis%1000 + ",";
  Serial.print(stringToPrintAcc);
  Serial.println(stringToPrintBatt);

  //Check to see if we "broke" the egg
   if(magnitude > THRESHOLD){
    Bean.setLed(255,0,0);
    Serial.println("I'm broke!");
    Serial.println("-------------------------");
    Bean.sleep(5000);
   }
  
  //This puts the bean into a sleep mode.  Currently set to 1 sec. 
  Bean.sleep(150);
}

// This functions helps convert the raw acceleration data to the milli g.  Taken from 
// from this website - http://legacy.punchthrough.com/bean/the-arduino-reference/accelerationreading/
int16_t convertToMg(int16_t rawAcceleration, uint8_t sensitivity)
{
   int32_t convertedValue = (int32_t)rawAcceleration * (int32_t)sensitivity * 1000L;
   convertedValue /= 511;
 
   return (int16_t)convertedValue;
}



