// Firmware for a machine producing a pattern of rain drops using solenoid
// valves.
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi
// Date: 2018-02-16

#include "AvrUtils.h"

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

#include "ValveController.h"

uint32_t indicatorCounter = 0;

/// \brief
///    Toggles the indicator led state.
void toggleIndicator() {
    static bool lit;

    if (lit) {
        INDICATOR_DATA &= ~BV(INDICATOR_DATA_PIN);
    }
    else {
        INDICATOR_DATA |= BV(INDICATOR_DATA_PIN);
    }

    lit = !lit;
}

int main() {
    // Indicator pin as output
    INDICATOR_DATA_DIR |= BV(INDICATOR_DATA_DIR_PIN);

    // Flush button is input with pullup enable
    FLUSH_BUTTON_DATA |= BV(FLUSH_BUTTON_DATA_PIN);

    // Valce control pins as output
    VALVE_MIDDLE_DATA_DIR |= BV(VALVE_MIDDLE_DATA_DIR_PIN);
    VALVE_1_DATA_DIR |= BV(VALVE_1_DATA_DIR_PIN);
    VALVE_2_DATA_DIR |= BV(VALVE_2_DATA_DIR_PIN);
    VALVE_3_DATA_DIR |= BV(VALVE_3_DATA_DIR_PIN);
    VALVE_4_DATA_DIR |= BV(VALVE_4_DATA_DIR_PIN);
    VALVE_5_DATA_DIR |= BV(VALVE_5_DATA_DIR_PIN);
    VALVE_6_DATA_DIR |= BV(VALVE_6_DATA_DIR_PIN);

    // Initialize valve controllers
    ValveController controllerMiddle(
        VALVE_MIDDLE_DATA_REF,
        VALVE_MIDDLE_DATA_PIN
    );
    ValveController controller1(VALVE_1_DATA_REF, VALVE_1_DATA_PIN);
    ValveController controller2(VALVE_2_DATA_REF, VALVE_2_DATA_PIN);
    ValveController controller3(VALVE_3_DATA_REF, VALVE_3_DATA_PIN);
    ValveController controller4(VALVE_4_DATA_REF, VALVE_4_DATA_PIN);
    ValveController controller5(VALVE_5_DATA_REF, VALVE_5_DATA_PIN);
    ValveController controller6(VALVE_6_DATA_REF, VALVE_6_DATA_PIN);

    uint32_t patternCounter = 0;

    while (true) {

        if (indicatorCounter == INDICATOR_HALF_PERIOD) {
            indicatorCounter = 0;
            toggleIndicator();
        }
        else {
            indicatorCounter++;
        }

        patternCounter++;

        // Single drop in the middle
        if (patternCounter == 1) {
            controllerMiddle.open(DROP_SIZE);
        }

        // Single drop on one vertex
        else if (patternCounter == 10*SECOND) {
            controller1.open(DROP_SIZE);
        }

        // Single drop on opposite side
        else if (patternCounter == 20*SECOND) {
            controller4.open(DROP_SIZE);
        }

        // Triangle shape followed by drop in the middle
        else if (patternCounter == 30*SECOND) {
            controller1.open(DROP_SIZE);
            controller3.open(DROP_SIZE);
            controller5.open(DROP_SIZE);
        }
        else if (patternCounter == 32*SECOND) {
            controllerMiddle.open(DROP_SIZE);
        }

        // Triangle and middle
        else if (patternCounter == 42*SECOND) {
            controller2.open(DROP_SIZE);
            controller4.open(DROP_SIZE);
            controller6.open(DROP_SIZE);
            controllerMiddle.open(DROP_SIZE);
        }

        // Hexagon
        else if (patternCounter == 52*SECOND) {
            controller1.open(DROP_SIZE);
            controller2.open(DROP_SIZE);
            controller3.open(DROP_SIZE);
            controller4.open(DROP_SIZE);
            controller5.open(DROP_SIZE);
            controller6.open(DROP_SIZE);
        }

        // Triangle followed by the other triangle
        else if (patternCounter == 62*SECOND) {
            controller2.open(DROP_SIZE);
            controller4.open(DROP_SIZE);
            controller6.open(DROP_SIZE);
        }
        else if (patternCounter == 62*SECOND + 5*DECI_SECOND) {
            controller1.open(DROP_SIZE);
            controller3.open(DROP_SIZE);
            controller5.open(DROP_SIZE);
        }

        // Spiral hexagon
        else if (patternCounter == 73*SECOND) {
            controller1.open(DROP_SIZE);
        }
        else if (patternCounter == 73*SECOND + 2*DECI_SECOND) {
            controller2.open(DROP_SIZE);
        }
        else if (patternCounter == 73*SECOND + 4*DECI_SECOND) {
            controller3.open(DROP_SIZE);
        }
        else if (patternCounter == 73*SECOND + 6*DECI_SECOND) {
            controller4.open(DROP_SIZE);
        }
        else if (patternCounter == 73*SECOND + 8*DECI_SECOND) {
            controller5.open(DROP_SIZE);
        }
        else if (patternCounter == 74*SECOND) {
            controller6.open(DROP_SIZE);
        }

        // End of sequence, start from beginning again
        else if (patternCounter == 84*SECOND) {
            patternCounter = 0;
        }

        controllerMiddle.run();
        controller1.run();
        controller2.run();
        controller3.run();
        controller4.run();
        controller5.run();
        controller6.run();

        if (!(FLUSH_BUTTON_INPUT & BV(FLUSH_BUTTON_INPUT_PIN)))
        {
            // Run the flush routine if flush button is down.
            // TODO: Implement
        }

        _delay_ms(LOOP_DELAY);
    }
}
