# Tank Level Monitor

Code in this directory sets up monitoring of water tank levels using a hydrostatic pressure level sensor.  There are a wide variety of devices to choose from at different price points.

## Why not use ultrasonics?

I tried.  But the nature of thanks I have led to a lot of echoes which made for unreliable measurements.  Also, this method is slightly backwards.  We are measuring the unoccupied space in the tank.  Finally, waterproof sensors are actually quite expensive.  You need the sensor to be waterproof to ensure reliability.

The big downsides of the sensor I chose is that it operates from 24V DC, and outputs a 0-5V level which is the depth measurement in metres.  My sensor is rated for 5m depth.  Since the ESP-32 has only 3.3V inputs, I put a voltage divider between the sensor and the analogue input pin.  Not elegant, but it works.  I also regulated the 24V down to a 5V supply for the board.

## Usage

Edit config.h to contain your WiFi and Splunk Server settings, compile and download to the ESP32

## Feedback

If something is wrong, or you want to request a feature, raise an issue against this repository.
