/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "platform.h"


// opmode flags, GET side
#define SA_MODE_GET_FREQ_BY_FREQ            1
#define SA_MODE_GET_PITMODE                 2
#define SA_MODE_GET_IN_RANGE_PITMODE        4
#define SA_MODE_GET_OUT_RANGE_PITMODE       8
#define SA_MODE_GET_UNLOCK                 16
#define SA_MODE_GET_DEFERRED_FREQ          32

// opmode flags, SET side
#define SA_MODE_SET_IN_RANGE_PITMODE        1 // Immediate
#define SA_MODE_SET_OUT_RANGE_PITMODE        2 // Immediate
#define SA_MODE_CLR_PITMODE                 4 // Immediate
#define SA_MODE_SET_UNLOCK                  8
#define SA_MODE_SET_LOCK                    0 // ~UNLOCK
#define SA_MODE_SET_DEFERRED_FREQ          16

// SetFrequency flags, for pit mode frequency manipulation
#define SA_FREQ_GETPIT                      (1 << 14)
#define SA_FREQ_SETPIT                      (1 << 15)
#define SA_FREQ_MASK                        (~(SA_FREQ_GETPIT|SA_FREQ_SETPIT))

// For generic API use, but here for now

typedef struct smartAudioDevice_s {
    int8_t version;
    int8_t channel;
    int8_t power;
    int8_t mode;
    uint16_t freq;
    uint16_t orfreq;
} smartAudioDevice_t;

typedef struct saPowerTable_s {
    int rfpower;
    int16_t valueV1;
    int16_t valueV2;
} saPowerTable_t;

typedef struct smartAudioStat_s {
    uint16_t pktsent;
    uint16_t pktrcvd;
    uint16_t badpre;
    uint16_t badlen;
    uint16_t crc;
    uint16_t ooopresp;
    uint16_t badcode;
} smartAudioStat_t;

extern smartAudioDevice_t saDevice;
extern saPowerTable_t saPowerTable[];
extern smartAudioStat_t saStat;
extern bool saDeferred;
extern uint16_t sa_smartbaud;

int saDacToPowerIndex(int dac);
void saSetBandAndChannel(uint8_t band, uint8_t channel);
void saSetMode(int mode);
void saSetPowerByIndex(uint8_t index);
void saSetFreq(uint16_t freq);
void saSetPitFreq(uint16_t freq);
bool vtxSmartAudioInit(void);

#ifdef SMARTAUDIO_DPRINTF
#ifdef OMNIBUSF4
#define DPRINTF_SERIAL_PORT SERIAL_PORT_USART3
#else
#define DPRINTF_SERIAL_PORT SERIAL_PORT_USART1
#endif
extern serialPort_t *debugSerialPort;
#define dprintf(x) if (debugSerialPort) printf x
#else
#define dprintf(x)
#endif // SMARTAUDIO_DPRINTF
