// https://www.arduinoall.com/article/77/nodemcu-esp8266-arduino-48-esp8266-nodemcu-line-notify-%E0%B8%AA%E0%B9%88%E0%B8%87%E0%B8%82%E0%B9%89%E0%B8%AD%E0%B8%84%E0%B8%A7%E0%B8%B2%E0%B8%A1%E0%B8%88%E0%B8%B2%E0%B8%81-nodemcu-%E0%B9%80%E0%B8%82%E0%B9%89%E0%B8%B2-line
//

void Line_Notify(String message) ;

#include 

// Config connect WiFi
#define WIFI_SSID "wifi_ssid" // แก้ชื่อ ssid
#define WIFI_PASSWORD "wifi_password" // แก้รหัสผ่าน

// Line config
#define LINE_TOKEN "W3emOgHLpuCCRoKw55lPaNrHsw9RUicy5vCf" // แก้ LINE TOKEN
String message = "Hello NodeMCU and Line";
String message2 = "%E0%B8%AA%E0%B8%A7%E0%B8%B1%E0%B8%AA%E0%B8%94%E0%B8%B5%20Line%20and%20NodeMCU%20%E0%B8%A2%E0%B8%B4%E0%B8%99%E0%B8%94%E0%B8%B5%E0%B8%97%E0%B8%B5%E0%B9%88%E0%B9%84%E0%B8%94%E0%B9%89%E0%B8%A3%E0%B8%B9%E0%B9%89%E0%B8%88%E0%B8%B1%E0%B8%81";
//Line Notify ยังไม่รองรับภาษาไทย ดังนั้นเราสามารถแปลงข้อความเป็น utf-8 เพื่อส่งเป็นภาษาไทยได้ จาก http://meyerweb.com/eric/tools/dencoder/

void setup() {
Serial.begin(115200);

WiFi.mode(WIFI_STA);
// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");

while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();
Serial.print("connected: ");
Serial.println(WiFi.localIP());
}

void loop() {
Serial.println("Enter !");
Line_Notify(message);
Line_Notify(message2);
Serial.println();
delay(10000);
}

void Line_Notify(String message) {
WiFiClientSecure client;

if (!client.connect("notify-api.line.me", 443)) {
Serial.println("connection failed");
return;
}

String req = "";
req += "POST /api/notify HTTP/1.1\r\n";
req += "Host: notify-api.line.me\r\n";
req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
req += "Cache-Control: no-cache\r\n";
req += "User-Agent: ESP8266\r\n";
req += "Content-Type: application/x-www-form-urlencoded\r\n";
req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
req += "\r\n";
req += "message=" + message;
Serial.println(req);
client.print(req);
delay(20);

Serial.println("-------------");
while (client.connected()) {
String line = client.readStringUntil('\n');
if (line == "\r") {
break;
}
Serial.println(line);
}
Serial.println("-------------");
}
