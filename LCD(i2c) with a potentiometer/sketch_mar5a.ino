#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Initialize LCD: address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
 // Configure ADC for potentiometer reading
 // ADMUX register configuration:
 // Bit 7-6 (REFS1:0) = 01 → AVCC as reference (5V)
 // Bit 5 (ADLAR) = 0 → Right-adjust result
 // Bit 3-0 (MUX3:0) = 0000 → Select ADC0 (A0 pin)
 ADMUX = 0b01000000;

 // ADCSRA register configuration:
 // Bit 7 (ADEN) = 1 → Enable ADC
 // Bit 6 (ADSC) = 0 → Don't start yet
 // Bit 2-0 (ADPS2:0) = 111 → Prescaler = 128
 // ADC Clock = 16MHz / 128 = 125kHz (optimal range)
 ADCSRA = 0b10000111;

 // Initialize I2C LCD
 lcd.init(); // Initialize the LCD
 lcd.backlight(); // Turn on backlight

 // Display startup message
 lcd.setCursor(0, 0);
 lcd.print("Voltage Monitor");
 lcd.setCursor(0, 1);
 lcd.print("Initializing...");

 delay(2000); // Show message for 2 seconds
 lcd.clear();

 // Display static labels
 lcd.setCursor(0, 0);
 lcd.print("ADC:");
 lcd.setCursor(0, 1);
 lcd.print("Voltage:");
}
void loop() {
 // Start ADC conversion
 ADCSRA |= (1 << ADSC); // Set ADSC bit to start

 // Wait for conversion to complete
 // ADSC bit is cleared automatically when done
while (ADCSRA & (1 << ADSC));

 // Read 10-bit ADC result
 uint16_t adcValue = ADC; // ADC register contains result

 // Convert ADC value to voltage
 // ADC resolution: 5V / 1023 = 4.88mV per step
 float voltage = (adcValue / 1023.0) * 5.0;

 // Calculate percentage (0-100%)
 float percentage = (adcValue / 1023.0) * 100.0;

 // Display ADC value on Row 1
 lcd.setCursor(5, 0);
 lcd.print(adcValue);
 lcd.print(" "); // Clear any extra characters

 // Display percentage
 lcd.setCursor(11, 0);
 lcd.print((int)percentage); // No decimal places
 lcd.print("% ");

 // Display voltage on Row 2
 lcd.setCursor(9, 1);
 lcd.print(voltage, 2); // 2 decimal places
 lcd.print("V "); // Clear any extra characters

 delay(200); // Update every 200ms (5 times per second)
}
