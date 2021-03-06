
    Created by Jean-Luc Deltombe (LX3JL) on 09/07/2017.
    Copyright © 2017 Jean-Luc Deltombe (LX3JL). All rights reserved.
    ----------------------------------------------------------------------------- 
    This file is part of ambed.
    xlxd is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    xlxd is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 ----------------------------------------------------------------------------

VERSION: 1.3.4
Hardware compatibility.
======================
This version of ambed is compatible with:
- DF2ET's AMBE3003USB opensource device (https://github.com/phl0/AMBE3003USB)
- LX3JL's USB-3006 opensource device (https://github.com/lx3jl/usb-3006)
- DVSI's USB-3000 device
- DVSI's USB-3003 device
- DVSI's USB-3012 device
- NWDR's ThumbDV device
- NWDR's ThumbDV-3 device
- DVMEGA AMBE3000 device
- DVMEGA AMBE3003 device
- TEAM6160 AMBE3000 device
Available transcoding channels per device:
```
device			 DMR->DSTAR		DSTAR->DMR		Nb Of concurrent channels
-------------------------------------------------------------------------------------------------
3000(pair)		    1				1			2
3003			    1				1			2
3003(pair)		    3				3			4
3003-3000(pair)	    2			    2		4
3006			    3				3			6
3012			    6				6			12
```
Multiple devices can be used at the same time.
You need to use 3000 by pairs or paired with a 3003
Do not to use USB hubs as they have proven making
system behaviour unreliable.

Instructions:
=============
1) Installation of FTDI drivers
Download from FTDI web site the latest D2XX driver package http://www.ftdichip.com/Drivers/D2XX.htm
Follow FTDI provided documentation for installation and testing of the drivers.
For macchine x86 x64
```
# wget http://www.ftdichip.com/Drivers/D2XX/Linux/libftd2xx-i386-1.4.8.gz
# wget http://www.ftdichip.com/Drivers/D2XX/Linux/libftd2xx-x86_64-1.4.8.gz
```
For raspberry ARMv6 ARMv7
```
# wget http://www.ftdichip.com/Drivers/D2XX/Linux/libftd2xx-arm-v6-hf-1.4.8.gz
# wget http://www.ftdichip.com/Drivers/D2XX/Linux/libftd2xx-arm-v7-hf-1.4.8.gz
```
Extract files
```
# tar xfvz libftd2xx-XXX-1.4.8.tgz
# cd release/build
# cp libftd2xx.* /usr/local/lib
# chmod 0755 /usr/local/lib/libftd2xx.so.1.4.8
# ln -sf /usr/local/lib/libftd2xx.so.1.4.8 /usr/local/lib/libftd2xx.so
```
2) installation of g++ compiler
```
# apt-get install build-essential
```
Only Debian 7
```
# apt-get install g++-4.7
```
2) download and compile ambed
```
# git clone https://github.com/lucamarche-iz1mlt/xlx_ambed.git
# cd xlx_ambed
# make clean
# make
# make install
```
Remove module kernel
```
# rmmod ftdi_sio
# rmmod usbserial
```
3) configuring ambed startup service
```
# cp -r ~/xlx_ambed/systemd/ambed.* /lib/systemd/system/
Edit file ambed.service for change IP if xlxd run other PC
N.B If ambed is running on same machine than xlxd, use default 127.0.0.1
otherwise use the machine own IPs
# pico /lib/systemd/system/ambed.service
Update sevice list
# systemctl daemon-reload
Enable service autostart
# systemctl enable ambed.timer
```
4) running ambed
note:
Due to specific FTDI driver implementation, ambed must be running
with root privilege, and cannot be run as a daemon.
So ambed will display the information and error messages in the
terminal it has been started from
Command of start/stop/restart/status service
```
# service ambed start
# service ambed stop
# service ambed restart
# service ambed status
```
To see the correct operation type
```
# screen -r ambed
```

Configure ambed
===============

In main.h find all parameter to set AMBE end conettion UDP.

```
#define NB_MAX_STREAMS 26
```
This parameter defines the number of UDP communication active at the same time. 
if I have an ambe board with 4 channels, the streaming streams in the counter will be channel / 2, 
then 2 and the UDP ports used will be 10101 and 10102.
It is useful if you do not want to open too many doors and only have the necessary.

```
// Transcoder server --------------------------------------------
#define TRANSCODER_PORT                 10100                               // UDP port
#define TRANSCODER_KEEPALIVE_PERIOD     2                                   // in seconds
#define TRANSCODER_KEEPALIVE_TIMEOUT    (TRANSCODER_KEEPALIVE_PERIOD + 1)   // in seconds
```
TRANSCODER_PORT should not be changed.
TRANSCODER_KEEPALIVE_PERIOD can be modified, but be careful that it is also the same on xlxd.
TRANSCODER_KEEPALIVE_TIMEOUT end of connection time.

```
// Transcoding speech gains
#define CODECGAIN_AMBEPLUS      -10  // in dB
#define CODECGAIN_AMBE2PLUS     +10  // in dB
```
CODECGAIN_AMBEPLUS and CODECGAIN_AMBE2PLUS are the gain levels, 
it can be useful to vary them if there are differences between AMBE input and output.
