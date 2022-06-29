//use this app
//https://play.google.com/store/apps/details?id=com.shredder.intercom
//as token you may use random words like "abrakadabra3319REFdsf4tfhgbdfefaraf"

#define SSID1 "WIRELESS"
#define PASSWORD1 "PASSWORD"
#define DEBUG 1
#define UNLOCK 2
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

  WiFiClient client;
  HTTPClient http;

String payload;
int httpCode;
byte cnt;
void setup(){
  if(DEBUG)Serial.begin(115200);
  WiFi.begin(SSID1, PASSWORD1);
  if(DEBUG)Serial.println(SSID1);
  if(DEBUG)Serial.println(PASSWORD1);
  while(WiFi.status()!= WL_CONNECTED){
      if(DEBUG)Serial.print(".");
      delay(400);
      cnt++;
      if (cnt > 30)ESP.restart();
  }
  if(DEBUG)Serial.println("wifi ok");
  pinMode(UNLOCK, OUTPUT);
}

void loop(){
  http.begin(client,"http://ruelf.ru/tokens.php?id=qwerty&type=get");
   httpCode = http.GET();
   payload = http.getString();
   if(payload.length()>10)payload="err";
   if(DEBUG)Serial.println(payload);
   if(payload != "1")digitalWrite(UNLOCK, HIGH);else digitalWrite(UNLOCK, LOW);
  http.end();
  delay(500);
}
