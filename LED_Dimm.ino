#include <ESP8266WiFi.h>      // 提供Wi-Fi功能的程式庫
#include <ESP8266WebServer.h>  // 提供網站伺服器功能的程式庫
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
#include "index.h"


//const byte ADC_PIN = A0;
//const byte GPIO_4  = 4;
//const byte GPIO_5  = 5;
// Only ESP01 Pin number
//const byte LED_PIN = 0;
const byte PWM_PIN = 2;

// You need to change below const char
const char* host = "test";			 
const char ssid[] = "ssid";
const char pass[] = "password";

ESP8266WebServer server(80);   // 宣告網站伺服器物件與埠號
ESP8266HTTPUpdateServer httpUpdater;
HTTPClient http;

// 定義處理首頁請求的自訂函式
void rootRouter() {
  server.send (200, "text/html", PAGE_INDEX );
}

void setup() {
//  pinMode(LED_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);
//  digitalWrite(PWM_PIN, HIGH);
  analogWrite(PWM_PIN, 0);
  
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  /*
   *  若要指定IP位址，請自行在此加入WiFi.config()敘述。
   WiFi.config(IPAddress(192,168,1,50),    // IP位址
               IPAddress(192,168,1,1),     // 閘道（gateway）位址
               IPAddress(255,255,255,0));  // 網路遮罩（netmask）
   */

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);   // 等待WiFi連線
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());  // 顯示ESP8266裝置的IP位址
 
  server.on ( "/", rootRouter);
  server.on ( "/index.html", rootRouter);
  
  server.on ("/DIMM", []() 
  {
    String state = server.arg("dimm");
    analogWrite(PWM_PIN, state.toInt());
    Serial.print("PWM_PIN: ");
    Serial.println(state);
  });

  server.on ("/TIME", []() {
    String val = server.arg("timevalue");
    Serial.print("TIME: ");
    Serial.println(val);
  });
  
  server.onNotFound([]() {
    server.send(404, "text/plain", "File NOT found!");
  });
  
  MDNS.begin(host);
  Serial.println("mDNS responder started");

  httpUpdater.setup(&server);
  server.begin();
  Serial.println("HTTP server started.");

  MDNS.setInstanceName("Cubie's ESP8266");
  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", host);
}

void loop() {
  server.handleClient();
}

