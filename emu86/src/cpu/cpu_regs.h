/*                                                                              
 * cpu_regs.h                                                                   
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

#ifndef __CPU_REGS_H
#define __CPU_REGS_H

typedef c_bit32u Reg32;

/**
 * Holds a segment register
 */

typedef struct {
	bit16u  val;
	bit8u  *ptr;	
} Segreg;

extern Reg32  datareg[4];
extern Reg32  addrreg[4];
extern Segreg segreg[6];

extern Segreg ow_segreg[6];

enum { A,  B,  C,  D };			/* data registers */
enum { SP, BP, SI, DI };		/* address registers */
enum { ES, CS, SS, DS };		/* segment registers */

#define reg_al  datareg[A].c_low.lob
#define reg_ah  datareg[A].c_low.hib
#define reg_ax  datareg[A].low
#define reg_eax datareg[A].val

#define reg_bl  datareg[B].c_low.lob
#define reg_bh  datareg[B].c_low.hib
#define reg_bx  datareg[B].low
#define reg_ebx datareg[B].val

#define reg_cl  datareg[C].c_low.lob
#define reg_ch  datareg[C].c_low.hib
#define reg_cx  datareg[C].low
#define reg_ecx datareg[C].val

#define reg_dl  datareg[D].c_low.lob
#define reg_dh  datareg[D].c_low.hib
#define reg_dx  datareg[D].low
#define reg_edx datareg[D].val

#define reg_si  addrreg[SI].low
#define reg_esi addrreg[SI].val

#define reg_di  addrreg[DI].low
#define reg_edi addrreg[DI].val

#define reg_sp  addrreg[SP].low
#define reg_esp addrreg[SP].val

#define reg_bp  addrreg[BP].low
#define reg_ebp addrreg[BP].val

#define sreg_cs segreg[CS]
#define sreg_ds segreg[DS]
#define sreg_es segreg[ES]
#define sreg_ss segreg[SS]

inline void cpu_set_segreg_val (bit8u r, bit16u val);
inline void cpu_sync_segreg_ptr(bit8u r);

#endif /* __CPU_REGS_H */
