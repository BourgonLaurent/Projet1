# Pins used by `lib1900`

| `io::Port` | `io::Position` | Used? | Class                                                           |
| ---------- | -------------- | ----- | --------------------------------------------------------------- |
| `A`        | `PA0`          |       |                                                                 |
|            | `PA1`          |       |                                                                 |
|            | `PA2`          |       |                                                                 |
|            | `PA3`          |       |                                                                 |
|            | `PA4`          |       |                                                                 |
|            | `PA5`          |       |                                                                 |
|            | `PA6`          |       |                                                                 |
|            | `PA7`          |       |                                                                 |
|            |                |       |                                                                 |
| `B`        | `PB0`          |       |                                                                 |
|            | `PB1`          |       |                                                                 |
|            | `PB2`          | Yes   | [Sound](sound.hpp)                                              |
|            | `PB3`          | Yes   | [Sound](sound.hpp)                                              |
|            | `PB4`          | *     | used by ATmega8 when flashing, try to avoid as much as possible |
|            | `PB5`          | *     | used by ATmega8 when flashing, try to avoid as much as possible |
|            | `PB6`          | *     | used by ATmega8 when flashing, try to avoid as much as possible |
|            | `PB7`          | *     | used by ATmega8 when flashing, try to avoid as much as possible |
|            |                |       |                                                                 |
| `C`        | `PC0`          | Yes   | [Memory](memory.hpp)                                            |
|            | `PC1`          | Yes   | [Memory](memory.hpp)                                            |
|            | `PC2`          |       |                                                                 |
|            | `PC3`          |       |                                                                 |
|            | `PC4`          |       |                                                                 |
|            | `PC5`          |       |                                                                 |
|            | `PC6`          |       |                                                                 |
|            | `PC7`          |       |                                                                 |
|            |                |       |                                                                 |
| `D`        | `PD0`          | Yes   | [Communication](communication.hpp)                              |
|            | `PD1`          | Yes   | [Communication](communication.hpp)                              |
|            | `PD2`          | Yes   | [InterruptButton](interruptButton.hpp)                          |
|            | `PD3`          |       |                                                                 |
|            | `PD4`          | Yes   | [Wheels](wheels.hpp)                                            |
|            | `PD5`          | Yes   | [Wheels](wheels.hpp)                                            |
|            | `PD6`          | Yes   | [Wheels](wheels.hpp)                                            |
|            | `PD7`          | Yes   | [Wheels](wheels.cpp)                                            |
