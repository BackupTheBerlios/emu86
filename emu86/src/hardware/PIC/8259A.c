/*
 * 8259A.c
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
#include <stdarg.h>

#include "8259A.h"

typedef struct _pic {
	bit8u p20;
	bit8u p21;

	bit8u next_icw;
	
	bit8u icw4_needed;
	bit8u single_8259;
	bit8u bit4u_iv;
	bit8u level_triggered;

	bit8u int_offset;

	bit8u irq[16];
} PIC;

PIC pic;			

void pic_init()
{
	pic.next_icw = 1;
}

void pic_write(bit8u port, bit8u data)
{
	int i;
//	DEBUG("wrote %02x to port %02x\n", data, port);
//	DEBUG("icw %02x\n", pic.next_icw);
	switch (pic.next_icw)
	{
		case 0x01:
			pic.next_icw++;
			if (port != 0x20)
				EMU_DEBUG("wrote icw1 on port 0x21"); 
			else
				pic.p20 = data;
				
			pic.icw4_needed     = data & 0x01;
			pic.single_8259     = (data >> 1) & 0x01;
			pic.bit4u_iv        = (data >> 2) & 0x01;
			pic.level_triggered = (data >> 3) & 0x01;

			EMU_DEBUG("icw4 needed: %d single 8259: %d 4bit iv: %d level triggered: %d",
			       pic.icw4_needed, pic.single_8259,pic.bit4u_iv, pic.level_triggered);
					      
			break;
		case 0x02:
			pic.next_icw++;
			if (port != 0x21)
				EMU_DEBUG("wrote icw2 on port 0x20");
			else
				pic.p21 = data;

			pic.int_offset = data & 0xf0;
			EMU_DEBUG("offset set to %02x", pic.int_offset);
			break;
		case 0x03:
			if (port != 0x21)
				EMU_DEBUG("wrote icw3 on port 0x20");
			else
				pic.p21 = data;
			pic.next_icw++;
			/* slave stuff */
			if (!pic.icw4_needed)
				pic.next_icw++;
			break;
		case 0x04:
			/* blar */
			if (port != 0x21)
				EMU_DEBUG("wrote icw3 on port 0x20");
			else
				pic.p21 = data;
			pic.next_icw++;
			break;
		case 0x05:
			/* IMR 1 */
			pic.p21 = data;
			for (i=0;i<8;i++)
			{
				pic.irq[i] = data & 0x01;
				data >>= 1;
			}

			EMU_DEBUG("wrote IMR1, irqs: %c%c%c%c%c%c%c%c"
			      " (o - off, S - serviced)",
			      pic.irq[0] ? 'o' : 'S',
			      pic.irq[1] ? 'o' : 'S',
			      pic.irq[2] ? 'o' : 'S',
			      pic.irq[3] ? 'o' : 'S',
			      pic.irq[4] ? 'o' : 'S',
			      pic.irq[5] ? 'o' : 'S',
			      pic.irq[6] ? 'o' : 'S',
			      pic.irq[7] ? 'o' : 'S');
			break;
			
	}	
}

void pic_read(bit8u port, bit8u *dest)
{
	if (port == 0x20)
		*dest = pic.p20;
	else
		*dest = pic.p21;
	EMU_DEBUG("read %02x from port %02x (PIC)",*dest,port);
}

void pic_interrupt(bit8u interrupt)
{
	interrupt += 0x08;
	EMU_DEBUG("IRQ %d", interrupt);
	cpu_int(interrupt);
}
