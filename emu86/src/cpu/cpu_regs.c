/*
 * cpu_regs.c
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
#include "cpu_regs.h"

Reg32  datareg[4];
Reg32  addrreg[4];
Segreg segreg[6];

inline void cpu_set_segreg_val(bit8u r, bit16u val)
{
	segreg[r].ptr = MEMBASE + ((segreg[r].val = val) * 16);
}

inline void cpu_sync_segreg_ptr(bit8u r)
{
	segreg[r].ptr = MEMBASE + (segreg[r].val * 16);
}
