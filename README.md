# picow\_infrared\_helper

## Overview

This should run on any modern unix system. It sends IR timing over UDP.

When used in conjunction with my picow\_infrared\_relay, a Pico W can listen on UDP
and then light an IR to send the IR code to a device.

## Hardware required

This is meant to be used with my picow\_infrared\_relay and rpi\_infrared\_reader
projects. Unlike those two, this will run on standard hardware.

## Software required

This is written in C and doesn't use any special libraries.

To make it, just do a:
```bash
git clone https://github.com/sanjayrao77/picow_infrared_helper
cd picow_infrared_helper
make
```

## Usage

After it's compiled, you can run ./irsender. That will print the following help:

```
Usage: irsender OUR_IP DEST_IP CMD [CMD] [CMD] ...
CMD: ipsearch, sequence, stereo, mute, optical, bluetooth, up_volume, down_volume
Example: irsender 192.168.1.9 192.168.1.255 ipsearch
Example: irsender 192.168.1.9 192.168.1.177 sequence down_volume down_volume optical
```

## NEC support

There is support for NEC-format codes. You can use necXXXX, on the command line to
refer to code XXXX in nec format. The program recognizes 16, 24 and 32bit codes, where
XXXX is in hexadecimal (and is 4, 6 or 8 characters).

## Future support

I've decoded other IR formats but haven't included them yet. Hopefully I'll add some soon.

## pronto.py

This is a simple script to convert "pronto" style hex codes to the raw timing that my
program uses.

## Adding new codes

Unless you happen to have the ir codes that are already included, you'll want to
add your own remote codes. You can use my rpi\_infrared\_reader to copy codes
from a remote.

To add a new code, you'll need to edit main.c. It should be fairly intuitive to
add to the existing tables.
