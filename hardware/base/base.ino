#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "chelowek";
const char* password = "11111111";

ESP8266WebServer server(80);

void handleRoot() {
  const String insects = handleGetInsects();

  String postForms = "<html>\
    <head>\
      <meta charset=\"utf-8\">\
      <title>ПАК</title>\
      <style>\
        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; font-size: 24px; display: flex; flex-direction: column; align-items: center }\
        h1 { text-align: center; }\
        form { width:100%; max-width: 500px; text-align: center; display: flex; gap: 15px; flex-direction: column; }\
        select { border: 1px solid #ccc; padding: 5px 30px 5px 10px; border-radius: 4px; }\
        input { font-size: 24px; border: none; border-radius: 10px; text-decoration: none; color: white; background: #0B63F6; }\
      </style>\
    </head>\
    <body>\
      <h1>ПАК</h1><br>\
      <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/change\">\
        <label for=\"albedo\">Альбедо в %</label>\
        <input id=\"albedo\" name=\"albedo\" type=\"range\" min=\"0\" max=\"100\" step=\"1\" value=\"\"><br>";
      if (insects) {
        postForms += "<select name=\"selectedInsect\" id=\"insects\">";
        postForms += "</select><br>";
      }
      postForms += "<input type=\"submit\" value=\"Отправить\"><br>";
      postForms += "</form></body>";
      postForms += "<script>";
      postForms += "document.addEventListener(\"DOMContentLoaded\", function(event) {";
      postForms += "const insects ="+ insects+";";
      postForms += "let parent = document.querySelector('#insects');";
      postForms += "for (let i = 0; i < insects.length; i++) {\
                      let newElem = document.createElement( \"option\" );\
                      newElem.textContent = insects[i].insectname;\
                      newElem.name = insects[i].insectname;\
                      newElem.value = insects[i].wavelengthFavorite;\
                      parent.appendChild(newElem);\
                  };";
    postForms += "});";
    postForms += "</script>";
    postForms += "</html>";
  
  server.send(200, "text/html", postForms);
}

void toggleLight(int waveLength) {
  Serial.print(waveLength);
  if (waveLength == 0) {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  else if (waveLength < 500) {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }
  else if (waveLength < 600) {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
  }
  else {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  }
}

String handleGetInsects() {
  String message = "";
  
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://79.174.86.190/insects")) {  // HTTP


    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = http.getString();
        Serial.println(payload);
        message = payload;
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }
    return message;
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { 
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    Serial.println(server.argName(i) + ": " + server.arg(i));
  }
  server.send(404, "text/plain", message);
}

void handleChange() {
  String message = "Settings changed\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { 
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    Serial.println(server.argName(i) + ": " + server.arg(i));
    if (server.argName(i) == "selectedInsect") {
      toggleLight(server.arg(i).toInt());
    }
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) { Serial.println("MDNS responder started"); }

  server.on("/", handleRoot);
  server.on("/change", handleChange);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
