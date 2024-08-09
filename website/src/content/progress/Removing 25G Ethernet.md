---
title: "Removed 2.5G Ethernet + Subtracting 38mm from the SSD"
hash: "Hello9999901/laptop/commit/3718073a7b3cd8b09f7a54d581c9525380008b53"
dateStart: "7/28/2024"
---

I have put a lot of thought into the sizing and overall integration of the system. As I was designing today, I realized that unless I increase the overall lower chassis thickness to around 17mm, it is impossible to fit an Ethernet connector (height of the connector would be 11.8mm + 1.6mm from PCB = 13.4mm). My aim for the system is still a sleek, integrated, and low-profile design. Unfortunately, I understand why Apple only includes USB-C for connectivity now.

Another tradeoff: With the feature set in mind, a 2280 SSD simply would not fit the vertical requirements. The exact reason is complicated: the keyboard limits the maximum height of the heatsink, meaning the heatpipes have to extend horizontally. The orientation of the CM3588 means that it is most optimal to route with tall components (SSD, wireless card, ribbon cables, etc.) all around it (rather than on one side). It is not that big of a loss, since it will still support 2242 and 2230 SSDs. The PCIe 3.0x4 is limited to 4GB/s, and the newest small-form-factor SSDs are much higher speed and will not be the performance bottleneck.
