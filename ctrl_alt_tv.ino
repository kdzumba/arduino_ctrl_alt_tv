#include <Arduino.h>
#include <WebServer.h>
#include "ir_commands.h"
#include "wifi_utils.h"

const uint16_t RECEIVER_OUTPUT = 15;
const uint16_t TRANSISTOR_BASE = 4;
const uint16_t BAUD_RATE = 9600;

WebServer server(80);

void setup() {
  Serial.begin(BAUD_RATE);
  connect_to_wifi();

  server.on("/", []() {
    server.send(200, "text/plain", "Hello from ESP32");
  });
  server.begin();

  init_ir(TRANSISTOR_BASE, RECEIVER_OUTPUT);
  Serial.println("Ready to transmit and receive signals...");
}

void loop() {
  server.handleClient();
  handle_ir_signal();
}
