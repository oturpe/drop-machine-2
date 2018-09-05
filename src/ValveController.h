
#ifndef _H_VALVE_CONTROLLER
#define _H_VALVE_CONTROLLER

/// \class ValveController
///
/// Controls a single direct operated, normally closed valve by switching a
/// mosfet controlling it. By default the valve of closed. By issuing an open()
/// call the valve opens for specified duration.
///
/// On initialization, port and pin used by the controller are given.
///
/// The controller must receive a run() call during each tick of the system
/// loop to calculate timings.
class ValveController {
public:
    /// \brief
    ///    Initializes a new valve controller.
    ///
    /// \param port
    ///    Port where driving mosfet is connected
    /// \param pin
    ///    Pin where driving mosfet is connected
    ValveController(Port port, uint8_t pin);

public:
    /// \brief
    ///    Instructs the controller to advance one step in sequence, essentially
    ///    stepping the controller's clock.
    void run();

    /// \brief
    ///    Instructs the valve to open for specified period. If the valve is
    ///    already open, the existing remaining open time is erased and the
    ///    valve will remain open for period give in the latest call.
    ///
    /// \param period
    ///    Open time in system loop ticks
    void open(uint16_t period);

private:
    /// Port where driving mosfet is connected.
    Port port;
    /// Pin in port D this controller controls.
    uint8_t pin;

    /// Remaining open period. 0 if the valve is closed.
    uint32_t openPeriod;
};

#endif