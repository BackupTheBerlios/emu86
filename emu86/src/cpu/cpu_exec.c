/*                                                                              
 * cpu_exec.c                                                                   
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
#include "cpu_exec.h"
#include "cpu_regs.h"
#include "cpu_flags.h"
#include "cpu_ip.h"
#include "cpu_fetch.h"
#include "cpu_modrm.h"
#include "cpu_debug.h"

#include "cpu_iflow.h"
#include "cpu_istack.h"
#include "cpu_ilogical.h"
#include "cpu_ishift.h"
#include "cpu_idecarith.h"
#include "cpu_ibinarith.h"
#include "cpu_idataptr.h"

#include "ports.h"

#include <stdlib.h>

#define seg(s)                          \
	segreg[DS].ptr = segreg[s].ptr; \
	segreg[SS].ptr = segreg[s].ptr; \
	cpu_exec_in();                  \
	cpu_sync_segreg_ptr(DS);	\
	cpu_sync_segreg_ptr(SS);
				

int verbose = 0;

inline void cpu_exec_in()
{
	bit8u opcode;
	
	Segreg tmpsr;
	
	bit8u  tmp8u;
	bit8u *tmp8u_ptr;
	bit16u tmp16u;
	
//	if (verbose)
//		cpu_short_dump();
/*
	if ((ip.ptr - sreg_cs.ptr) > 0xFFFF)
	{
		shutdown();
	}

	if ((ip.ptr - sreg_cs.ptr) == 0xECB7)
		verbose = 1;

	if ((ip.ptr - sreg_cs.ptr) == 0xECF4)
		verbose = 0;

	if ((ip.ptr - sreg_cs.ptr) == 0xED06)
		verbose = 0;*/

/*	if  ( ((ip.ptr - sreg_cs.ptr) > 0xE394) &&
	       ((ip.ptr - sreg_cs.ptr) < 0xE3DA) )
	{
		verbose = 1;
	} else verbose = 0; */
	
