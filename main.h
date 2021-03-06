//
//  main.h
//  ambed
//
//  Created by Jean-Luc Deltombe (LX3JL) on 13/04/2017.
//  Copyright © 2015 Jean-Luc Deltombe (LX3JL). All rights reserved.
//
// ----------------------------------------------------------------------------
//    This file is part of ambed.
//
//    xlxd is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    xlxd is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#ifndef main_h
#define main_h

#include <vector>
#include <array>
#include <map>
#include <queue>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <ctime>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <arpa/inet.h>

////////////////////////////////////////////////////////////////////////////////////////
// defines

// version -----------------------------------------------------

#define VERSION_MAJOR                   1
#define VERSION_MINOR                   3
#define VERSION_REVISION                5

// global ------------------------------------------------------

//#define RUN_AS_DAEMON
#define NB_MAX_STREAMS                  26                                  //number of transcoded modules
//#define DEBUG_DUMPFILE

// Transcoder server --------------------------------------------
#define TRANSCODER_PORT                 10100                               // UDP port
#define TRANSCODER_KEEPALIVE_PERIOD     2                                   // in seconds
#define TRANSCODER_KEEPALIVE_TIMEOUT    (TRANSCODER_KEEPALIVE_PERIOD + 1)   // in seconds

// Codecs -------------------------------------------------------
#define CODEC_NONE                      0
#define CODEC_AMBEPLUS                  1
#define CODEC_AMBE2PLUS                 2

// Transcoding speech gains
#define CODECGAIN_AMBEPLUS              -16                                 // in dB
#define CODECGAIN_AMBE2PLUS             +10                                 // in dB

// Transcoding Tweaks
#define USE_AGC                         0
#define AGC_CLAMPING                    3                                   //clamps the AGC gain to +- this value
#define USE_BANDPASSFILTER              1

// Timeouts -----------------------------------------------------
#define STREAM_ACTIVITY_TIMEOUT         TRANSCODER_KEEPALIVE_TIMEOUT        // in seconds


////////////////////////////////////////////////////////////////////////////////////////
// typedefs

typedef unsigned char           uint8;
typedef unsigned short          uint16;
typedef unsigned int            uint32;
typedef unsigned int            uint;


////////////////////////////////////////////////////////////////////////////////////////
// macros

#define MIN(a,b) 				((float)(a) < (float)(b))?(a):(b)
#define MAX(a,b) 				((a) > (b))?(a):(b)
#define MAKEWORD(low, high)		((uint16)(((uint8)(low)) | (((uint16)((uint8)(high))) << 8)))
#define MAKEDWORD(low, high)	((uint32)(((uint16)(low)) | (((uint32)((uint16)(high))) << 16)))
#define LOBYTE(w)				((uint8)(uint16)(w & 0x00FF))
#define HIBYTE(w)				((uint8)((((uint16)(w)) >> 8) & 0xFF))
#define LOWORD(dw)				((uint16)(uint32)(dw & 0x0000FFFF))
#define HIWORD(dw)				((uint16)((((uint32)(dw)) >> 16) & 0xFFFF))

////////////////////////////////////////////////////////////////////////////////////////
// FIR Filter coefficients computed to be the closest to the recommended filter in 
// Documentation
//
// Following GNU Octave script was used
/*
pkg load signal;
fsamp = 8000;
fcuts = [200 300 3000 3400];
mags = [0 1 0];
devs = [0.2 1 0.2];

[n,Wn,beta,ftype] = kaiserord(fcuts,mags,devs,fsamp);
n = n + rem(n,2);
hh = fir1(n,Wn,ftype,kaiser(n+1,beta),'noscale');

freqz(hh);
[H,f] = freqz(hh,1,1024,fsamp);
plot(f,abs(H))
disp(hh);
grid
*/

#if USE_BANDPASSFILTER == 1

const float FILTER_TAPS[] {
-0.0153779f,  0.0114832f, -0.0060703f, -0.0221526f, 0.0085472f, -0.0449400f,
-0.0068112f, -0.0307485f, -0.0548559f, -0.0022596f, -0.0879344f, -0.0166698f,
-0.0533627f, -0.1015552f,  0.0424673f, -0.2116654f,  0.1267453f,  0.7375000f,
0.1267453f, -0.2116654f,  0.0424673f, -0.1015552f, -0.0533627f, -0.0166698f,
-0.0879344f, -0.0022596f, -0.0548559f, -0.0307485f, -0.0068112f, -0.0449400f,
0.0085472f, -0.0221526f, -0.0060703f,  0.0114832f, -0.0153779f };
#define FILTER_TAPS_LENGTH          35

#endif

////////////////////////////////////////////////////////////////////////////////////////
// global objects

class CAmbeServer;
extern CAmbeServer  g_AmbeServer;

class CVocodecs;
extern CVocodecs    g_Vocodecs;

 
////////////////////////////////////////////////////////////////////////////////////////
#endif /* main_h */
