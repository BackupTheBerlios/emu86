/*
 * 6845.c
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

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
 
#include "../../cpu/cpu.h"
#include "../../mem/mem.h"

#include "6845.h"

int u = 0;

typedef struct _mda {
	c_bit16u addr;
	bit8u reg;
} MDA;

MDA mda;

void mda_read_status(bit8u *data)
{
//	DEBUG("[MDA] status byte read\n");
	u++;
	if (u == 4) { u = 0; *data = 0; } else *data = 9;
}

void mda_select_reg(bit8u data)
{
	mda.reg = data;
//	DEBUG("[MDA] register %02x selected\n", data);
}

void mda_write_reg(bit8u data)
{
	switch (mda.reg)
	{
		case 0x0C:
			mda.addr.hib = data;
			break;
		case 0x0D:
			mda.addr.lob = data;
//			DEBUG("[MDA] address space set to: %04x\n", mda.addr);
			break;
		default:
//			DEBUG("[MDA] set unimplemented register %02x to %02x\n",
//			      mda.reg, data);
			break;
	}
}

bit32u was_last = 4324;

char buf[32000];

void mda_textmode_out()
{
	bit32u now = 0;
	int i = 0;
	bit8u x,y;
	char *ptr;
/*tr = mem + 0xb000 * 16;

	for (y = 0; y<24; y++) 
		for (x = 0; x < 80; x++) {
			now += *ptr;
			ptr++;
		}

	if (now == was_last)
		return;
	else
	{
		was_last = now;
	}
	
//	printf("update: %d\n", now);
*/	
	erase();
	ptr = mem + 0xb000 * 16;

	for (y = 0; y<24; y++)
	{
		for (x = 0; x < 80; x++)
		{
			if ((*ptr >= 32) && (*ptr <= 126))
				mvaddch(y,x,*ptr);
			ptr += 2;
		}
	}
	refresh();
}
