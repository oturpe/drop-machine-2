// This is the configuration file. Ideally, any configuration and calibration
// of the device should be done by changing this file only.

// Needed by util/delay.h
#define F_CPU 1000000UL

// Delay between two executions of main loop, given in millisecond.
#define LOOP_DELAY 20

// One secind, given in units of LOOP_DELAY
#define SECOND  50
// One secind, given in units of LOOP_DELAY
#define DECI_SECOND  5

// Definition of indicator pin.
#define INDICATOR_DATA_DIR DDRE
#define INDICATOR_DATA_DIR_PIN DDE1
#define INDICATOR_DATA PORTE
#define INDICATOR_DATA_PIN PORTE1

// Half length of one complete indicator period. In other words, the time the
// indicator spends on and off. Given in units of LOOP_DELAY.
#define INDICATOR_HALF_PERIOD 25

// Definition of flush button pin.
#define FLUSH_BUTTON_DATA_DIR DDRE
#define FLUSH_BUTTON_DATA_DIR_PIN DDE2
#define FLUSH_BUTTON_DATA PORTE
#define FLUSH_BUTTON_DATA_PIN PORTE2
#define FLUSH_BUTTON_INPUT PINE
#define FLUSH_BUTTON_INPUT_PIN PINE2


// Definition of valve control pins
#define VALVE_MIDDLE_DATA_DIR DDRB
#define VALVE_MIDDLE_DATA_DIR_PIN DDB0
#define VALVE_MIDDLE_DATA PORTB
#define VALVE_MIDDLE_DATA_PIN PORTB0
#define VALVE_MIDDLE_DATA_REF B

#define VALVE_1_DATA_DIR DDRD
#define VALVE_1_DATA_DIR_PIN DDD0
#define VALVE_1_DATA PORTD
#define VALVE_1_DATA_PIN PORTD0
#define VALVE_1_DATA_REF D

#define VALVE_2_DATA_DIR DDRD
#define VALVE_2_DATA_DIR_PIN DDD1
#define VALVE_2_DATA PORTD
#define VALVE_2_DATA_PIN PORTD1
#define VALVE_2_DATA_REF D

#define VALVE_3_DATA_DIR DDRD
#define VALVE_3_DATA_DIR_PIN DDD2
#define VALVE_3_DATA PORTD
#define VALVE_3_DATA_PIN PORTD2
#define VALVE_3_DATA_REF D

#define VALVE_4_DATA_DIR DDRD
#define VALVE_4_DATA_DIR_PIN DDD3
#define VALVE_4_DATA PORTD
#define VALVE_4_DATA_PIN PORTD3
#define VALVE_4_DATA_REF D

#define VALVE_5_DATA_DIR DDRD
#define VALVE_5_DATA_DIR_PIN DDD4
#define VALVE_5_DATA PORTD
#define VALVE_5_DATA_PIN PORTD4
#define VALVE_5_DATA_REF D

#define VALVE_6_DATA_DIR DDRD
#define VALVE_6_DATA_DIR_PIN DDD5
#define VALVE_6_DATA PORTD
#define VALVE_6_DATA_PIN PORTD5
#define VALVE_6_DATA_REF D

// Length of valve opening during a drop. Measured in units of LOOP_DELAY
#define DROP_SIZE 4
// Multiplier for adjusting the drop sequence speed
#define DROP_FREQUENCY_MULTIPLIER 50

