/*                                                                              
 * cpu_debug.c
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
#include "cpu_debug.h"
#include "cpu_regs.h"
#include "cpu_flags.h"
#include "cpu_ip.h"

void cpu_dump()
{
	EMU_DEBUG("Status:\n"
	      "  Instruction Opcode: 0x%02x  flags: %c%c%c%c%c%c%c%c%c\n"
	      "    AX = %04x  BX = %04x  CX = %04x  DX = %04x\n"
	      "    ES = %04x  SS = %04x  DS = %04x  CS = %04x\n"
	      "    BP = %04x  SI = %04x  DI = %04x  SP = %04x\n"
	      "    IP = %04x\n",
		*ip.ptr, 
		flags.AF ? 'A' : ' ', 
		flags.OF ? 'O' : ' ',
		flags.SF ? 'S' : ' ', 
		flags.ZF ? 'Z' : ' ',
		flags.CF ? 'C' : ' ',
		flags.PF ? 'P' : ' ',
		flags.TF ? 'T' : ' ', 
		flags.IF ? 'I' : ' ',
		flags.DF ? 'D' : ' ',
		reg_ax, reg_bx, reg_cx, reg_dx,
		sreg_es.val,
		sreg_ss.val,
		sreg_ds.val,
		sreg_cs.val,
		reg_bp, reg_si, reg_di, reg_sp,
		(ip.ptr - sreg_cs.ptr)
		);
}

void cpu_short_dump()
{
	EMU_DEBUG("\x1B[31mAX:\x1B[0m%04x"
	      " \x1B[31mBX:\x1B[0m%04x"
	      " \x1B[31mCX:\x1B[0m%04x"
	      " \x1B[31mDX:\x1B[0m%04x"
	      " \x1B[31mES:\x1B[0m%04x"
	      " \x1B[31mSS:\x1B[0m%04x"
	      " \x1B[31mDS:\x1B[0m%04x"
	      " \x1B[31mSI:\x1B[0m%04x"
	      " %c%c%c%c%c%c%c%c%c",
	      reg_ax, reg_bx, reg_cx, reg_dx,
	      sreg_es.val,
	      sreg_ss.val,
	      sreg_ds.val, reg_si,
              flags.AF ? 'A' : ' ',
              flags.OF ? 'O' : ' ',
              flags.SF ? 'S' : ' ',
              flags.ZF ? 'Z' : ' ',
              flags.CF ? 'C' : ' ',
              flags.PF ? 'P' : ' ',
              flags.TF ? 'T' : ' ',
              flags.IF ? 'I' : ' ',
              flags.DF ? 'D' : ' ');
}

void cpu_dump_mem(int s, int b, int ial)
{
/*	int i,k;
	printf("Memory dump: \n");
	k = ial-1;
	for (i = 0; i < b; i++)
	{	
		k++;
		if (k == ial)
		{
			printf("0x%.8x: ", s+i);
			k = 0;
		}
		printf("%.2x ", mem[s+i]);
		if (k == ial - 1) printf("\n");
	}*/
}
