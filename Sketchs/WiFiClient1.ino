/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "Keenetic-8750";
const char* password = "19lolo55";

const char* host = "192.168.1.35";
const char* streamId   = "....................";
const char* privateKey = "....................";

void setup() {
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 666;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String str= ""; 
  while (str != "poki")
  {
    while (Serial.available() == 0) {}

    char incomingBytes[10];
    char sendingBytes[10];
    
    if (Serial.available() > 0)
     {
        Serial.readBytes(incomingBytes, 9);
        int i = 0;
        str = "";
        while (incomingBytes[i] != '\r')
        {
          str+=incomingBytes[i];
          i++;
        }
        client.println(str);
     }
     
    
    //client.print("Hello");             
    int timeout = millis() + 5000;
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
  }

  client.stop();
  Serial.println();
  Serial.println("closing connection");
}

