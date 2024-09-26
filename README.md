This project uses Raspbeery Pi processor and an ESP-32 chipset to communicate via wifi using MQTT protocol.
A DHT11 sensor is connected to the ESP-32 board where data is collected.
It uses the RPi to host a node.js server which will be used to display the data from the ESP-32 on a webpage.

STEPS:

1.Create a project directory.
2.Create app.js file in it.
3.Create a folder in the project directory named views.
4.create another file called index.ejs which stores the html code.
5.Also create the arduino file to run the ESP-32 along with the DHT11(humidity and temperature sensor).
6.Host the server by running the app.js file.
7.Run the arduino file and check for wifi connection and MQTT connection.
8.check for packet sent staus and refresh the webpage which displays the data.
