/*
 * cpu_iflow.c
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

#include "cpu_ip.h"
#include "cpu_flags.h"
#include "cpu_istack.h"
#include "cpu_regs.h"

/**
 * JMP (Jump) unconditionally transfers control to the target location. JMP is
 * a one-way transfer of execution;  it does not save a return address on  the
 * stack.
 */

inline void cpu_djmp8(bit8s dest)
{
	ip.ptr += dest;
}

inline void cpu_djmp16(bit16s dest)
{
	ip.ptr += dest;

	ip.ptr = ((ip.ptr - MEMBASE) & 0xFFFF) + MEMBASE;
}

inline void cpu_ijmp16(bit16u dest)
{
	ip.ptr = sreg_cs.ptr + (dest & 0xFFFF);
}

inline void cpu_int(bit8u i)
{
	if (!flags.IF) return;

	cpu_push16(cpu_inflate_flags());
	
	flags.IF = 0;
	flags.TF = 0;

	cpu_push16(sreg_cs.val);
	cpu_push16(ip.ptr - sreg_cs.ptr);

	bit16u offset = *(bit16u*)(MEMBASE + i * 4);
	cpu_set_segreg_val(CS, *(bit16u*)(MEMBASE + i * 4 + 2) );
	ip.ptr = sreg_cs.ptr + offset;
	
	EMU_DEBUG("int 0x%.2x (%cw) vector: %04x:%04x", i, i >= 0x10 ? 's' : 'h',
              sreg_cs.val, ip.ptr - sreg_cs.ptr);

}

inline void cpu_call_far(bit16u destcs, bit16u destip)
{
	bit16u tmp16u;

	cpu_push16(sreg_cs.val);
	tmp16u = (ip.ptr - sreg_cs.ptr) + 2;
	cpu_push16(tmp16u);

	cpu_set_segreg_val(CS, destcs);
	cpu_set_ip_val(destip);
}
