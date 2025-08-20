#include <Arduino.h>
#include <WebServer.h>
#include "ir_commands.h"
#include "wifi_utils.h"
#include "server.h"

const uint16_t RECEIVER_OUTPUT = 15;
const uint16_t TRANSISTOR_BASE = 4;
const uint16_t BAUD_RATE = 9600;

void setup() {
  Serial.begin(BAUD_RATE);
  connect_to_wifi();
  create_apn();
  init_routes();

  init_ir(TRANSISTOR_BASE, RECEIVER_OUTPUT);
  Serial.println("Ready to transmit and receive signals...");
}

// unsigned long lastToggle = 0;
// const unsigned long interval = 7000; // 7 seconds

void loop() {
  // unsigned long now = millis();
  //   if (now - lastToggle >= interval) {
  //       toggle_tv_power();
  //       lastToggle = now;
  //   }
  handle_http_requests();
  handle_ir_signal();
}
