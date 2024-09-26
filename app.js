const express = require('express');
const mqtt = require('mqtt');
const path = require('path');

const app = express();
const port = 3000;

// Set view engine to EJS
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

// Array to store sensor data
let sensorData = { temperature: null, humidity: null };

// MQTT setup
const mqttBrokerUrl = 'mqtt://broker.hivemq.com'; // Public MQTT broker for testing
const client = mqtt.connect(mqttBrokerUrl);

client.on('connect', () => {
    console.log('Connected to MQTT broker');
    client.subscribe('esp32/sensor_data', (err) => {
        if (!err) {
            console.log('Subscribed to esp32/sensor_data topic');
        }
    });
});

// Handle incoming messages
client.on('message', (topic, message) => {
    const data = JSON.parse(message.toString());
    sensorData.temperature = data.temperature;
    sensorData.humidity = data.humidity;
    console.log(`Received message: ${message.toString()}`);
});

// Serve the main page
app.get('/', (req, res) => {
    res.render('index', { sensorData });
});

// Start the server
app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});