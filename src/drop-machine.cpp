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
    VALVE_INNER_0_DATA_DIR |= BV(VALVE_INNER_0_DATA_DIR_PIN);
    VALVE_INNER_1_DATA_DIR |= BV(VALVE_INNER_1_DATA_DIR_PIN);
    VALVE_INNER_2_DATA_DIR |= BV(VALVE_INNER_2_DATA_DIR_PIN);
    VALVE_INNER_3_DATA_DIR |= BV(VALVE_INNER_3_DATA_DIR_PIN);
    VALVE_INNER_4_DATA_DIR |= BV(VALVE_INNER_4_DATA_DIR_PIN);
    VALVE_INNER_5_DATA_DIR |= BV(VALVE_INNER_5_DATA_DIR_PIN);
    VALVE_OUTER_0_DATA_DIR |= BV(VALVE_OUTER_0_DATA_DIR_PIN);
    VALVE_OUTER_1_DATA_DIR |= BV(VALVE_OUTER_1_DATA_DIR_PIN);
    VALVE_OUTER_2_DATA_DIR |= BV(VALVE_OUTER_2_DATA_DIR_PIN);
    VALVE_OUTER_3_DATA_DIR |= BV(VALVE_OUTER_3_DATA_DIR_PIN);
    VALVE_OUTER_4_DATA_DIR |= BV(VALVE_OUTER_4_DATA_DIR_PIN);
    VALVE_OUTER_5_DATA_DIR |= BV(VALVE_OUTER_5_DATA_DIR_PIN);
    VALVE_OUTER_6_DATA_DIR |= BV(VALVE_OUTER_6_DATA_DIR_PIN);
    VALVE_OUTER_7_DATA_DIR |= BV(VALVE_OUTER_7_DATA_DIR_PIN);
    VALVE_OUTER_8_DATA_DIR |= BV(VALVE_OUTER_8_DATA_DIR_PIN);
    VALVE_OUTER_9_DATA_DIR |= BV(VALVE_OUTER_9_DATA_DIR_PIN);
    VALVE_OUTER_10_DATA_DIR |= BV(VALVE_OUTER_10_DATA_DIR_PIN);
    VALVE_OUTER_11_DATA_DIR |= BV(VALVE_OUTER_11_DATA_DIR_PIN);

    // Initialize valve controllers
    ValveController controllerMiddle(VALVE_MIDDLE_DATA_REF, VALVE_MIDDLE_DATA_PIN);
    ValveController controllerInner0(VALVE_INNER_0_DATA_REF, VALVE_INNER_0_DATA_PIN);
    ValveController controllerInner1(VALVE_INNER_1_DATA_REF, VALVE_INNER_1_DATA_PIN);
    ValveController controllerInner2(VALVE_INNER_2_DATA_REF, VALVE_INNER_2_DATA_PIN);
    ValveController controllerInner3(VALVE_INNER_3_DATA_REF, VALVE_INNER_3_DATA_PIN);
    ValveController controllerInner4(VALVE_INNER_4_DATA_REF, VALVE_INNER_4_DATA_PIN);
    ValveController controllerInner5(VALVE_INNER_5_DATA_REF, VALVE_INNER_5_DATA_PIN);
    ValveController controllerOuter0(VALVE_OUTER_0_DATA_REF, VALVE_OUTER_0_DATA_PIN);
    ValveController controllerOuter1(VALVE_OUTER_1_DATA_REF, VALVE_OUTER_1_DATA_PIN);
    ValveController controllerOuter2(VALVE_OUTER_2_DATA_REF, VALVE_OUTER_2_DATA_PIN);
    ValveController controllerOuter3(VALVE_OUTER_3_DATA_REF, VALVE_OUTER_3_DATA_PIN);
    ValveController controllerOuter4(VALVE_OUTER_4_DATA_REF, VALVE_OUTER_4_DATA_PIN);
    ValveController controllerOuter5(VALVE_OUTER_5_DATA_REF, VALVE_OUTER_5_DATA_PIN);
    ValveController controllerOuter6(VALVE_OUTER_6_DATA_REF, VALVE_OUTER_6_DATA_PIN);
    ValveController controllerOuter7(VALVE_OUTER_7_DATA_REF, VALVE_OUTER_7_DATA_PIN);
    ValveController controllerOuter8(VALVE_OUTER_8_DATA_REF, VALVE_OUTER_8_DATA_PIN);
    ValveController controllerOuter9(VALVE_OUTER_9_DATA_REF, VALVE_OUTER_9_DATA_PIN);
    ValveController controllerOuter10(VALVE_OUTER_10_DATA_REF, VALVE_OUTER_10_DATA_PIN);
    ValveController controllerOuter11(VALVE_OUTER_11_DATA_REF, VALVE_OUTER_11_DATA_PIN);

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
            controllerInner0.open(DROP_SIZE);
        }

        // Single drop on opposite side
        else if (patternCounter == 20*SECOND) {
            controllerInner3.open(DROP_SIZE);
        }

        // Triangle shape followed by drop in the middle
        else if (patternCounter == 30*SECOND) {
            controllerInner0.open(DROP_SIZE);
            controllerInner2.open(DROP_SIZE);
            controllerInner4.open(DROP_SIZE);
        }
        else if (patternCounter == 32*SECOND) {
            controllerMiddle.open(DROP_SIZE);
        }

        // Triangle and middle
        else if (patternCounter == 42*SECOND) {
            controllerInner1.open(DROP_SIZE);
            controllerInner3.open(DROP_SIZE);
            controllerInner5.open(DROP_SIZE);
            controllerMiddle.open(DROP_SIZE);
        }

        // Hexagon
        else if (patternCounter == 52*SECOND) {
            controllerInner0.open(DROP_SIZE);
            controllerInner1.open(DROP_SIZE);
            controllerInner2.open(DROP_SIZE);
            controllerInner3.open(DROP_SIZE);
            controllerInner4.open(DROP_SIZE);
            controllerInner5.open(DROP_SIZE);
        }

        // Triangle followed by the other triangle
        else if (patternCounter == 62*SECOND) {
            controllerInner1.open(DROP_SIZE);
            controllerInner3.open(DROP_SIZE);
            controllerInner5.open(DROP_SIZE);
        }
        else if (patternCounter == 62*SECOND + 5*DECI_SECOND) {
            controllerInner0.open(DROP_SIZE);
            controllerInner2.open(DROP_SIZE);
            controllerInner4.open(DROP_SIZE);
        }

        // Spiral hexagon
        else if (patternCounter == 73*SECOND) {
            controllerInner0.open(DROP_SIZE);
        }
        else if (patternCounter == 73*SECOND + 2*DECI_SECOND) {
            controllerInner1.open(DROP_SIZE);
        }
        else if (patternCounter == 73*SECOND + 4*DECI_SECOND) {
            controllerInner2.open(DROP_SIZE);
        }
        else if (patternCounter == 73*SECOND + 6*DECI_SECOND) {
            controllerInner3.open(DROP_SIZE);
        }
        else if (patternCounter == 73*SECOND + 8*DECI_SECOND) {
            controllerInner4.open(DROP_SIZE);
        }
        else if (patternCounter == 74*SECOND) {
            controllerInner5.open(DROP_SIZE);
        }

        // End of sequence, start from beginning again
        else if (patternCounter == 84*SECOND) {
            patternCounter = 0;
        }

        controllerMiddle.run();
        controllerInner0.run();
        controllerInner1.run();
        controllerInner2.run();
        controllerInner3.run();
        controllerInner4.run();
        controllerInner5.run();
        controllerOuter0.run();
        controllerOuter1.run();
        controllerOuter2.run();
        controllerOuter3.run();
        controllerOuter4.run();
        controllerOuter5.run();
        controllerOuter6.run();
        controllerOuter7.run();
        controllerOuter8.run();
        controllerOuter9.run();
        controllerOuter10.run();
        controllerOuter11.run();

        if (!(FLUSH_BUTTON_INPUT & BV(FLUSH_BUTTON_INPUT_PIN)))
        {
            // Run the flush routine if flush button is down.
            // TODO: Implement
        }

        _delay_ms(LOOP_DELAY);
    }
}
