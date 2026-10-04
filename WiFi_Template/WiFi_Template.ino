#include <WiFi.h>
#include <WebServer.h>
#include "WiFi_Configs.h"

// This project creates the a rough template for ESP32 WiFi usage using the Arduino IDE.

// The ESP32 creates an HTTP server, which allows the HTTP client to POST or GET data from it.
// Posting data sends data to the server, and getting data recieves data from it.

// GENERAL STATUS CODES:
// 200 -> OK
// 404 -> NOT FOUND
// 500 -> Server Error


WebServer server(PORT_ID); // create a WebServer object named server to listen on network port 80

void handleData() {

  String data = server.arg("plain"); // set a string variable data equal to the raw body of the
                                    // http request
  Serial.println("Recieved:");
  Serial.println(data);

  server.send(200, "text/plain", "ESP recieved data"); // send 200 status code [request succeeded],
                                                       // then a normal plain text with a body of,
                                                       // "ESP recieved data" back to the http client
}

void setup() {
  Serial.begin(115200);

  // Connect to WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // While connecting
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Prints Status
  Serial.println();
  Serial.println("Connected!");

  // Prints ESP's IP
  Serial.println();
  Serial.println("ESP IP: ");
  Serial.println(WiFi.localIP());


  // Prints reachable server 
  Serial.println();
  Serial.println("Reachable Server @: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(PORT_ID);

  server.on("/data", HTTP_POST, handleData); // Register an /data endpoint so that when the server 
                                            // recieves an HTTP post at /data, handleData() is ran.
  server.begin(); // start listening for connections
}

void loop() {
  server.handleClient(); // check for and process incoming HTTP requests
}
