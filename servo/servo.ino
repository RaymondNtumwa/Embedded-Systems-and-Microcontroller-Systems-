#include <avr/io.h> 
#include <util/delay.h> 
 
void setupTimer1Servo() { 
    DDRB |= (1 << PB1);  // Pin 9 output 
     
    // Fast PWM, ICR1 as TOP, prescaler 8 
    TCCR1A = (1 << COM1A1) | (1 << WGM11); 
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); 
     
    ICR1 = 39999;  // 50 Hz frequency 
} 
 
void setServoAngle(uint8_t angle) { 
    // Map angle (0-180) to pulse width (1000-2000 µs) 
    // OCR1A range: 2000-4000 (for 1ms-2ms at 2MHz timer clock) 
    uint16_t pulseWidth = 2000 + (angle * 2000L / 180); 
    OCR1A = pulseWidth; 
} 
 
int main(void) { 
    setupTimer1Servo(); 
     
    while(1) { 
        setServoAngle(0);    // Move to 0° 
        _delay_ms(1000); 
         
        setServoAngle(45);   // Move to 45° 
        _delay_ms(1000); 
         
        setServoAngle(90);   // Move to 90° (center) 
        _delay_ms(1000); 
         
        setServoAngle(135);  // Move to 135° 
        _delay_ms(1000); 
         
        setServoAngle(180);  // Move to 180° 
        _delay_ms(1000); 
    } 
     
    return 0; 
}