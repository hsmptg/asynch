#include <Arduino.h>
#include "myserial.h"

#define BUFSIZE 10
char cmd[BUFSIZE];
int pos = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  USART_Init(9600);
  print("Hello world!!!\r\n");
}

void loop() {
  char ch;

  ch = USART_Receive();
  USART_Transmit(ch);
  if (ch == '\r') {
    USART_Transmit('\n');
    switch (cmd[0]) {
      case 'l':
        digitalWrite(LED_BUILTIN, cmd[2] != '0');
        break;
      case 'v':
        print("Version 1.0\r\n");
        break;
    }
    pos = 0;
  } else
    if (pos < BUFSIZE)
      cmd[pos++] = ch;
}
