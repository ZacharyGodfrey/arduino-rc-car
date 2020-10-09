# Arduino RC Car

A simple remote-controlled car. The car uses an Arduino Uno as its brain; it receives input through an RF transceiver and uses an Adafruit Motor Shield to control 4 DC motors connected to the wheels. Turning the car left and right is achieved by altering the speed and/or direction of the motors on each side of the car.

## Hardware

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

### 3D Printed Parts

To be determined.

## Software

### The Remote

The remote constantly checks the value of each of the input devices. It then checks which state the combination of values correspond to and sends that state value to the car via a radio frequency transceiver.

### The Car

The car constantly checks for a new state value coming from the remote via a radio frequency transceiver. If the incoming state value is valid and is different from the car's current state (repeated inputs are ignored) then the car will adjust the motors according to the new state.

### Communication

The remote sends the desired state to the car as a single integer value. The following table lists all of the available states:

|Input Value|Car State|
|--:|:--|
|0|None - The car's initial state, ignored if sent from the remote|
|1|Stop - Lock motors and prevent the wheels from turning|
|2|Coast - Release motors and allow the wheels to spin freely|
|3|Move Forward Slowly|
|4|Move Forward Quickly|
|5|Move Backward Slowly|
|6|Move Backward Quickly|
|7|Rotate Left Slowly|
|8|Rotate Left Quickly|
|9|Rotate Right Slowly|
|10|Rotate Right Quickly|

## References

- [Adafruit Motor Shield V2 Library](https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library)
- [RF24 Library](https://github.com/nRF24/RF24)
- [nRF24L01 Tutorial #1](https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/)
- [nRF24L01 Tutorial #2](https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/)