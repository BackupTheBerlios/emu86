/*
 * cpu_idarith.c
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

#include "cpu.h"
#include "cpu_flags.h"
#include "cpu_regs.h"

inline void cpu_daa()
{
	if (((reg_al & 0x0F) > 9) || (flags.AF))
	{
		reg_al += 0x06;
		flags.AF = 1;
	}
	else
		flags.AF = 0;

	if ((reg_al > 0x9f) || (flags.CF))
	{
		reg_al += 0x60;
		flags.CF = 1;
	}
	else
		flags.CF = 0;

       set_zf(reg_al);
       set_sf8(reg_al);
       set_pf(reg_al);
}


