#include <avr/io.h>

#include "AvrUtils.h"

#include "config.h"

#include "ValveController.h"

ValveController::ValveController(Port port, uint8_t pin) : 
    port(port),
    pin(pin),
    openPeriod(0) {
}

void ValveController::run() {
    // If the valve is already closed, there is nothing to do.
    if (!openPeriod) {
        return;
    }

    openPeriod--;

    // If the open period concluded right now, close the valve.
    if (!openPeriod) {
        switch (port) {
        case A:
            PORTA &= ~BV(pin);
            break;
        case B:
            PORTB &= ~BV(pin);
            break;
        case C:
            PORTC &= ~BV(pin);
            break;
        case D:
            PORTD &= ~BV(pin);
            break;
        default:
            break;
        }
    }
}

void ValveController::open(uint16_t period) {
    switch (port) {
    case A:
        PORTA |= BV(pin);
        break;
    case B:
        PORTB |= BV(pin);
        break;
    case C:
        PORTC |= BV(pin);
        break;
    case D:
        PORTD |= BV(pin);
        break;
    default:
        break;
    }

    openPeriod = period;
}
