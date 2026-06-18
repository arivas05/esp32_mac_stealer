# ESP32 MAC STEALER WITH A MAC SPOOFER


## Disclaimer
This repository is provided for educational and authorized research purposes only. I do not condone any unethical or illegal use of the materials contained herein.
The project was originally for Information Security by Dr. Varol and is being expanded upon for Linux machines

Thank you to Blednica for letting me collaberate with him on TinyHASH

## REQUIREMENTS
This project reqiuires an ESP32, a breadboard, copper wires, SPI breakout board, a MicroSD card, and MicroSD card reader. The ESP-IDF is needed to run this repository https://github.com/espressif/esp-idf 


## Wiring Setup
The table below shows the default pin assignments.

SD card pin | SPI pin | ESP32 pin     | ESP32-S2, ESP32-S3 | ESP32-P4 | ESP32-H2 | ESP32-C3 and other chips |  Notes
------------|---------|---------------|--------------------|----------|----------|--------------------------|------------
 D0         | MISO    | GPIO19        | GPIO37             | GPIO13   | GPIO0    | GPIO6                    |
 D3         | CS      | GPIO5         | GPIO34             | GPIO10   | GPIO1    | GPIO1                    |
 CLK        | SCK     | GPIO18        | GPIO36             | GPIO12   | GPIO4    | GPIO5                    |
 CMD        | MOSI    | GPIO5         | GPIO35             | GPIO11   | GPIO5    | GPIO4                    | 10k pullup


## Diagram





Make sure to read the README.md in the mac_spoofer file!
