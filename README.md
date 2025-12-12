# 🛒 Carronho

Prototype for [Carrildo 🎠](https://github.com/worstmakers/carrildo), the super screaming car. The idea is to test the algoritm to controlling the motors and the screaming.

But, Carronho will do that in silence, with a red LED for the screams.

## Caracteristics

Carronho is assembled in a [ZK-2WD chassis](https://pt.aliexpress.com/item/1005007531700001.html). The kit has the chassis, motor gears, 3xAA battery box(gears only), a switch, two tires, an universal wheel and all the screws, standoffs and nuts, necessary to assemble the car.

Meaning, **it does not have any means to control the car** whatsoever.

This project started by selecting components to make Carronho (this project) closest to Carrildo with the least components as possible.

Carrildo will ride with no controller and when it hit something (triggering a limit switch), it will play a pre-recordered scream. The car, then will ride backwards and adjust course and continue riding by itself until hit something again and, hopefully, screams one more time.

In order make Carronho do the Carrildo's basics, the following components were choosed:

-   A L298N H bridge to control the gears.
-   A HC-SR04 ultrassonic sensor to recongnize distance.
-   A red LED to emulate the screams.
-   A Arduino UNO to command everybody.
-   9V battery
-   AA batteries

_see BOM.md to full material's list_

To avoid noise between microcontroller and gears (and batteries to last longer), Carronho will have energy input from two battery systems: a 9V battery for the Arduino UNO and 3xAA batteries for the gears with the gear box that came with the kit.

The most important thing in selecting the components for the Carronho project was that the components needed to be available for purchasing in the Santa Efigênia neighborhood (São Paulo city, São Paulo/Brasil), because we were already waiting for the delivery of the components for Carrildo that were bought in ~Motherland China~ AliExpress website (and I, Jenny DeVito, couldn't wait to ~play~ test my new projct).
