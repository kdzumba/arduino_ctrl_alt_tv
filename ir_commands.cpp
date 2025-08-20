#include "ir_commands.h"
#include <IRremote.h>

static IRsend* ir_sender = nullptr;
static IRrecv* ir_receiver = nullptr;

void init_ir(uint16_t tx_pin, uint16_t rx_pin) {
  IrSender.begin(tx_pin);
  IrReceiver.begin(rx_pin, ENABLE_LED_FEEDBACK);
}

void handle_ir_signal() {
  if(IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();
  }
}

void toggle_tv_power() {
  Serial.println("Sending NEC signal: Address=0xBF00, Command=0x0D");
  IrSender.sendNEC(0xBF00, 0x0D, 0);
}

void change_input() {
  Serial.println("Sending NEC signal: Address=0xBF00, Command=0x0D");
  IrSender.sendNEC(0xBF00, 0x12, 0);
}

void go_up() {
  Serial.println("Sending NEC signal: Address=0xBF00, Command=0x16");
  IrSender.sendNEC(0xBF00, 0x16, 0);
}

void go_down() {
  Serial.println("Sending NEC signal: Address=0xBF00, Command=0x17");
  IrSender.sendNEC(0xBF00, 0x17, 0);
}

void go_left() {
  Serial.println("Sending NEC signal: Address=0xBF00, Command=0x19");
  IrSender.sendNEC(0xBF00, 0x19, 0);
}

void go_right() {
  Serial.println("Sending NEC signal: Address=0xBF00, Command=0x18");
  IrSender.sendNEC(0xBF00, 0x18, 0);
}

void select() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0x15");
  IrSender.sendNEC(0xBF00, 0x15, 0);
}

void increase_volume() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0x44");
  IrSender.sendNEC(0xBF00, 0x44, 0);
}

void decrease_volume() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0x43");
  IrSender.sendNEC(0xBF00, 0x43, 0);
}

void go_back() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0x48");
  IrSender.sendNEC(0xBF00, 0x48, 0);
}

void go_home() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0x20");
  IrSender.sendNEC(0xBF00, 0x20, 0);
}

void open_menu() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0x14");
  IrSender.sendNEC(0xBF00, 0x14, 0);
}

void toggle_pause() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0xCA");
  IrSender.sendNEC(0xBF00, 0xCA, 0);
}

void mute() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0xE");
  IrSender.sendNEC(0xBF00, 0xE, 0);
}

void exit() {
  Serial.println("Sending NEC signal: Address=0xBF00, command=0x5C");
  IrSender.sendNEC(0xBF00, 0x5C, 0);
}

void open_netflix() {
  Serial.println("Sending NEC signal: address=0xBF00, command=0x2D");
  IrSender.sendNEC(0xBF00, 0x2D, 0);
}

void open_amazon_prime() {
  Serial.println("Sending NEC signal: address=0xBF00, command=0xBB");
  IrSender.sendNEC(0xBF00, 0xBB, 0);
}

void open_youtube() {
  Serial.println("Sending NEC signal: address=0xBF00, command=0xAA");
  IrSender.sendNEC(0xBF00, 0xAA, 0);
}

void open_showmax() {
  Serial.println("Sending NEC signal: address=0xBF00, command=0xFA");
  IrSender.sendNEC(0xBF00, 0xFA, 0);
}

void open_dstv() {
  Serial.println("Sending NEC signal: address=0xBF00, command=0xFB");
  IrSender.sendNEC(0xBF00, 0xFB, 0);
}

void increase_channel() {
  Serial.println("Increase channel");
}

void decrease_channel() {
  Serial.println("Decrease channel");
}
