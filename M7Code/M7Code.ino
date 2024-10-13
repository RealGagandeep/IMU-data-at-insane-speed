#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiSSLClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <Arduino_LSM6DSOX.h>
#include <WiFi.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Gagandeep's S9";
const char* password = "123456789";

WiFiServer server(80);

byte buffer[2000*12];   
void setup() {
  Serial.println("inside setup");
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");


  // Start the web server
  server.begin();
  Serial.println("HTTP server started");



  // Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

}

void loop() {
  int16_t aX, aY, aZ, gX, gY, gZ;
  // Serial.println("YOO");
  for (int i = 0; i<2000; )
  {
    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable())
    {
      IMU.readAcceleration(aX, aY, aZ);
      IMU.readGyroscope(gX, gY, gZ);

      buffer[12*i] = aX & 0xff;
      buffer[12*i + 1] = (aX >> 8);
      buffer[12*i + 2] = aY & 0xff;
      buffer[12*i + 3] = (aY >> 8);
      buffer[12*i + 4] = aZ & 0xff;
      buffer[12*i + 5] = (aZ >> 8);
      buffer[12*i + 6] = gX & 0xff;
      buffer[12*i + 7] = (gX >> 8);
      buffer[12*i + 8] = gY & 0xff;
      buffer[12*i + 9] = (gY >> 8);
      buffer[12*i + 10] = gZ & 0xff;
      buffer[12*i + 11] = (gZ >> 8);
      i++;
    }
  }
  // Serial.write(&buffer[0], 12*12000);

    WiFiClient client = server.available();
    
  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {

      client.write(&buffer[0], 12*2000);
      // client.write("This is transfered data from nicla*****");
      client.println();
      client.stop();
      Serial.println("Data sent to client");
    }
  }
}
