#include <Arduino.h>

void USART_Init(long BAUD);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void print(char *str);