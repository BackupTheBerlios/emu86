/*
 * cpu_idataptr.c
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

inline void cpu_load_ptr(bit16u *dest, bit16u *src, bit8u sreg)
{
	*dest = *src;
	cpu_set_segreg_val(sreg, *(src + 1)); // beware - it adds 2 ;)
}
