
    {
    }
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

// 7-segment patterns for Common Cathode (0-9)
// Hex values: 0:0x3F, 1:0x06, 2:0x5B, 3:0x4F, 4:0x66, 5:0x6D, 6:0x7D, 7:0x07, 8:0x7F, 9:0x6F
uint8_t segment_map[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
volatile int8_t current_digit = 0;

void UART_init(unsigned int ubrr) {
	// Set baud rate registers
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	
	// Enable receiver, transmitter, and RX Complete Interrupt
	UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
	
	// Set frame format: 8 data bits, 1 stop bit
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART_send_string(char* str) {
	while (*str) {
		while (!(UCSR0A & (1 << UDRE0))); // Wait for empty transmit buffer
		UDR0 = *str++;
	}
}

// ISR triggers when a character is received from TeraTerm
ISR(USART_RX_vect) {
	char received_char = UDR0; // Read the character from PC

	if (received_char == 'u') {
		// Ascending order logic: 0,1,2...8,9,0...
		current_digit++;
		if (current_digit > 9) current_digit = 0;
	}
	else if (received_char == 'd') {
		// Descending order logic: 9,8,7...1,0,9...
		current_digit--;
		if (current_digit < 0) current_digit = 9;
	}
	else {
		// Notify error if character is not 'u' or 'd'
		UART_send_string("ERR\r\n");
	}
}

int main(void) {
	// Configure PORTD as output for the 7-segment display
	DDRD = 0xFF;
	
	// Initialize UART at 9600 baud (Value 103 for 16MHz)
	UART_init(103);
	
	// Global Interrupt Enable
	sei();

	while (1) {
		// Initially 0 is displayed, then updates based on 'current_digit'
		PORTD = segment_map[current_digit];
	}
}

