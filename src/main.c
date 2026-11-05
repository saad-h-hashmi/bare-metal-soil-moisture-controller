#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define SOIL_SENSOR_CHANNEL 0U  /* ADC0 / Arduino Uno analog input A0 */
#define RELAY_OUTPUT_PIN    PB0 /* Arduino Uno digital pin D8 */
#define DRY_THRESHOLD       500U

static void adc_init(void) {
    /* Use AVcc as the ADC reference and a 128 prescaler at 16 MHz. */
    ADMUX = (1U << REFS0) | SOIL_SENSOR_CHANNEL;
    ADCSRA = (1U << ADEN) | (1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0);
}

static uint16_t read_soil_sensor(void) {
    ADCSRA |= (1U << ADSC);
    while (ADCSRA & (1U << ADSC)) {
        /* Wait for conversion to complete. */
    }
    return ADC;
}

int main(void) {
    DDRB |= (1U << RELAY_OUTPUT_PIN);
    PORTB &= ~(1U << RELAY_OUTPUT_PIN);
    adc_init();

    while (1) {
        const uint16_t moisture_reading = read_soil_sensor();

        /* Retains the original project rule: ADC readings below 500 activate
           the relay output. Calibrate this threshold and polarity for the
           exact sensor and relay module before connecting a pump. */
        if (moisture_reading < DRY_THRESHOLD) {
            PORTB |= (1U << RELAY_OUTPUT_PIN);
        } else {
            PORTB &= ~(1U << RELAY_OUTPUT_PIN);
        }

        _delay_ms(1000);
    }
}
