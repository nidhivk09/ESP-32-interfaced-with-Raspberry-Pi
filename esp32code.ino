#include <WiFi.h>
#include <SocketIoClient.h>

#include "DHT.h"

#define DHTPIN 4          // Pin where DHT11 is connected
#define DHTTYPE DHT11    // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "NIDHI'S iPhone";       // Your Wi-Fi SSID
const char* password = "n1234567"; // Your Wi-Fi password
//const char* serverUrl = "http://<raspberry_pi_ip>:3000"; 
// URL of your Node.js server
const char* serverIp = "172.18.0.1";  // IP address of your Node.js server
const int serverPort = 3443;                 // Port number of your Node.js server


SocketIoClient socketIO;

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  socketIO.begin(serverUrl);
}

void loop() {
  socketIO.loop();
  delay(2000); // Wait a few seconds between measurements

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Emit sensor data to the Node.js server
  socketIO.emit("sensor_data", "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}");
}
