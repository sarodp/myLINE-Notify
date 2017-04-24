#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

////////////////////////////////////////////////////////
//
// @BotFather
// https://www.unzeen.com/article/3383/
// ﻿การสร้าง Telegram Bot สำหรับส่งข้อมูลแจ้งเตือนจาก ESP8266
//
//////////////////////////////////////////////////////

// WIFI SSID & Password
const char* ssid = "WIFI_SSID";
const char* password = "PASSWORD123";

// Telegram Server API
const int httpsPort = 443;
const char* host = "api.telegram.org";// @BotFather
// https://www.unzeen.com/article/3383/
// ﻿การสร้าง Telegram Bot สำหรับส่งข้อมูลแจ้งเตือนจาก ESP8266

const String AccessToken = "<YOUR_ACCESS_TOKEN>";

const int SwitchPin = 2; // GPIO2
int SwitchOldStatus = HIGH;
int SwitchNewStatus = HIGH;

void setup(void){
  Serial.begin(9600);
  
  pinMode(SwitchPin, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait for connection
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
}

void loop(void){

  // Read Data From Switch
  SwitchNewStatus = digitalRead(SwitchPin);
  
  if(SwitchNewStatus == LOW && SwitchNewStatus != SwitchOldStatus){
    
    String PostData = "text=แจ้งเตือน: สวิตซ์บน ESP8266 ถูกกด&chat_id=<YOUR_CHAT_ID>";

    WiFiClientSecure client;
    Serial.print("connecting to ");
    Serial.println(host);
    
    if (!client.connect(host, httpsPort)) {
      Serial.println("connection failed");
      return;
    }
    
    // POST
    client.print(String("POST ") + "/bot" + AccessToken + "/sendMessage HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
             "User-Agent: ESP8266-Notification\r\n" +
             "Content-Type: application/x-www-form-urlencoded\r\n" +
             "Cache-Control: no-cache\r\n" +
             "Content-Length: " + String(PostData.length()) + "\r\n" +
             "\r\n" +
             PostData);

    // Header
    Serial.println("-------Response Header-------");
    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        break;
      }

      Serial.println(line);
    }

    // Body
    Serial.println("-------Response Body-------");
    String body = client.readStringUntil('\n');
    Serial.println(body);  

  }

  SwitchOldStatus = SwitchNewStatus;
  delay(500);
}
 