//	if ((ip.ptr - sreg_cs.ptr) == 0xE3DA) shutdown(); */
	
	switch (opcode = fetchb())
	{
	case 0x00: /* (00 /r) ADD r/m8,r8 - Add byte register to r/m byte */
		fetch_modrm8();
		cpu_add8(rm8, *r8);
		break;
	case 0x01: /* (01 /r) ADD r/m16,r16 - Add word register to r/m word */
		fetch_modrm16();
		cpu_add16(rm16, *r16);
		break;
	case 0x02: /* (02 /r) ADD r8,r/m8 - Add r/m byte to byte register */
		fetch_modrm8();
		cpu_add8(r8, *rm8);
		break;
	case 0x03: /* (03 /r) ADD r16,r/m16 - Add r/m word to word register */
		fetch_modrm16();
		cpu_add16(r16, *rm16);
		break;
	case 0x04: /* (04 ib) ADD AL,imm8 - Add immediate byte to AL */
		cpu_add8(&reg_al, fetchb());
		break;
	case 0x05: /* (05 iw) ADD AX,imm16 - Add immediate word to AX */
		cpu_add16(&reg_ax, fetchw());
		break;
	case 0x06: /* (06) PUSH ES - Push ES */
		cpu_push16(sreg_es.val);
		break;
	case 0x07: /* (07) POP ES - Pop top of stack into ES */
		cpu_pop16(&sreg_es.val);
		cpu_sync_segreg_ptr(ES);
		break;
	case 0x08: /* (08 /r) OR r/m8,r8 - OR byte register to r/m byte */
		fetch_modrm8();
		cpu_or8(rm8, *r8);
		break;
	case 0x09: /* (09 /r) OR r/m16,r16 - OR word register to r/m word */
		fetch_modrm16();
		cpu_or16(rm16, *r16);
		break;
	case 0x0A: /* (0A /r) OR r8,r/m8 - OR r/m byte to byte register */
		fetch_modrm8();
		cpu_or8(r8, *rm8);
		break;
	case 0x0B: /* (0B /r) OR r16,r/m16 - OR r/m word to word register */
		fetch_modrm16();
		cpu_or16(r16, *rm16);
		break;
	case 0x0C: /* (0C ib) OR AL,imm8 - OR immediate byte to AL */
		cpu_or8(&reg_al, fetchb());
		break;
	case 0x0D: /* (0D iw) OR AX,imm16 - OR immediate word to AX */
		cpu_or16(&reg_ax, fetchw());
		break;
	case 0x0E: /* (0E) PUSH CS - Push CS */
		cpu_push16(sreg_cs.val);
		break;
	case 0x0F: /* (0F ??) ? - ? (2 byte opcode) */
		goto NI;
	case 0x10: /* (10 /r) ADC r/m8,r8 - Add with carry byte register to r/m byte */
		fetch_modrm8();
		cpu_adc8(rm8, *r8);
		break;
	case 0x11: /* (11 /r) ADC r/m16,r16 - Add with carry word register to r/m word */
		fetch_modrm16();
		cpu_adc16(rm16, *r16);
		break;
	case 0x12: /* (12 /r) ADC r8,r/m8 - Add with carry r/m byte to byte register */
		fetch_modrm8();
		cpu_adc8(r8, *rm8);
		break;
	case 0x13: /* (13 /r) ADC r16,r/m16 - Add with carry r/m word to word register */
		fetch_modrm16();
		cpu_adc16(r16, *rm16);
		break;
	case 0x14: /* (14 ib) ADC AL,imm8 - Add with carry immediate byte to AL */
		cpu_adc8(&reg_al, fetchb());
		break;
	case 0x15: /* (15 iw) ADC AX,imm16 - Add with carry immediate word to AX */
		cpu_adc16(&reg_ax, fetchw());
		break;
	case 0x16: /* (16) PUSH SS - Push SS */
		cpu_push16(sreg_ss.val);
		break;
	case 0x17: /* (17) POP SS - Pop top of stack into SS */
		cpu_pop16(&sreg_ss.val);
		cpu_sync_segreg_ptr(SS);
		break;
	case 0x18: /* (18 /r) SBB r/m8,r8 - Subtract with borrow byte register from r/m byte */
		fetch_modrm8();
		cpu_sbb8(rm8, *r8);
		break;
	case 0x1E: /* (1E) PUSH DS - Push DS */
		cpu_push16(sreg_ds.val);
		break;
	case 0x1F: /* (1F) POP DS - Pop top of stack into DS */
		cpu_pop16(&sreg_ds.val);
		cpu_sync_segreg_ptr(DS);
		break;
	case 0x22: /* (22 /r) AND r8,r/m8 - AND r/m byte to byte register */
		fetch_modrm8();
		cpu_and8(r8, *rm8);
		break;
	case 0x24: /* (24 ib) AND AL,imm8 - AND immediate byte to AL */
		cpu_and8(&reg_al, fetchb());
		break;
	case 0x26: /* SEG ES: */
		seg(ES);
		break;
	case 0x27: /* (27) DAA - Decimal adjust AL after addition */
		cpu_daa();
		break;
	case 0x2A: /* (2A /r) SUB r8,r/m8 - Subtract byte register from r/m byte */
		fetch_modrm8();
		cpu_sub8(rm8, *r8);
		break;
	case 0x2B: /* (2B /r) SUB r16,r/m16 - Subtract word register from r/m word */
		fetch_modrm16();
		cpu_sub16(rm16, *r16);
		break;
	case 0x2C: /* (2C ib) SUB AL,imm8 - Subtract immediate byte from AL */
		cpu_sub8(&reg_al, fetchb());
		break;
	case 0x2E: /* SEG CS */
		seg(CS);
		break;
	case 0x32: /* (32 /r) XOR r8,r/m8 - Exclusive-OR byte register to r/m byte */
		fetch_modrm8();
		cpu_xor8(r8, *rm8);
		break;
	case 0x33: /* (33 /r) XOR r16,r/m16 - Exclusive-OR word register to r/m word */
		fetch_modrm16();
		cpu_xor16(r16, *rm16);
		break;
	case 0x36: /* SEG SS: */
		seg(SS);
		break;
	case 0x38: /* (38 /r) CMP r/m8,r8 - Compare byte register to r/m byte */
		fetch_modrm8();
		cpu_cmp16(*rm8, *r8);
		break;
	case 0x3A: /* (3A /r) CMP r8,r/m8 - Compare r/m byte to byte register */
		fetch_modrm8();
		cpu_cmp16(*r8, *rm8);
		break;
	case 0x3B: /* (3B /r) CMP r16,r/m16 - Compare r/m word to word register */
		fetch_modrm16();
		cpu_cmp16(*r16, *rm16);
		break;
	case 0x3C: /* (3C ib) CMP AL,imm8 - Compare immediate byte to AL */
		cpu_cmp8(reg_al, fetchb());
		break;
	case 0x3D: /* (3D iw) CMP AX,imm16 - Compare immediate word to AX */
		cpu_cmp16(reg_ax, fetchw());
		break;
	case 0x42: /* INC DX */
		cpu_inc16(&reg_dx);
		break;
	case 0x43: /* INC BX */
		cpu_inc16(&reg_bx);
		break;
	case 0x45: /* INC BP */
		cpu_inc16(&reg_bp);
		break;
	case 0x46: /* INC SI */
		cpu_inc16(&reg_si);
		break;
	case 0x47: /* INC DI */
		cpu_inc16(&reg_di);
		break;
	case 0x4A: /* DEC DX */
		cpu_dec16(&reg_dx);
		break;
	case 0x4B: /* DEC BX */
		cpu_dec16(&reg_bx);
		break;
	case 0x4F: /* DEC DI */
		cpu_dec16(&reg_di);
		break;
	case 0x50: /* PUSH AX */
		cpu_push16(reg_ax);
		break;
	case 0x51: /* PUSH CX */
		cpu_push16(reg_cx);
		break;
	case 0x52: /* PUSH DX */
		cpu_push16(reg_dx);
		break;
	case 0x53: /* PUSH BX */
		cpu_push16(reg_bx);
		break;
	case 0x55: /* PUSH BP */
		cpu_push16(reg_bp);
		break;
	case 0x56: /* PUSH SI */
		cpu_push16(reg_si);
		break;
	case 0x57: /* PUSH DI */
		cpu_push16(reg_di);
		break;
	case 0x58: /* POP AX */
		cpu_pop16(&reg_ax);
		break;
	case 0x59: /* POP CX */
		cpu_pop16(&reg_cx);
		break;
	case 0x5A: /* POP DX */
		cpu_pop16(&reg_dx);
		break;
	case 0x5B: /* POP BX */
		cpu_pop16(&reg_bx);
		break;
	case 0x5D: /* POP BP */
		cpu_pop16(&reg_bp);
		break;
	case 0x5E: /* POP SI */
		cpu_pop16(&reg_si);
		break;
	case 0x5F: /* POP DI */
		cpu_pop16(&reg_di);
		break;
	case 0x70: /* (70 cb) JO rel8 - Jump short if overflow (OF=1) */
		if (!flags.OF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x71: /* (71 cb) JNO rel8 - Jump short if not overflow (OF=0) */
		if (flags.OF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x72: /* (72 cb) JNAE rel8 - Jump short if not above or equal (CF=1) */
		if (!flags.CF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x73: /* (73 cb) JNB rel8 - Jump short if not below (CF=0) */
		if (flags.CF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x74: /* (74 cb) JZ rel8 - Jump short if 0 (ZF=1) */
		if (!flags.ZF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x75: /* (75 cb) JNZ rel8 - Jump short if not zero (ZF=0) */
		if (flags.ZF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x76: /* (76 cb) JNA rel8 - Jump short if not above (CF=1 or ZF=1) */
		if (!flags.ZF && !flags.CF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x78: /* (78 cb) JS rel8 - Jump short if sign (SF=1) */
		if (!flags.SF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x79: /* (79 cb) JNS rel8 - Jump short if not sign (SF=0) */
		if (flags.SF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x7A: /* (7A cb) JPE rel8 - Jump short if parity even (PF=1) */
		if (!flags.PF) ip.ptr++; else cpu_djmp8(fetchb());
		break;		
	case 0x7B: /* (7B cb) JPO rel8 - Jump short if parity odd (PF=0) */
		if (flags.PF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x7C: /* (7C cb) JL rel8 -  Jump short if less (SF<>OF) */
		if (flags.SF == flags.OF) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0x80:
		fetch_modrm8_opex();
		switch (opex)
		{
			case 0x01: /* (80 /1 ib) OR r/m8,imm8 - OR immediate byte to r/m byte */
				cpu_or8(rm8, fetchb());
				break;
			case 0x04: /* (80 /4 ib) AND r/m8,imm8 - AND immediate byte to r/m byte */
				cpu_and8(rm8, fetchb());
				break;
			case 0x07: /* (80 /7 ib) CMP r/m8,imm8 - Compare immediate byte to r/m byte */
				cpu_cmp8(*rm8, fetchb());
				break;
			default:
				goto NI;
		}
		break;
	case 0x81: 
		fetch_modrm16_opex();
		switch (opex)
		{
			case 0x00: /* (81 /0 iw) ADD r/m16,imm16 - Add immediate word to r/m word */
				cpu_add16(rm16, fetchw());
				break;
			case 0x04: /* (81 /4 iw) AND r/m16,imm16 - AND immediate word to r/m word */
				cpu_and16(rm16, fetchw());
				break;
			case 0x07: /* (81 /7 iw) CMP r/m16,imm16 - Compare immediate word to r/m word */
				cpu_cmp16(*rm16, fetchw());
				break;
			default:
				goto NI;
		}
		break;
	case 0x83:
		fetch_modrm16_opex();
		switch (opex)
		{
			case 0x00: /* (83 /0 ib) ADD r/m16,imm8 - Add sign-extended immediate byte to r/m word */
				cpu_add16(rm16, (bit16u) (bit8s) fetchb());
				break;
			case 0x05: /* (83 /5 ib) SUB r/m16,imm8 - Subtract sign-extended immediate byte from r/m word */
				cpu_sub16(rm16, (bit16u) (bit8s) fetchb());
				break;
			case 0x07: /* (83 /7 ib) CMP r/m16,imm8 - Compare sign extended immediate byte to r/m word */
				cpu_cmp16(*rm16, (bit16u) (bit8s) fetchb());
				break;
			default:
				goto NI;
		}
		break;
	case 0x86: /* (86 /r) XCHG r/m8,r8 - Exchange byte register with EA byte */
		fetch_modrm8();
		tmp8u = *r8;
		*r8 = *rm8;
		*rm8 = tmp8u;
		break;
	case 0x88: /* (88 /r) MOV r/m8,r8 - Move byte register to r/m byte */
		fetch_modrm8();
		*rm8 = *r8;
		break;
	case 0x89: /* (89 /r) MOV r/m16,r16 - Move word register to r/m word */
		fetch_modrm16();
		*rm16 = *r16;
		break;
	case 0x8A: /* (8A /r) MOV r8,r/m8 - Move r/m byte to byte register */
		fetch_modrm8();
		*r8 = *rm8;
		break;
	case 0x8B: /* (8B /r) MOV r16,r/m16 - Move r/m word to word register */
		fetch_modrm16();
		*r16 = *rm16;
		break;
	case 0x8C: /* (8C /r) MOV r/m16,Sreg - Move segment register to r/m word */
		fetch_modrm16_opex();
		*rm16 = segreg[opex].val;
		break;
	case 0x8E: /* (8E /r) MOV Sreg,r/m16 - Move r/m word to segment register */
		fetch_modrm16_opex();
		cpu_set_segreg_val(opex, *rm16);
		break;
	case 0x90: /* (90) NOP - No operation */
		break;
	case 0x9C: /* (9C) PUSHF - Push FLAGS */
		cpu_push16(cpu_inflate_flags());
		break;
	case 0x9D: /* (9D) POPF - Pop top of stack FLAGS */
		cpu_deflate_flags(*(bit16u *)(sreg_ss.ptr + reg_sp));
		reg_sp += 2;
		break;
	case 0x9E: /* (9E) SAHF - Store AH into flags SF ZF xx AF xx PF xx CF */
		cpu_deflate_flags(reg_ah);
		break;
	case 0x9F: /* (9F) LAHF - Load: AH := flags SF ZF xx AF xx PF xx CF */
		reg_ah = cpu_inflate_flags() & 0xFF;
		break;
	case 0xA0: /* (A0) MOV AL,moffs8 - Move byte at (seg:offset) to AL */
		reg_al = *fetchw_offs8();
		break;
	case 0xA1: /* (A1) MOV AX,moffs16 - Move word at (seg:offset) to AX */
		reg_ax = *fetchw_offs16();
		break;
	case 0xA2: /* (A2) MOV moffs8,AL - Move AL to (seg:offset) */
		*fetchw_offs8() = reg_al;
		break;
	case 0xA3: /* (A3) MOV moffs16,AX - Move AX to (seg:offset) */
		*fetchw_offs16() = reg_ax;
		break;
	case 0xA5: /* (A5) MOVSW - Move word DS:[(E)SI] to ES:[(E)DI] */
		*(bit16u *) (sreg_es.ptr + reg_di) = *(bit16u *) (sreg_ds.ptr + reg_si);
		reg_di += -4*flags.DF+2;
		reg_si += -4*flags.DF+2;
		break;
	case 0xA8: /* (A8 ib) TEST AL,imm8 - AND immediate byte with AL */
		cpu_test8(reg_al, fetchb());
		break;
	case 0xAA: /* (AA) STOSB - Store AL in byte ES:[(E)DI], update (E)DI */
		*(bit8u *) (sreg_es.ptr + reg_di) = reg_al;
		reg_di += -2*flags.DF+1;
		break;
	case 0xAB: /* (AB) STOSW - Store AX in word ES:[(E)DI], update (E)DI */
		*(bit16u *) (sreg_es.ptr + reg_di) = reg_ax;
		
		reg_di += -4*flags.DF+2;
		break;
	case 0xAC: /* (AC) LODSB - Load byte DS:[(E)SI] into AL */
		reg_al = *(bit8u *) (sreg_ds.ptr + reg_si);
		reg_si += -2*flags.DF+1;
		break;
	case 0xAE: /* (AE SCASB) - Compare bytes AL-ES:[DI], update (E)DI */
		DEBUG("cmp: %02x %02x\n", reg_al, *(sreg_es.ptr + reg_di)); 
		cpu_cmp8(reg_al, *(sreg_es.ptr + reg_di));
		reg_di += -2*flags.DF+1;
		break;
	case 0xB0: /* (B0 + rb) MOV reg8,imm8 - Move immediate byte to register */
		reg_al = fetchb();
		break;
	case 0xB1: /* MOV CL,1b */
		reg_cl = fetchb();
		break;
	case 0xB2: /* MOV DL,lb */
		reg_dl = fetchb();
		break;
	case 0xB3: /* MOV BL,lb */
		reg_bl = fetchb();
		break;
	case 0xB4: /* MOV AH,lb */
		reg_ah = fetchb();
		break;
	case 0xB5: /* MOV CH,lb */
		reg_ch = fetchb();
		break;
	case 0xB7: /* MOV BH,lb */
		reg_bh = fetchb();
		break;
	case 0xB8: /* (B8 + rw) MOV reg16,imm16 - Move immediate word to register */
		reg_ax = fetchw();
		break;
	case 0xB9: /* MOV CX,lw */
		reg_cx = fetchw();
		break;
	case 0xBA: /* MOV DX,lw */
		reg_dx = fetchw();
		break;
	case 0xBB: /* MOV BX,Iw */
		reg_bx = fetchw();
		break;
	case 0xBC: /* MOV SP,Iw */
		reg_sp = fetchw();
		break;
	case 0xBD: /* MOV BP,Iw */
		reg_bp = fetchw();
		break;
	case 0xBE: /* MOV SI,lw */
		reg_si = fetchw();
		break;
	case 0xBF: /* MOV DI,Iw */
		reg_di = fetchw();
		break;
	case 0xCA: /* (CA iw) RET imm16 - Return (far), same privilege, pop imm16 bytes */
		cpu_pop16(&tmp16u);
		cpu_pop16(&sreg_cs.val);
		cpu_sync_segreg_ptr(CS);
		ip.ptr = sreg_cs.ptr + tmp16u;
		break;
	case 0xC3: /* (C3) RET */
		cpu_pop16(&tmp16u);
//		DEBUG("ret to %04x:%04x\n", segreg[segreg_cs].val, tmp16u);
		ip.ptr = sreg_cs.ptr + tmp16u;
		break; 
	case 0xC6: /* (C6) MOV r/m8,imm8 - Move immediate byte to r/m byte */
		fetch_modrm8_opex();
		*rm8 = fetchb();
		break;
	case 0xC7: /* (C7) MOV r/m16,imm16 - Move immediate word to r/m word */
		fetch_modrm16_opex();
		*rm16 = fetchw();
		break;
	case 0xC5: /* (C5 /r) LDS r16,m16:16 - Load DS:r16 with pointer from memory */
		fetch_modrm16();
		cpu_load_ptr(r16, rm16, DS);
		break;
	case 0xCD: /* (CD ib) INT imm8 - Interrupt numbered by immediate byte */
		cpu_int(fetchb());
		break;
	case 0xCF: /* (CF) IRET - Interrupt return (far return and pop flags) */
		cpu_pop16(&tmp16u);
		cpu_pop16(&sreg_cs.val);
		
		cpu_sync_segreg_ptr(CS);
		ip.ptr = sreg_cs.ptr + tmp16u;
		cpu_pop16(&tmp16u);
		cpu_deflate_flags(tmp16u);
		break;
	case 0xD0:
		fetch_modrm8_opex();
		switch (opex)
		{
			case 0x04: /* (D0 /4) SAL r/m8,1 - Multiply r/m byte by 2, once */
				cpu_sal8(rm8, 1);
				break;
			default:
				goto NI;
		}
		break;
	case 0xD1:
		fetch_modrm16_opex();
		switch (opex)
		{
			case 0x04: /* (D1 /4) SHL r/m16,1 - Multiply r/m word by 2, once */
				cpu_sal16(rm16, 1);
				break;
			case 0x05: /* (D1 /5) SHR r/m16,1 - Unsigned divide r/m word by 2, once */
				cpu_shr16(rm16, 1);
				break;
			case 0x07: /* (D1 /7) SAR r/m16,1 - Signed divide^(1) r/m word by 2, once */
				cpu_sar16(rm16, 1);
				break;
			default:
				goto NI;
		}
		break;
	case 0xD2: 
		fetch_modrm8_opex();
		switch (opex)
		{
			case 0x00: /* (D2 /0) ROL r/m8,CL - Rotate 8 bits r/m byte left CL times */
				cpu_rol8(rm8, reg_cl);
				break;
			case 0x01: /* (D2 /1) ROR r/m8,CL -  Rotate 8 bits r/m byte right CL times */
				cpu_ror8(rm8, reg_cl);
				break;
			case 0x04: /* (D2 /4) SAL r/m8,CL - Multiply r/m byte by 2, CL times */
				cpu_sal8(rm8, reg_cl); 
				break;
			case 0x05: /* (D2 /5) SHR r/m8,CL - Unsigned divide r/m byte by 2, CL times */
				cpu_shr8(rm8, reg_cl);
				break;
			default: 
				goto NI;
		}
		break;
	case 0xD3: 
		fetch_modrm16_opex();
		switch (opex)
		{
			case 0x04: /* (D3 /4) SHL r/m16,CL - Multiply r/m word by 2, CL times */ 
				cpu_sal16(rm16, reg_cl);
				break;
			case 0x05: /* (D3 /5) SHR r/m16,CL - Unsigned divide r/m word by 2, CL times */
				cpu_shr16(rm16, reg_cl);
				break;
			default:
				goto NI;
		}			
		break;
	case 0xD7: /* (D7) XLATB - Set AL to memory byte DS:[(E)BX + unsigned AL] */
		reg_al = *(sreg_ds.ptr + reg_bx + (bit16u)reg_al);
		break;
	case 0xE2: /* (E2 cb) LOOP rel8 - DEC count; jump short if count <> 0 */
//		if (*ptr_ip == 0xFE) {DEBUG("waiting...\n"); reg_cx = 0; ptr_ip++; break; }
		reg_cx--;
		if (reg_cx > 0)
			cpu_djmp8(fetchb());
		else
			ip.ptr++;
		break;
	case 0xE3: /* (E3 cb) JCXZ rel8 - Jump short if CX register is 0 */
		if (reg_cx) ip.ptr++; else cpu_djmp8(fetchb());
		break;
	case 0xE4: /* (E4 ib) IN AL,imm8 - Input byte from immediate port into AL */
		port_in(fetchb(), &reg_al);
		break;
	case 0xE6: /* (E6 ib) OUT imm8,AL - Output byte AL to immediate port number */
		port_out(fetchb(), reg_al);
		break;
	case 0xE8: /* (E8 cw) CALL rel16 - Call near, displacement relative to next instruction */

/*		DEBUG("call to %04x:%04x\n", sreg_cs.val, 
		      ((ip.ptr - sreg_cs.ptr + (*(bit16u *)ip.ptr + 
		       2) ) & 0xFFFF)); */
		
		tmp16u = (ip.ptr - sreg_cs.ptr) + 2;
		cpu_push16(tmp16u);
		ip.ptr = sreg_cs.ptr + ((ip.ptr - sreg_cs.ptr + (*(bit16u *)ip.ptr + 2) ) & 0xFFFF);
		break;
	case 0xE9: /* (E9 cw) JMP rel16 - Jump near, displacement relative to next instruction */
		ip.ptr = sreg_cs.ptr + ((ip.ptr - sreg_cs.ptr + (*(bit16u *)ip.ptr + 2) ) & 0xFFFF);
		break;
	case 0xEA: /* (EA cd) JMP ptr16:16 - Jump intersegment, 4-byte immediate address */
		cpu_set_segreg_val(CS, *(bit16u *)(ip.ptr + 2));
		ip.ptr = sreg_cs.ptr + *(bit16u *)(ip.ptr);
		break;
	case 0xEB: /* (EB cb) JMP rel8 - Jump short */
		cpu_djmp8(fetchb());
		break;
	case 0xEC: /* (EC) IN AL,DX - Input byte from port DX into AL */
		port_in(reg_dx, &reg_al);
		break;
	case 0xEE: /* (EE) OUT DX,AL - Output byte AL to port number in DX */
		port_out(reg_dx, reg_al);
		break;
	case 0xF2: /* (F2) REPNE - Repeat following string operation */
		tmp8u_ptr = ip.ptr;
		while ((!flags.ZF) && (reg_cx))
		{
			ip.ptr = tmp8u_ptr;
			cpu_exec_in();
			reg_cx--;
		}
		break;
	case 0xF3: /* (F3) REP - Repeat following string operation */
		tmp8u_ptr = ip.ptr;
		if ((*ip.ptr != 0xAA) && (*ip.ptr != 0xAB))
			goto NI;
		while (reg_cx)
		{
			ip.ptr = tmp8u_ptr;
			cpu_exec_in();
			reg_cx--;
		}
		break;
	case 0xF5: /* (F5) CMC - Complement carry flag */
		flags.CF = !flags.CF;
		break;
	case 0xF6:
		fetch_modrm8_opex();
		switch (opex)
		{
			case 0x00: /* (F6 /0 ib) TEST r/m8,imm8 - AND immediate byte with r/m byte */
				cpu_test8(*rm8, fetchb());
				break;
			case 0x04: /* (F6 /4) MUL AL,r/m8 - Unsigned multiply (AX := AL * r/m byte) */
				cpu_mul8(*rm8);
				break;
			default:
				goto NI;
		}
		break;
	case 0xF8: /* (F8) CLC - Clear carry flag */
		flags.CF = 0;
		break;
	case 0xF9: /* (F9) STC - Set carry flag */
		flags.CF = 1;
		break;
	case 0xFA:
//		DEBUG("---- IF = 0\n");
		flags.IF = 0;
		break;
	case 0xFB: /* (FB) STI - Set interrupt flag; interrupts enabled at the end of the next instruction */
//		DEBUG("++++ IF = 1\n");
		flags.IF = 1;
		break;
	case 0xFC: /* (FC) CLD - Clear direction flag */
		flags.DF = 0;
		break;
	case 0xFD: /* (FD) STD - Set direction flag so (E)SI and/or (E)DI decrement */
		flags.DF = 1;
		break;
	case 0xF4: /* (F4) HLT - Halt */
		DEBUG("Processor halted\n");
		cpu_dump();
		goto end;
		break;
	case 0xF7:
		fetch_modrm16_opex();
		switch (opex)
		{
			case 0x06: /* (F7 /6) DIV AX,r/m16 - Unsigned divide DX:AX by r/m word (AX=Quo, DX=Rem) */
				cpu_div16(*rm16);
				break;
			default:
				goto NI;
		}
		break;
	case 0xFE:
		fetch_modrm8_opex();
		switch (opex)
		{
			case 0x00: /* (FE /0) INC r/m8 - Increment r/m byte by 1 */
				cpu_inc8(rm8);
				break;
			case 0x01: /* (FE /1) DEC r/m8 - Decrement r/m byte by 1 */
				cpu_dec8(rm8);
				break;
			default:
				goto NI;
		}
		break;
	case 0xFF: 
		fetch_modrm16_opex();
		switch (opex)
		{
			case 0x03: /* (FF /3) CALL m16:16 Call intersegment, address at r/m dword */
				cpu_dump_mem(0x40 * 16 + 0x67,4,4);
				cpu_dump();
				cpu_call_far(*(rm16+1), *rm16); /* beware.. */
				cpu_dump();
				break;
			case 0x04: /* (FF /4) JMP r/m16 - Jump near indirect */
				cpu_ijmp16(*rm16);
				break;
			default:
				goto NI;
				break;
		}
		break;
	default:
		goto NI;
	}
	return;
NI:
	ip.ptr--;
	DEBUG("OPCODE NOT IMPLEMENTED:\n");
	cpu_dump();
end:
	shutdown();
}
