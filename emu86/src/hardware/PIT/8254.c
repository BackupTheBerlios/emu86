/*
 * 8254.c
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include "8254.h"

typedef struct _pit_timer {
	bit16u count;
	bit16u count_start;
	bit16u latch;
	
	bit8u mode;

	bit8u bcd;
	bit8u active;
	bit8u gate;
	bit8u out;

	bit8u rwl;

	bit8u msb;

} PIT_timer;

typedef struct _pit {
	PIT_timer timer[2];
} PIT;

PIT pit;

#define RWL_LATCH    0x00
#define RWL_RW8_LSB  0x01
#define RWL_RW8_MSB  0x02
#define RWL_RW16_LSB 0x03
#define RWL_RW16_MSB 0x04 /* fake (uhm, i dunno but i guess so :) */

void pit_write_cw(bit8u val)
{
	int t = (val >> 6) & 3;

	int i = pit.timer[t].rwl;

	pit.timer[t].rwl   = (val >> 4) & 3;
	pit.timer[t].msb   = (pit.timer[t].rwl == 2) ? 1 : 0;
	
	pit.timer[t].mode  = (val >> 1) & 7;
	pit.timer[t].bcd   = val & 1;
	
	EMU_DEBUG("wrote command word: (%02x) timer: %d mode: %d rwl: %d bcd: %d",
		val, t, pit.timer[t].mode, pit.timer[t].rwl, pit.timer[t].bcd); 

	if (pit.timer[t].rwl == RWL_LATCH)
	{
		pit.timer[t].latch = pit.timer[t].count;
		EMU_DEBUG("timer %d latched %x", t, pit.timer[t].latch);
		pit.timer[t].rwl = i;
	} 
}

void pit_write_timer(bit8u t, bit8u data)
{
	EMU_DEBUG("wrote to timer %d: %02x)", t, data);
	switch (pit.timer[t].rwl)
	{
		case RWL_RW8_LSB:
			reprogram_counter(t, data);
			break;
		case RWL_RW8_MSB:
			reprogram_counter(t, (data << 8));
			break;
		case RWL_RW16_LSB:
			pit.timer[t].latch = data;
			pit.timer[t].rwl = RWL_RW16_MSB;
			break;
		case RWL_RW16_MSB:
			reprogram_counter(t, (pit.timer[t].latch & 0xff) | (data << 8));
			break;
		default:
			EMU_WARN("tried to write to timer %d with rwl %d", t, pit.timer[t].rwl);
			break;
	}
}

void pit_read_latch(bit8u t, bit8u *data)
{
	EMU_DEBUG("read from latched timer %d: %02x",t,pit.timer[t].latch);
	*data = pit.timer[t].latch;
}

void reprogram_counter(bit8u t, bit16u val)
{
	pit.timer[t].count_start = val;
	pit.timer[t].latch = 0;

	switch (pit.timer[t].mode)
	{
		case 0x00:
			pit.timer[t].count = pit.timer[t].count_start;
//			if (pit.timer[t].gate)
			{
				pit.timer[t].out = 0;
				start(t);
			}
			break;
		case 0x02:
			if (pit.timer[t].gate && !pit.timer[t].active) {
				pit.timer[t].count = pit.timer[t].count_start;
				pit.timer[t].active = 1;
				pit.timer[t].out = 1;
				start(t);
			}
		case 0x03:
			if (pit.timer[t].count_start == 1)
				EMU_DEBUG("reprogram_counter(): illegal count_start (1) in mode 3");
			pit.timer[t].count_start = pit.timer[t].count_start & 0xfffe;
			if (pit.timer[t].gate && !pit.timer[t].active) {
				pit.timer[t].count = pit.timer[t].count_start;
				pit.timer[t].active = 1;
				pit.timer[t].out = 1;
				start(t);
			}
			break;
		default:
			EMU_DEBUG("reprogram_counter(): mode %d not implemented", pit.timer[t].mode);
			break;
	}
}

void start(bit8u t)
{
	
}

void pit_read_count(bit8u t, bit8u *data)
{
	switch (pit.timer[t].rwl)
	{
/*		case RWL_RW_LSB:
			*data = pit.timer[t].latch & 0xff;
			pit.timer[t].rwl = RWL_RW_MSB;
			break;
		case RWL_RW_MSB:
			*data = (pit.timer[t].latch >> 8) & 0xff;
			break;
		default:
			printf("pit_read_count(): tried to read from timer %d with rwl %d\n", t, pit.timer[t].rwl);;
			break;
*/										
	}
}

void pit_init ()
{
	int i;
	for (i = 0; i < 3; i++)
	{
		pit.timer[i].mode = 0;
		pit.timer[i].bcd = 0;
		pit.timer[i].msb = 0;
		pit.timer[i].count = 0;
		pit.timer[i].out = 0;
	}
}

void pit_tick()
{
	int i, prevout;

	prevout = pit.timer[0].out;
	
	for (i = 0; i < 3; i++)
	{
		switch (pit.timer[i].mode)
		{
			case 0: /* Mode 0: Interrupt on terminal count */
				if (pit.timer[i].count == 0)
					pit.timer[i].count = 0xFFFF;
				else
				{
					pit.timer[i].count--;
//					if (i == 0)
	//					DEBUG("timer dec to %x\n", pit.timer[i].count);
					if (pit.timer[i].count == 0)
						pit.timer[i].out = 1;
				}
				break;
			case 1: /* Mode 1: Hardware retriggerable one-shot */
				break;
			case 2: /* Mode 2: Rate generator */
				break;
			case 3: /* Mode 3: Square wave mode */
				break;
			case 4: /* Mode 4: Software triggered strobe */
				break;
			case 5: /* Mode 5: Hardware triggered strobe (retriggerable) */
				break;
		}
	}

	if ((prevout == 0) && (pit.timer[0].out == 1))
	{
		pic_interrupt(0);
	}
}
