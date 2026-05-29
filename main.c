

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

// --- Pin Mapping ---
// Motors: PD4, PD5, PD6, PD7 (corresponds to Arduino 4, 5, 6, 7)
// Trigger: PC0 (Arduino A0)
// Echo: PC1 (Arduino A1)
// Servo: PB1 (Arduino 9 - Using Timer 1 for PWM)

void init_hardware() {
	// Set PD4-PD7 as Output for Motors
	DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
	
	// Set PC0 (Trig) as Output, PC1 (Echo) as Input
	DDRC |= (1 << DDC0);
	DDRC &= ~(1 << DDC1);
	
	// --- Servo PWM Setup (Timer 1) ---
	DDRB |= (1 << DDB1); // Set PB1 as Output
	// Fast PWM, Top=ICR1, Clear OC1A on Compare Match
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
	ICR1 = 39999; // 20ms period for servo
}

void set_servo(int angle) {
	// Map 0-180 degrees to pulse width (approx 1000 to 4800)
	OCR1A = 1000 + (angle * 21);
}

uint16_t get_distance() {
	PORTC &= ~(1 << PORTC0);
	_delay_us(2);
	PORTC |= (1 << PORTC0);
	_delay_us(10);
	PORTC &= ~(1 << PORTC0);
	
	uint16_t count = 0;
	while (!(PINC & (1 << PINC1)) && count < 65000) count++; // Wait for High
	
	uint16_t duration = 0;
	while ((PINC & (1 << PINC1)) && duration < 65000) {
		_delay_us(1);
		duration++;
	}
	return duration / 58; // Convert to cm
}

// --- Movement Functions ---
void move_forward() {
	PORTD = (1 << PD4) | (1 << PD6); // IN1 and IN3 HIGH
}

void stop_motors() {
	PORTD &= ~((1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
}

int main(void) {
	init_hardware();
	set_servo(90); // Look forward
	_delay_ms(1000);

	while (1) {
		if (get_distance() < 20) {
			stop_motors();
			_delay_ms(500);
			
			// Basic Logic: Look left/right (simplified for pure C)
			set_servo(10); // Look Right
			_delay_ms(500);
			uint16_t d_right = get_distance();
			
			set_servo(170); // Look Left
			_delay_ms(500);
			uint16_t d_left = get_distance();
			
			set_servo(90); // Center
			_delay_ms(500);
			
			if (d_left > d_right) {
				PORTD = (1 << PD4) | (1 << PD7); // Turn Left
				} else {
				PORTD = (1 << PD5) | (1 << PD6); // Turn Right
			}
			_delay_ms(500);
			stop_motors();
			} else {
			move_forward();
		}
	}
}