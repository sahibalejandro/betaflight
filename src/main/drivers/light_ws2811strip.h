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

#include "io.h"

#define WS2811_LED_STRIP_LENGTH 32
#define WS2811_BITS_PER_LED 24
#define WS2811_DELAY_BUFFER_LENGTH 42 // for 50us delay

#define WS2811_DATA_BUFFER_SIZE (WS2811_BITS_PER_LED * WS2811_LED_STRIP_LENGTH)

#define WS2811_DMA_BUFFER_SIZE (WS2811_DATA_BUFFER_SIZE + WS2811_DELAY_BUFFER_LENGTH)   // number of bytes needed is #LEDs * 24 bytes + 42 trailing bytes)

#if defined(STM32F40_41xxx)
#define BIT_COMPARE_1 67 // timer compare value for logical 1
#define BIT_COMPARE_0 33  // timer compare value for logical 0
#elif defined(STM32F7)
#define BIT_COMPARE_1 76 // timer compare value for logical 1
#define BIT_COMPARE_0 38  // timer compare value for logical 0
#else
#define BIT_COMPARE_1 17 // timer compare value for logical 1
#define BIT_COMPARE_0 9  // timer compare value for logical 0
#endif

void ws2811LedStripInit(ioTag_t ioTag);

void ws2811LedStripHardwareInit(ioTag_t ioTag);
void ws2811LedStripDMAEnable(void);

void ws2811UpdateStrip(void);

void setLedHsv(uint16_t index, const hsvColor_t *color);
void getLedHsv(uint16_t index, hsvColor_t *color);

void scaleLedValue(uint16_t index, const uint8_t scalePercent);
void setLedValue(uint16_t index, const uint8_t value);

void setStripColor(const hsvColor_t *color);
void setStripColors(const hsvColor_t *colors);

bool isWS2811LedStripReady(void);

#if defined(STM32F4) || defined(STM32F7)
extern uint32_t ledStripDMABuffer[WS2811_DMA_BUFFER_SIZE];
#else
extern uint8_t ledStripDMABuffer[WS2811_DMA_BUFFER_SIZE];
#endif
extern volatile uint8_t ws2811LedDataTransferInProgress;
