# The DataFarm Project [![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=au-chrismor_datafarm&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=au-chrismor_datafarm)

## Introduction

This is a working framework for gathering data from gardens, tanks, vehicles and other things you will find on a small farm.  It is based on my own experiences and learnings as I go through the journey.

I live in an area where gathering and managing your resources is required, and it's important to know how much water or energy you are using, not only at the present time but historically as well.  There are plenty of ways to do this, and this is simply my take on the process.

## Requirements

## Hardware

I have standardised on ESP-32 modules for this project because they offer the right balance of features, ease-of-use and price.  In addition you will need the some (or all) of the following per device:
* 1 x BME280 module for weather sensing
* 3 x 10K 0.25W resistors per port for analog sensing (0-5V)
* 1 x DS18B20 encapsulated temperature sensor for tank monitoring
* 1 x 4K7 0.25W resistor if you are using the DS18B20
* 1 x Hydrostatic depth probe for tank monitoring 0-5V output, choose a depth range to suit your tank.  I use 0-5m to make the conversion simple.
* 1 x 10K Thermistor in a stainless steel shell. Use this for meausring temperatures in harsh environments.


Each module directory has a BOM (Bill of Materials) document

## Software

As the sensors are generally Arduino compatible (ESP-32), I have written all the sensor code in Arduino/C++.  The bulk of the code is the same, the only real differences are in how sensors are operated

## Building

Just compile the relevant directory using the Arduino IDE and download to your sensor module.

## Deployment

You will need a Splunk installation to use this solution.  You can use the free license for most applications because it's unlikely you would generate more than 500Mb/day of data even with a lot of sensors.

Set up an HTTP Event Collector (HEC) as per the documentation.  For this version, clear the "Enable SSL" checkbox in HEC Global Settings.  While in most other cases, I would encourage you to use SSL, the overhead to do so with these microcontrollers is just not justified, and really, there's no real risk in the data you are exposing (Unless you start sending GPS coordinates).

It's something I want to come back to later.

## Splunk Sourcetype

All the data from sensors is intended to go into Splunk, so it's useful to have a standard source type and reporting structure.  The event structure sent to the HEC looks like this:

{
    "host": "sensor_name",
    "sourcetype": "datafarm",
    "index": "index_name",
    "event": {
        "sensortype": "sensor_type_name",
        "depth":"number"
    }
}

Valid types for sensortype:

* tankdepth
* temperature
* soilmoisture
* environment
* acpower
* dcpower
* weather
* location

### sensortype = tankdepth

#### depth

An integer value of the ADC output

#### temperature

A float value from the DS18B20 device.  If device is not used, set this field to "-274" (which is impossible, so we know to disregard it)

#### battery

An integer value of the ADC output.  If this input is not used, set this field to "-1"

### sensortype = soilmoisture

#### moisture

An integer value of the ADC output

#### battery

An integer value of the ADC output.  If this input is not used, set this field to "-1"

### sensortype = temperature

#### temperature

A float value of the DS18B20
Alternatively, this might be a thermistor.  The dashboards don't care, it's just a sensor selection.

#### battery

An integer value of the ADC output.  If this input is not used, set this field to "-1"

### sensortype = environment

#### temperature

A float value from the BME280.  In my code this is Centigrade, change to Farenheight if you prefer

#### humidity

A float value from the BME280.  Measurement in %RH

#### pressure

A float value from the BME280.  Measurement in kPa

#### battery

An integer value of the ADC output.  If this input is not used, set this field to "-1"

### sensortype = acpower

#### voltage

An integer value of the ADC output

#### current

An integer value of the ADC output

### sensortype = dcpower

#### voltage

An integer value of the ADC output

#### current

An integer value of the ADC output

### sensortype = weather

#### windspeed

An integer value of wind speed in m/s

#### winddir

An integer value of the ADC output

#### rainfall

An integer value of the number of pulses on the raingauge since midnight

#### uv

An integer value of the ADC output

#### lightlevel

An integer value of the ADC output

#### temperature

A float value from the BME280.  In my code this is Centigrade, change to Farenheight if you prefer

#### humidity

A float value from the BME280.  Measurement in %RH

#### pressure

A float value from the BME280.  Measurement in kPa

#### battery

An integer value of the ADC output.  If this input is not used, set this field to "-1"

### sensortype = temperature

#### thermistor

A float value of the thermistor in degrees C

#### battery

An integer value of the ADC output.  If this input is not used, set this field to "-1"

### sensortype = location

#### altitude

A float value of the height above sea level

#### heading

A float value of the current heading

#### latitude

A float value of the current latitude

#### longitude

A float value of the current longitude

#### satellites

An integer value of the number of satellites currently visible to the receiver

#### speed

A float value of the current ground speed

#### battery

An integer value of the ADC output.  If this input is not used, set this field to "-1"

Feel free to add other sensortypes and generate a PR

