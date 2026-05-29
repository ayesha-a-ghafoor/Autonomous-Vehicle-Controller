#define F_CPU 16000000UL // 16 MHz Clock (Arduino Uno Standard)
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

// --- Macros for Motor Control (safely only changing PD4-PD7) ---
#define MOTOR_MASK ((1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7))

void init_hardware() {
// 1. Motor Pins (PD4-PD7) & Buzzer (PD2) as Output
DDRD |= MOTOR_MASK | (1 << DDD2);

// 2. Ultrasonic Pins: Trig (PC0) as Output, Echo (PC1) as Input
DDRC |= (1 << DDC0);
DDRC &= ~(1 << DDC1);

// 3. Servo (PB1), Red LED (PB0) & Yellow LED (PB2) as Output
DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2);

// 4. Timer 1 Setup for Servo PWM on PB1 (Fast PWM, Top=ICR1)
TCCR1A |= (1 << COM1A1) | (1 << WGM11);
TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler 8
ICR1 = 39999; // 20ms period (50Hz)
}

void set_servo(int angle) {
// Map 0-180 degrees to pulse width (approx 1000 to 4800)
OCR1A = 1000 + (angle * 21);
}

uint16_t get_distance() {
// Send 10us Trigger Pulse
PORTC &= ~(1 << PORTC0);
_delay_us(2);
PORTC |= (1 << PORTC0);
_delay_us(10);
PORTC &= ~(1 << PORTC0);

// Wait for Echo to go High (with timeout)
uint16_t count = 0;
while (!(PINC & (1 << PINC1)) && count < 65000) count++;

// Measure how long Echo stays High
uint16_t duration = 0;
while ((PINC & (1 << PINC1)) && duration < 65000) {
_delay_us(1);
duration++;
}

return duration / 58; // Convert microseconds to cm
}

// --- Movement Functions ---
void move_forward() {
PORTD = (PORTD & ~MOTOR_MASK) | (1 << PD4) | (1 << PD6);
}

void move_backward() {
PORTD = (PORTD & ~MOTOR_MASK) | (1 << PD5) | (1 << PD7);
}

void turn_left() {
PORTD = (PORTD & ~MOTOR_MASK) | (1 << PD4) | (1 << PD7);
}

void turn_right() {
PORTD = (PORTD & ~MOTOR_MASK) | (1 << PD5) | (1 << PD6);
}

void stop_motors() {
PORTD &= ~MOTOR_MASK; // Set all motor pins to LOW
}

int main(void) {
init_hardware();
set_servo(90); // Look straight

// Welcome Beep
PORTD |= (1 << PORTD2); // Buzzer ON
_delay_ms(100);
PORTD &= ~(1 << PORTD2); // Buzzer OFF
_delay_ms(1000);

while (1) {
uint16_t distance = get_distance();

if (distance > 0 && distance < 25) {
stop_motors();

// Obstacle Warning: Buzzer Beep
PORTD |= (1 << PORTD2);
_delay_ms(200);
PORTD &= ~(1 << PORTD2);

move_backward();
_delay_ms(400);
stop_motors();

// Look Left
set_servo(170);
_delay_ms(500);
uint16_t left_dist = get_distance();

// Look Right
set_servo(10);
_delay_ms(500);
uint16_t right_dist = get_distance();

// Center Head
set_servo(90);
_delay_ms(500);

// Decision Making
if (left_dist >= right_dist) {
PORTB |= (1 << PORTB0); // Red LED ON
turn_left();
_delay_ms(600);
PORTB &= ~(1 << PORTB0); // Red LED OFF
} else {
PORTB |= (1 << PORTB2); // Yellow LED ON
turn_right();
_delay_ms(600);
PORTB &= ~(1 << PORTB2); // Yellow LED OFF
}
stop_motors();
} else {
// Path is clear
move_forward();
}
_delay_ms(50); // Small loop delay
}
} isko samjhao like A-z kh kia hia aur kaisay hia yai libraray q use ki h9a wagira sb