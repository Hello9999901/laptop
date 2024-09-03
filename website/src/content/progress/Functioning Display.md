---
title: "Functioning Display"
hash: "Hello9999901/zmk/commit/fdd6672159e983177fd62d12f2ffced35667086c"
dateStart: "9/2/2024"
---

In the end, it seems like the culprit of the non-functional display was the hardware. Using the exact same devicetree compile and surrounding hardware setup, I was able to get the display running. In particular, the difficulties were most likely in the high-speed signaling losses across the SoM, the Hirose connectors, the HDMI connector, and the transition to the "anyon_e display evaluation" breakout board. The difference between V1 and V2 Short was the use of a male HDMI connector and the shortest signaling traces possible. This eliminated the need for a male-male HDMI conversion between the boards and shortened the FR4 trace lengths by around 2cm. That is -20% change from the pervious length. However, it looks like brightness control must be done over PWM, as (unfortunately predicted) adjusting the voltage does not result in a change in brightness. In my measurements (assuming default output is the stated 400 nits), the max current draw is around 0.5A at 12V, so a PWM brightness system should be implementable.
