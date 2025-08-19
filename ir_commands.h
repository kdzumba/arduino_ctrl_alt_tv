#ifndef IR_COMMANDS_H
#define IR_COMMANDS_H

#include <Arduino.h>

void toggle_tv_power();
void change_input();
void go_up();
void go_down();
void go_left();
void go_right();
void select();
void increase_volume();
void decrease_volume();
void increase_channel();
void decrease_channel();
void go_back();
void go_home();
void open_menu();
void toggle_pause();
void mute();
void exit();
void open_netflix();
void open_amazon_prime();
void open_youtube();
void open_showmax();
void open_dstv();

void init_ir(uint16_t tx_pin, uint16_t rx_pin);
void handle_ir_signal();

#endif //IR_COMMANDS_H