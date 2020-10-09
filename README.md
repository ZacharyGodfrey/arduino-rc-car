# Arduino RC Car

A simple remote-controlled car that combines 3D modeling and 3D printing with electronics and embedded systems programming.

**Note:** This project is my first attempt at using a micro-controller and writing C++. The code probably isn't perfect, but it gets the job done in a way that is (hopefully) easy to follow.

## Contents

- [The Car](#the-car)
  - [3D Printed Parts](#3d-printed-parts)
  - [Purchased Parts](#purchased-parts)
  - [Assembly](#assembly)
- [The Remote](#the-remote)
  - [3D Printed Parts](#3d-printed-parts-1)
  - [Purchased Parts](#purchased-parts-1)
  - [Assembly](#assembly-1)
- [Communication](#communication)
- [To-Do List](#to-do-list)
- [Future Upgrades](#future-upgrades)
- [References](#references)

## The Car

The car constantly checks for a new state value coming from the remote via an RF transceiver. If the incoming state value is valid and is different from the car's current state (repeated inputs are ignored) then the car will adjust the motors according to the new state.

### 3D Printed Parts

To be determined.

### Purchased Parts

|Quantity|Unit Price|Item|
|--:|--:|:--|
|1|$23.00|[Arduino Uno Rev3](https://store.arduino.cc/usa/arduino-uno-rev3)|
|1|$19.95|[Adafruit Motor Shield for Arduino v2 Kit](https://www.adafruit.com/product/1438)|
|1|$8.99|[NRF24L01+PA+LNA Wireless RF Transceiver Module (2 pack)](https://www.amazon.com/HiLetgo%C2%AE-NRF24L01-Wireless-Transceiver-Compatible/dp/B00WG9HO6Q)|
|2|$8.49|[3-6V DC Motors with Wheels (2 pack)](https://www.amazon.com/Gearbox-Motor-Wheel-Arduino-Smart/dp/B07P6QCJPX)|
|4|$1.32|[M3x35mm Screws (2 pack)](https://www.homedepot.com/p/M3-0-5-x-35-mm-Internal-Hex-Metric-Socket-Head-Cap-Screw-2-Pack-844518/204283594)|
|2|$0.65|[M3 Lock Washers (4 pack)](https://www.homedepot.com/p/Everbilt-M3-4-Piece-Stainless-Steel-Metric-Lock-Washer-842398/204993665)|
|4|$0.56|[M3 Hex Nuts (2 pack)](https://www.homedepot.com/p/Everbilt-M3-5-Stainless-Steel-Metric-Hex-Nut-2-Piece-per-Bag-842318/204836105)|
|1|$2.50|[Inline Power Switch with 2.1mm Barrel Jack](https://www.adafruit.com/product/1125)|
|1|$5.79|[6 AA Battery Box with 2.1mm Barrel Jack (2 pack)](https://www.amazon.com/Battery-Holder-Connector-Output-Pack/dp/B07XP7H9PB)|
|1|$6.98|[Dupont Wire Kit](https://www.amazon.com/Elegoo-EL-CP-004-Multicolored-Breadboard-arduino/dp/B01EV70C78)|

**Total Price:** $93.01 (pre-tax)

### Assembly

To be determined.

## The Remote

The remote constantly checks the value of each of the input buttons. It then maps the combination of values to a corresponding state value and sends that value to the car via an RF transceiver.

### 3D Printed Parts

To be determined.

### Purchased Parts

To be determined.

### Assembly

To be determined.

## Communication

The remote sends the desired state to the car as a single integer value. The following table lists all of the available states:

|Input Value|Car State|Description|
|--:|:--|:--|
|0|`STATE_NONE`|The initial state, ignored if sent from the remote|
|1|`STATE_BRAKE`|Lock motors and prevent the wheels from turning|
|2|`STATE_COAST`|Release motors and allow the wheels to spin freely|
|3|`STATE_DRIVE_SLOW`|Move forward at the defined slow speed|
|4|`STATE_DRIVE_FAST`|Move forward at the defined fast speed|
|5|`STATE_REVERSE_SLOW`|Move backward at the defined slow speed|
|6|`STATE_REVERSE_FAST`|Move backward at the defined fast speed|
|7|`STATE_LEFT_SLOW`|Rotate left (counter-clockwise) at the defined slow speed|
|8|`STATE_LEFT_FAST`|Rotate left (counter-clockwise) at the defined fast speed|
|9|`STATE_RIGHT_SLOW`|Rotate right (clockwise) at the defined slow speed|
|10|`STATE_RIGHT_FAST`|Rotate right (clockwise) at the defined slow speed|

## To-Do List

- 3D model, print, and assemble car body
- Research and purchase electronics for remote
- 3D model, print, and assemble remote
- Test functionality and tweak settings
- Remove `TODO` statements in scripts

## Future Upgrades

In a future version, I'd like to refine the driving so that the car moves more like a car - able to make slight direction changes while moving forward/backward instead of having to stop and rotate. This will probably require the remote to send some indication of the desired X (left/right) and Y (forward/backward) velocities.

## References

- [Adafruit Motor Shield V2 Library](https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library)
- [RF24 Library](https://github.com/nRF24/RF24)
- [nRF24L01 Tutorial #1](https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/)
- [nRF24L01 Tutorial #2](https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/)