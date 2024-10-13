// #include <ArduinoBLE.h>
#include <Arduino_LSM6DSOX.h>
// #include <SPI.h>
#include <SD.h>
File myFile;
char buffer[20];
int16_t A, B, C, X, Y, Z;

void setup()
{
  // RPC.begin();
  //       while (!Serial) {
  //   ;  // wait for serial port to connect. Needed for native USB port only
  // }
  Serial.begin(9600);
  Serial.println("setup is running");
  // delay(5000);
  if (!IMU.begin())
    Serial.println("Failed to initialize IMU!");
  else
    Serial.println("Initialized IMU");
  if (!SD.begin(SS))
    {Serial.println("initialization failed!");
    while (1);
    }
  else
    Serial.println("Initialized SD");
  myFile = SD.open("dataFile.txt", FILE_WRITE);
}

void loop()
{ 
        // while (!Serial) {
    // ;  // wait for serial port to connect. Needed for native USB port only}
  Serial.println("loop is running");
  Serial.print(IMU.accelerationAvailable() && IMU.gyroscopeAvailable());

    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) 
    {
      IMU.readAcceleration(A, B, C);

      Serial.println("here inside the if ");
      IMU.readGyroscope(X, Y, Z);

      // t1 = micros();
      sprintf(buffer, "%.3d,%.3d,%.3d,%.3d,%.3d,%.3d", A, B, C, X, Y, Z);
      myFile.println(buffer);
      myFile.flush();
      // t2 = micros();

      // Serial.println(t2-t1);
      delay(1000);
    }
}
