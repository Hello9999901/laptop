---
title: "Powertrain Charging Functional"
hash: "Hello9999901/laptop/commit/7e120f42460bdfba6e477f5982cce70f7909ddb4"
dateStart: "10/31/2024"
---

After fixing some (many) mistakes with the board, the powertrain charged a battery pack to ~4.18V per cell as expected.

The problems include:

- Used N-MOS for BATFET instead of P-MOS
- Battery pack voltage joined with system power
- Charge/Discharge FETs on battery balancing IC non-functional

I will send a fixed board to production, but I'm not sure if it'll arrive in time for the term deadline.
