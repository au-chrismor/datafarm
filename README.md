# The DataFarm Project

## Introduction

This is a working framework for gathering data from gardens, tanks, vehicles and other things you will find on a small farm.  It is based on my own experiences and learnings as I go through the journey.

I live in an area where gathering and managing your resources is required, and it's important to know how much water or energy you are using, not only at the present time but historically as well.  There are plenty of ways to do this, and this is simply my take on the process.

## Requirements

## Hardware

I have standardised on ESP-32 modules for this project because they offer the right balance of features, ease-of-use and price.  In addition you will need the some (or all) of the following per device:
* 1 x BME280 module for weather sensing
* 2 x 10K 0.25W resistors per port for analog sensing (0-5V)
* 1 x DS18B20 encapsulated temperature sensor for tank monitoring
* 1 x 4K7 0.25W resistor if you are using the DS18B20
* 1 x Hydrostatic depth probe for tank monitoring

Each module directory has a BOM (Bill of Materials) document

## Software

## Building

## Deployment
