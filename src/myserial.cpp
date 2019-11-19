#include "myserial.h"

#define FOSC 16000000L // Clock Speed

void USART_Init(long BAUD) {
  unsigned int ubrr;

  ubrr = (FOSC/16+BAUD/2)/BAUD-1;

  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  
  /* Not Double the USART Transmission Speed */
  UCSR0A = (0<<U2X0);
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 1stop bit */
  UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data) {
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1<<UDRE0)));
  
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

unsigned char USART_Receive(void) {
  /* Wait for data to be received */
  while (!(UCSR0A & (1<<RXC0)));
  
  /* Get and return received data from buffer */
  return UDR0;
}

void print(char *str) {
  char c;
  while ((c = *str++) != 0)
    USART_Transmit(c);
}
