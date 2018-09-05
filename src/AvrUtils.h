// Generic Avr helpers

// Cleaner setting of bits
#define BV(x) (1<<x)

/// \enum Port
///
/// Symbols for referring to separate io ports.
enum Port { A, B, C, D };
