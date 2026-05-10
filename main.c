/*
 * Automatic Night Lamp - DIGITAL INPUT VERSION
 * ATMega32 @ 1MHz
 * LDR on PD0, LED on PB0
 * 
 * NO ADC. Just reads digital HIGH/LOW from voltage divider.
 */

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // Set PD0 as input (LDR input)
    DDRD &= ~(1 << PD0);
    
    // Enable internal pull-up? NO — we have external voltage divider
    // So PORTD bit 0 stays 0
    PORTD &= ~(1 << PD0);
    
    // Set PB0 as output (LED)
    DDRB |= (1 << PB0);
    
    // Start with LED OFF
    PORTB &= ~(1 << PB0);
    
    while (1)
    {
        // Read LDR input (1 = HIGH voltage = DARK)
        if (PIND & (1 << PD0))
        {
            // Dark -> LED ON
            PORTB |= (1 << PB0);
        }
        else
        {
            // Bright -> LED OFF
            PORTB &= ~(1 << PB0);
        }
        
        // Small delay to avoid jitter
        _delay_ms(50);
    }
}