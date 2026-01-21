# 🛒 Carronho

Prototype for [Carrildo 🎠](https://github.com/worstmakers/carrildo), the super screaming car. The idea is to test the algoritm to controlling the motors and the screaming.

But, Carronho will do that in silence, with a red LED for the screams.

## Caracteristics

Carronho is assembled in a [ZK-2WD chassis](https://pt.aliexpress.com/item/1005007531700001.html). With an ultrassonic sensor, an red LED, a motor driver and an Arduino Uno.

Meaning, **it does not have any means to control the car** whatsoever.

This project started by selecting components to make Carronho (this project) closest to Carrildo with the least components as possible.

_see [history.md](/docs/history.md) for the story._

In order make Carronho do the Carrildo's basics, the following components were choosed:

- A ~~L298N~~, ~~L9110S~~ DRV8833 H bridge to control the gears.
- A HC-SR04 ultrassonic sensor to recongnize distance.
- A red LED to emulate the screams.
- An Arduino UNO to command everybody.
- 9V battery
- AA batteries

_see [BOM.md](/docs/BOM.md) to full material's list and [assembly.md](/docs/assembly.md) for a referece on how to assemble it._

### Roadmap 🗺️

Carronho will be dissassembled to give birth to Carrildo.

---

_Feito por Worst Makers._ <br>
_2025-2026_
