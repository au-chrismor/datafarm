# Tank Level Monitor

Code in this directory sets up monitoring of water tank levels using a hydrostatic pressure level sensor.  There are a wide variety of devices to choose from at different price points.

## Why not use ultrasonics?

I tried.  But the nature of thanks I have led to a lot of echoes which made for unreliable measurements.  Also, this method is slightly backwards.  We are measuring the unoccupied space in the tank.  Finally, waterproof sensors are actually quite expensive.  You need the sensor to be waterproof to ensure reliability.

The big downsides of the sensor I chose is that it operates from 24V DC, and outputs a 0-5V level which is the depth measurement in metres.  My sensor is rated for 5m depth.  Since the ESP-32 has only 3.3V inputs, I put a voltage divider between the sensor and the analogue input pin.  Not elegant, but it works.  I also regulated the 24V down to a 5V supply for the board.

## Usage

Edit config.h to contain your WiFi and Splunk Server settings, compile and download to the ESP32

## Feedback

If something is wrong, or you want to request a feature, raise an issue against this repository.

## Bill of Materials

To reproduce my installation you will need:

* An ESP-32 controller module.  Ideally, get one with an external antenna.  With minor changes, you could also use an ESP-8266 if you have some available.

* Regulated Power Supply to suit the ESP-32.

* A Hydrostatic Pressure Water Depth Sensor.  Output Range: 0-5V.  Select a Depth Range to suit your tank.  I use 5m for all my devices because it makes the math easier.  Pay close attention to the power supply requirements for this sensor.  Many of them require 24V DC.  Ideally this should be regulated to ensure consistency.

* Two 10K 0.25W Resistors to form a voltage divider.  This ensures the output of the depth sensor can't damage the 3.3V input on the ESP.

* Waterproof DS18B20 temperature sensor.  Make sure the cabling is long enough to reach the bottom of the tank, and that it is rated for permanent immersion.

* One 4K7 0.25W resistor to "bias" the DS18B20.

* Weatherproof enclosure large enough to mount everything.

* Small piece of veroboard or prototype shield to mount the components.

