/*
 * istack.c
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

/**
 * PUSH (Push) decrements the stack pointer (SP), then transfers the source 
 * operand to the top of stack indicated by SP. 
 */

inline void cpu_push8(bit8u src)
{
        reg_sp -= 1;
	*(bit8u *)(sreg_ss.ptr + reg_sp) = src;
}

inline void cpu_push16(bit16u src)
{
	reg_sp -= 2;
	*(bit16u *)(sreg_ss.ptr + reg_sp) = src;
}

/**
 * POP (Pop) transfers the byte or word at the current top of stack  (indicated 
 * by SP)  to the destination operand,  and then increments SP  to point to the 
 * new top of stack.
 */

inline void cpu_pop8(bit8u *dest)
{
        *dest = *(bit8u *)(sreg_ss.ptr + reg_sp);
	reg_sp += 1;
}
		

inline void cpu_pop16(bit16u *dest)
{
	*dest = *(bit16u *)(sreg_ss.ptr + reg_sp);
	reg_sp += 2;
}

