---
title: "Starting Over V0.2"
hash: "Hello9999901/laptop/commit/8de2bc9e0074f80b906bef1af565acf0b877c5ee"
dateStart: "8/21/2024"
---

After the display evaluation, I think I have a much better handle on high-speed signaling especially in relation to the CM3588. This new motherboard revision will be a near-final layout and close to the tape-out design.

I am paying special attention the integrity, coupling, and EMC of the board, so I've made the bold move for a 6 layer stackup - (Signal, GND, Power, Power, GND, Signal). I might use the first power plane for low speed signaling since the power requirements aren't that high.
