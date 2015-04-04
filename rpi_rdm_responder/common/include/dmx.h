/**
 * @file dmx.h
 *
 */
/* Copyright (C) 2015 by Arjan van Vught <pm @ http://www.raspberrypi.org/forum/>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef DMX_H_
#define DMX_H_

#include <stdint.h>

#define DMX_DATA_BUFFER_SIZE			512		///< //TODO include SC

#define DMX_TRANSMIT_BREAK_TIME_MIN		92		///< 92μs
#define DMX_TRANSMIT_BREAK_TIME_TYPICAL	176		///< 176μs
#define DMX_TRANSMIT_MAB_TIME_MIN		12		///< 12μs
#define DMX_TRANSMIT_MAB_TIME_MAX		1E6		///< 1s

#define DMX_MIN_SLOT_VALUE 				0		///< The minimum value a DMX512 slot can take.
#define DMX_MAX_SLOT_VALUE 				255		///< The maximum value a DMX512 slot can take.
#define DMX512_START_CODE				0		///< The start code for DMX512 data. This is often referred to as NSC for "Null Start Code".

enum
{
	DMX_UNIVERSE_SIZE = 512 					///< The number of slots in a DMX512 universe.
};

typedef enum
{
	DMX_PORT_DIRECTION_IDLE = 0,	///<
	DMX_PORT_DIRECTION_OUTP = 1,	///< DMX output
	DMX_PORT_DIRECTION_INP = 2		///< DMX input
} _dmx_port_direction;


struct _dmx_statistics
{
	uint16_t mark_after_break;
	uint16_t slots_in_packet;
	uint16_t break_to_break;
	uint16_t updates_per_seconde;
	uint16_t slot_to_slot;
};

struct _total_statistics
{
	uint32_t dmx_packets;
	uint32_t rdm_packets;
};

extern uint8_t dmx_data[DMX_DATA_BUFFER_SIZE];

extern void dmx_init(void);
extern void dmx_port_direction_set(const uint8_t, const uint8_t);
extern const uint8_t dmx_port_direction_get(void);
extern void dmx_data_send(const uint8_t *, const uint16_t);

extern const uint8_t *rdm_available_get(void);
extern const uint8_t *rdm_get_current_data(void);

extern void rdm_available_set(const uint8_t);
extern const uint64_t rdm_data_receive_end_get(void);
extern const uint8_t dmx_available_get(void);
extern void dmx_available_set(const uint8_t);
extern const uint64_t dmx_output_break_time_get(void);
extern void dmx_output_break_time_set(const uint64_t);
extern const uint64_t dmx_output_mab_time_get(void);
extern void dmx_output_mab_time_set(const uint64_t);

extern void dmx_statistics_reset(void);
extern void total_statistics_reset(void);
extern const struct _total_statistics *total_statistics_get(void);

#endif /* DMX_H_ */