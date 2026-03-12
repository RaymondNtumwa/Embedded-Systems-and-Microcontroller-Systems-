#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void setupADC() {
    ADMUX = 0b01000000;   // AVCC reference, ADC0
    ADCSRA = 0b10000111;  // Enable ADC, prescaler 128
}

uint16_t readADC() {
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

void setupTimer1Servo() {
    DDRB |= (1 << PB1);  // PB1 = D9

    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // prescaler 8
    ICR1 = 39999;  // 20 ms period
}

void setServoAngle(uint8_t angle) {
    if (angle > 180) angle = 180;
    uint16_t pulseWidth = 2000 + (angle * 2000UL / 180);
    OCR1A = pulseWidth;
}

void setupUART(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    UCSR0A = 0x00;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uartTransmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uartPrintString(const char *str) {
    while (*str) {
        uartTransmit(*str++);
    }
}

void uartPrintNumber(uint16_t num) {
    char buffer[6];
    uint8_t i = 0;

    if (num == 0) {
        uartTransmit('0');
        return;
    }

    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i > 0) {
        uartTransmit(buffer[--i]);
    }
}

void setup() {
    setupADC();
    setupTimer1Servo();
    setupUART(103);   // 9600 baud
}

void loop() {
    uint16_t adcValue = readADC();
    uint8_t angle = (adcValue * 180UL) / 1023;

    setServoAngle(angle);

    uartPrintString("ADC: ");
    uartPrintNumber(adcValue);
    uartPrintString("  Angle: ");
    uartPrintNumber(angle);
    uartPrintString("\r\n");

    _delay_ms(200);
}