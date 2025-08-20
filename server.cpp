#include "server.h"
#include "ir_commands.h"
#include <map>
#include <string>
#include <WebServer.h>

static WebServer web_server(80);

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
  {"NETFLIX", open_netflix},
  {"SHOWMAX", open_showmax},
  {"YOUTUBE", open_youtube},
  {"PRIME", open_amazon_prime},
  {"DSTV", open_dstv}
};

void init_routes() {
  web_server.on("/command", [&web_server]() {
    if(web_server.hasArg("key")) {
      String key = web_server.arg("key");
      trigger_command(key);
    } else {
      web_server.send(400, "text/plain", "Missing 'key' parameter");
    }
  });

  web_server.on("/toggle", [&web_server]() {
    toggle_tv_power();
    web_server.send(200, "text/plain", "Toggled TV power");
  });

  web_server.begin();
}

void trigger_command(const String& key) {
  std::string std_key = key.c_str();
  if(key_to_signal_map.count(std_key)) {
    key_to_signal_map[std_key]();
    web_server.send(200, "text/plain", "Executed command: " + key);
  } else {
    web_server.send(404, "text/plain", "Uknown command: " + key);
  }
}

void handle_http_requests() {
  web_server.handleClient();
}
