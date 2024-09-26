#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define DHTPIN 16          // Pin where DHT11 is connected
#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "wifiname";
const char* password = "wifipassword";

const char* mqttBrokerUrl = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    dht.begin();
    delay(2000);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
   Serial.println("connected to wifi");
    client.setServer(mqttBrokerUrl, 1883); // Set MQTT server and port
}

void loop() {

float humidity = dht.readHumidity(0);
    float temperature = dht.readTemperature();

//          Serial.print("Humidity: ");
//  Serial.print(humidity);
//  Serial.print(" %\t");
//  Serial.print("Temperature: ");
//  Serial.print(temperature);
//  Serial.println(" *C");
    if (!client.connected()) {
        reconnect(); // Reconnect if not connected
    }
    
    client.loop();

  

    if (!isnan(humidity) && !isnan(temperature)) {
        String jsonData = "{\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";
        
        client.publish("esp32/sensor_data", jsonData.c_str());
        Serial.println("Data sent: " + jsonData);

//        Serial.print("Humidity: ");
//  Serial.print(humidity);
//  Serial.print(" %\t");
//  Serial.print("Temperature: ");
//  Serial.print(temperature);
//  Serial.println(" *C");

        
        delay(5000); // Send data every 5 seconds
    }
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client")) {
            Serial.println("ESP 32 connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            delay(5000);
        }
    }
}
