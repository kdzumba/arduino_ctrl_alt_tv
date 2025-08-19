#ifndef SERVER_H
#define SERVER_H

#include<Arduino.h>

void trigger_command(const String& key);
void init_routes();
void handle_http_requests();

#endif //SERVER_H