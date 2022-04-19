# ESC_Inverter_400Hz
Repurpose a BLDC ESC as 3 phase 400Hz inverter driver.

A new firmare is programmed into the atmega 8 microcontroller to drive three phases into a 400Hz transformer. The transformer used is made as a 115 to 14 VAC but used here in reverse to generate a 115 VAC 400 Hz supply from a 20 VDC input, suitable for driving avaiation instruments. Tested on a Sperry articicial horizon gyroscope.

![Overview](./images/IMG_20220419_183145.jpg)

[images](./images)

# prototype firmware

[sketch](./ESC_400Hz_Gen/ESC_400Hz_Gen.ino)

