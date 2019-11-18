#include <Arduino.h>

#define RAW

#ifdef RAW
#define FOSC 16000000L // Clock Speed
#define BAUD 115200
#define MYUBRR (FOSC/16+BAUD/2)/BAUD-1

void USART_Init(unsigned int ubrr) {
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
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
#endif

void setup() {
#ifdef RAW
  USART_Init(MYUBRR);
#else
  Serial.begin(115200);
#endif
}

void loop() {
#ifdef 0
  static unsigned char c = 'A';
  USART_Transmit(c++);
  delay(500);
#else
  Serial.print("tick... ");
  delay(500);
  Serial.println("tack!");
  delay(500);
#endif
}