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
#define THRESHOLD 1300
//Set's the Acceleration range, choices are 2,4,8, or 16 +/- g
#define RANGE 4

void setup() {
  // Setup the Bean serial port
  Serial.begin();
  // Set the acceleration range on the bean to +/- 4g
  Bean.setAccelerationRange(RANGE);
  // Enable Wake on Connection
  Bean.enableWakeOnConnect(true);
}

void loop() {
  bool connected = false;
  connected = Bean.getConnectionState();
  uint16_t batt;
  int16_t mag;
  
  // Turn the Bean's LED green  
  Bean.setLed(0, 255, 0);
  Bean.sleep(20);
  Bean.setLed(0, 0, 0);

  //batt = batteryLevel();
  mag = accelMagnitude();
  
  
  //Grabs the battery voltage and formats the string for printing
  //uint16_t batteryReading =  Bean.getBatteryVoltage();
  //String stringToPrintBatt = String();
  //stringToPrintBatt = stringToPrintBatt + batteryReading/100 + "." + batteryReading%100;

  //This grabs the x,y,z acceleration data and we put together a string for printing
  //AccelerationReading acceleration = Bean.getAcceleration();
  //uint32_t magnitude = abs(acceleration.xAxis) + abs(acceleration.yAxis) + abs(acceleration.zAxis);
  //int16_t xaxis = abs(convertToMg(acceleration.xAxis,acceleration.sensitivity));
  //int16_t yaxis = abs(convertToMg(acceleration.yAxis,acceleration.sensitivity));
  //int16_t zaxis = abs(convertToMg(acceleration.zAxis,acceleration.sensitivity));

  // Format the serial output like this: "mag,x-axis,yaxis,zaxis,battery_voltage"
  //String stringToPrintAcc = String();
  //stringToPrintAcc = stringToPrintAcc + magnitude + "," + xaxis/1000 + "." + xaxis%1000 + "," + yaxis/1000 + "." + yaxis%1000 + "," + zaxis/1000 + "." + zaxis%1000 + ",";
  //Serial.print(stringToPrintAcc);
  //Serial.println(stringToPrintBatt);

  //Check to see if we "broke" the egg
   if(mag > THRESHOLD){
    Bean.setLed(255,0,0);
    Serial.println("I'm broke!");
    Serial.println("-------------------------");
    Bean.sleep(15000);
   }
  
  //This puts the bean into a sleep mode. 
  Bean.sleep(100);
}

//------------------------------------------------------------------------------------
// Below are functions used in this program

// This functions helps convert the raw acceleration data to the milli g.  Taken from 
// from this website - http://legacy.punchthrough.com/bean/the-arduino-reference/accelerationreading/
int16_t convertToMg(int16_t rawAcceleration, uint8_t sensitivity)
{
   int32_t convertedValue = (int32_t)rawAcceleration * (int32_t)sensitivity * 1000L;
   convertedValue /= 511;
 
   return (int16_t)convertedValue;
}

//Take a battery reading and send it to the serial port and return the value.
uint16_t batteryLevel(void)
{
  uint16_t level = Bean.getBatteryLevel();

  Serial.print("Battery level %: ");
  Serial.println(level, DEC);

}

//Take the X,Y,Z acceleration and find the magnitude, then print this and return it

int16_t accelMagnitude(void)
{
  
  AccelerationReading accel = {0, 0, 0};
  accel = Bean.getAcceleration();
  int32_t magnitude = sqrt((accel.xAxis*accel.xAxis) + (accel.yAxis * accel.yAxis) + (accel.zAxis * accel.zAxis));
  int32_t gs = (magnitude * RANGE * 1000L)/511;
  Serial.print("Accel:");
  Serial.println(gs);
  //Serial.print(accel.xAxis,DEC);
  //Serial.print(",");
  //Serial.print(accel.yAxis,DEC);
  //Serial.print(",");
  //Serial.println(accel.zAxis,DEC);
  return (int16_t)gs;

}

