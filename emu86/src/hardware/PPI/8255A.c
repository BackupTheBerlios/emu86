/*
 * 8255A.c
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

#include "8255A.h"

#define BOOT_FLOPPY   1
#define MATHCHIP      1
#define MEM_BANKS     4
#define VIDEO_ADAPTER MDA
#define FLOPPY_DISKS  1

#define MDA     0x03
#define CGA_40c 0x02
#define CGA_80c 0x01
#define EGA     0x00
#define VGA     0x00

#define DIP_SWITCHES	(BOOT_FLOPPY |               \
                         (MATHCHIP << 1) |           \
			 ((MEM_BANKS-1) << 2) |      \
			 (VIDEO_ADAPTER << 4) |      \
			 ((FLOPPY_DISKS-1) << 6)     \
			)

typedef struct _ppi {
	bit8u	port_a;

	bit8u	read_high_switches;
} PPI;

PPI ppi;

void ppi_init()
{
	ppi.read_high_switches = 0;

	ppi.port_a = 0xaa;
}

void ppi_write_port_a(bit8u val)
{
	ppi.port_a = val;
	DEBUG("[PPI] wrote port a (%02x)\n", val);
}

void ppi_read_port_a(bit8u *val)
{
	*val = ppi.port_a;
	DEBUG("[PPI] read port a (%02x)\n", *val);
}

void ppi_write_port_b(bit8u val)
{
	ppi.read_high_switches = val & 0x8;
	DEBUG("[PPI] wrote port b (%02x)\n", val);
}

void ppi_read_port_c(bit8u *dest)
{
	bit8u res = 0;
	if (!ppi.read_high_switches) 
		res |= (DIP_SWITCHES & 0x0f);
	else
		res |= ((DIP_SWITCHES & 0xf0) >> 4);
	*dest = res;
	DEBUG("DIP is: %02x\n",DIP_SWITCHES);
	DEBUG("read_high_switches: %d\n", ppi.read_high_switches);
	DEBUG("[PPI] read port c (%02x)\n", *dest);
}
