/*
 * cpu_flags.c
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

Flags   flags;

bit8u   ptable[256] = {	1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
			0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
			0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
			0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
			0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
			0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
			0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
			0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
			0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
			1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1  };

inline bit16u cpu_inflate_flags()
{
        bit16u tmp = 0;

        if (flags.CF) tmp |= 0x0001;
        /* 1 */
        if (flags.PF) tmp |= 0x0004;
        /* 0 */
        if (flags.AF) tmp |= 0x0010;
        /* 0 */
        if (flags.ZF) tmp |= 0x0040;
        if (flags.SF) tmp |= 0x0080;
        if (flags.TF) tmp |= 0x0100;
        if (flags.IF) tmp |= 0x0200;
        if (flags.DF) tmp |= 0x0400;
        if (flags.OF) tmp |= 0x0800;
        /* IOPL1... */
        /* IOPL2... */
        if (flags.NT) tmp |= 0x4000;
        /* 0 */

        return tmp;
}

inline void cpu_deflate_flags(bit16u src)
{
        flags.CF = src & 0x1;
        /* 1 */
        flags.PF = (src >> 2) & 0x1;
        /* 0 */
        flags.AF = (src >> 4) & 0x1;
        /* 0 */
        flags.ZF = (src >> 6) & 0x1;
        flags.SF = (src >> 7) & 0x1;
        flags.TF = (src >> 8) & 0x1;
        flags.IF = (src >> 9) & 0x1;
        flags.DF = (src >> 10) & 0x1;
        flags.OF = (src >> 11) & 0x1;
        /* IOPL1... */
        /* IOPL2... */
        flags.NT = (src >> 14) & 0x4000;
        /* 0 */
}


