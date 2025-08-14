#include <IRremote.h>
#include <WiFi.h>
#include <WebServer.h>

#include <map>
#include <string>

// const char* WIFI_NAME = "";
// const char* WIFI_PASSWORD = "";

const char* WIFI_NAME = "";
const char* WIFI_PASSWORD = "";

const uint16_t RECEIVER_OUTPUT = 15;
const uint16_t BAUD_RATE = 9600;
const uint16_t TRANSISTOR_BASE = 4;
const uint16_t DELAY = 10000;

void toggle_tv_power() {
  Serial.println("Sending NEC signal: Address=0xBF00, Command=0x0D");
  IrSender.sendNEC(0xBF00, 0x0D, 0);
}

void change_input() {
  Serial.println("Sending NEC signal: Address=0xBF00, Command=0x0D");
  IrSender.sendNEC(0xBF00, 0x12, 0);
}

void go_up() {
  Serial.println("Up clicked -> Sending NEC signal: Address=0xBF00, Command=0x16");
  IrSender.sendNEC(0xBF00, 0x16, 0);
}

void go_down() {
  Serial.println("Down clicked -> Sending NEC signal: Address=0xBF00, Command=0x17");
  IrSender.sendNEC(0xBF00, 0x17, 0);
}

void go_left() {
  Serial.println("Left clicked -> Sending NEC signal: Address=0xBF00, Command=0x19");
  IrSender.sendNEC(0xBF00, 0x19, 0);
}

void go_right() {
  Serial.println("Right clicked -> Sending NEC signal: Address=0xBF00, Command=0x18");
  IrSender.sendNEC(0xBF00, 0x18, 0);
}

void select() {
  Serial.println("Ok clicked -> Sending NEC signal: Address=0xBF00, command=0x15");
  IrSender.sendNEC(0xBF00, 0x15, 0);
}

void increase_volume() {
  Serial.println("VOL Up clicked -> Sending NEC signal: Address=0xBF00, command=0x44");
  IrSender.sendNEC(0xBF00, 0x44, 0);
}

void decrease_volume() {
  Serial.println("VOL Down clicked -> Sending NEC signal: Address=0xBF00, command=0x43");
  IrSender.sendNEC(0xBF00, 0x43, 0);
}

void increase_channel() {
  Serial.println("CH Up clicked -> Sending NEC signal: Address=0xBF00, command=0x4A");
  IrSender.sendNEC(0xBF00, 0x4A, 0);
}

void decrease_channel() {
  Serial.println("CH Down clicked -> Sending NEC signal: Address=0xBF00, command=0x4B");
  IrSender.sendNEC(0xBF00, 0x4B, 0);
}

void go_back() {
  Serial.println("Back button clicked -> Sending NEC signal: Address=0xBF00, command=0x48");
  IrSender.sendNEC(0xBF00, 0x48, 0);
}

void go_home() {
  Serial.println("Home button clicked -> Sending NEC signal: Address=0xBF00, command=0x20");
  IrSender.sendNEC(0xBF00, 0x20, 0);
}

void open_menu() {
  Serial.println("Menu button clicked -> Sending NEC signal: Address=0xBF00, command=0x14");
  IrSender.sendNEC(0xBF00, 0x14, 0);
}

void toggle_pause() {
  Serial.println("Toggle play button clicked -> Sending NEC signal: Address=0xBF00, command=0xCA");
  IrSender.sendNEC(0xBF00, 0xCA, 0);
}

void mute() {
  Serial.println("Mute button clicked -> Sending NEC signal: Address=0xBF00, command=0xE");
  IrSender.sendNEC(0xBF00, 0xE, 0);
}

void exit() {
  Serial.println("Exit button clicked -> Sending NEC signal: Address=0xBF00, command=0x5C");
  IrSender.sendNEC(0xBF00, 0x5C, 0);
}

void open_netflix() {
  Serial.println("Netflix button clicked -> Sending NEC signal: address=0xBF00, command=0x2D");
  IrSender.sendNEC(0xBF00, 0x2D, 0);
}

void open_amazon_prime() {
  Serial.println("Amazon Prime button clicked -> Sending NEC signal: address=0xBF00, command=0xBB");
  IrSender.sendNEC(0xBF00, 0xBB, 0);
}

void open_youtube() {
  Serial.println("YouTube button clicked -> Sending NEC signal: address=0xBF00, command=0xAA");
  IrSender.sendNEC(0xBF00, 0xAA, 0);
}

void open_showmax() {
  Serial.println("Showmax button clicked -> Sending NEC signal: address=0xBF00, command=0xFA");
  IrSender.sendNEC(0xBF00, 0xFA, 0);
}

void open_dstv() {
  Serial.println("DSTV button clicked -> Sending NEC signal: address=0xBF00, command=0xFB");
  IrSender.sendNEC(0xBF00, 0xFB, 0);
}

void trigger_command(const String& key) {
  std::string std_key = key.c_str();
  if(key_to_signal_map.count(std_key)) {
    key_to_signal_map[std_key]();
    server.send(200, "text/plain", "Executed command: " + key);
  } else {
    server.send(404, "text/plain", "Uknown command: " + key);
  }
}

std::map<std::string, void(*)()> key_to_signal_map = {
  {"POWER", toggle_tv_power},
  {"INPUT", change_input},
  {"UP", go_up},
  {"DOWN", go_down},
  {"LEFT", go_left},
  {"RIGHT", go_right},
  {"SELECT", select},
  {"VOL_UP", increase_volume},
  {"VOL_DOWN", decrease_volume},
  {"CH_UP", increase_channel},
  {"CH_DOWN", decrease_channel},
  {"BACK", go_back},
  {"HOME", go_home},
};

WebServer server(80);
IRrecv ir_recv(RECEIVER_OUTPUT);

void setup() {
  Serial.begin(BAUD_RATE);
  connect_to_wifi();

  WiFi.softAP("ESP32_AP", "12345678");
  Serial.println("Access Point Started");
  Serial.println(WiFi.softAPIP());

  // ✅ Set up server endpoints BEFORE starting the server
  server.on("/", []() {
    server.send(200, "text/plain", "Hello from the other side");
  });

  server.on("/toggle", []() {
    toggle_tv_power();
    server.send(200, "text/plain", "Toggled TV power");
  });

  server.on("/command", []() {
    if(server.hasArg("key")) {
      String key = server.arg("key");
      trigger_command(key);
    } else {
      server.send(400, "text/plain", "Missing 'key' parameter");
    }
  });

  server.begin();  // ✅ Start the server after routes are registered
  Serial.println("HTTP server started");

  IrSender.begin(TRANSISTOR_BASE);
  IrReceiver.begin(RECEIVER_OUTPUT, ENABLE_LED_FEEDBACK);
  Serial.println("Ready to transmit and receive signals...");
}

void loop() {
  try_read_signal();
  server.handleClient();
}

void connect_to_wifi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void try_read_signal() {
  if (IrReceiver.decode()) {
    Serial.println("Read signal from IR remote...");
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();
  }
}


