/*
 * cpu_flags.h
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

#ifndef __CPU_FLAGS_H
#define __CPU_FLAGS_H

/**
 * Holds (E)FLAGS as a couple of integers for faster access
 */

typedef struct {

	/* System Flags */

	bit8u VM;	/* Virtual 8086 Mode */
	bit8u RF;	/* Resume Flag */
	bit8u NT;	/* Nested Task Flag */
	bit8u IOPL;	/* I/O Privilege Level */
	bit8u IF;	/* Interrupt Enable */
	
	/* Control Flags */

	bit8u DF;	/* Direction Flag */

	/* Status Flags */
	
	bit8u OF;	/* Overflow Flag */
	bit8u TF;       /* Trap Flag */
	bit8u SF;	/* Sign Flag */
	bit8u ZF;	/* Zero Flag */
	bit8u AF;	/* Adjust Flag */
	bit8u PF;	/* Parity Flag */
	bit8u CF;	/* Carry Flag */

} Flags;

extern Flags flags;
extern bit8u ptable[256];

inline bit16u cpu_inflate_flags();
inline void   cpu_deflate_flags(bit16u src);

#define set_cf_add(src,dest)            flags.CF=src<dest
#define set_cf_adc8(dest)               flags.CF=dest>>8
#define set_cf_adc16(dest)              flags.CF=dest>>16
#define set_cf_sbb8(dest)               flags.CF=(dest&0x100)==0x100
#define set_cf_sbb16(dest)              flags.CF=(dest&0x10000)==0x10000
#define set_cf_sub(dest,src)            flags.CF=(dest<src)

#define set_cf_sal8(pdest,src)          flags.CF=(src>8) && (pdest>>(8-src))&0x01
#define set_of_sal8(pdest,src,dest)     if (src==1) flags.OF=( ((pdest^dest)&0x80)>0 )
#define set_cf_sal16(pdest,src)         flags.CF=(src>16) && (pdest>>(16-src))&0x01
#define set_of_sal16(pdest,src,dest)    if (src==1) flags.OF=( ((pdest^dest)&0x8000)>0 )

#define set_cf_shr8(pdest,src)          flags.CF=(pdest>>(src-1))&0x01
#define set_of_shr8(pdest,src)          if (src==1) flags.OF=(pdest>=0x80)
#define set_cf_shr16(pdest,src)         flags.CF=(pdest>>(src-1))&0x01
#define set_of_shr16(pdest,src)         if (src==1) flags.OF=(pdest>=0x8000)

#define set_cf_rol8(dest)               flags.CF=dest & 0x01
#define set_of_rol8(dest,src)           if(src==1)flags.OF=((src^dest)&0x80)>0
#define set_cf_rol16(dest)              flags.CF=dest & 0x01
#define set_of_rol16(dest,src)          if(src==1)flags.OF=((src^dest)&0x8000)>0

#define set_cf_ror8(dest)               flags.CF=dest
#define set_of_ror8(dest,src)           if(src==1)flags.OF=((src^dest)&0x80)>0

#define set_of_add8(pdest,src,dest)     flags.OF=(dest^src)&(dest^pdest)&0x80
#define set_of_add16(pdest,src,dest)    flags.OF=(dest^src)&(dest^pdest)&0x8000
#define set_of_sub8(pdest,src,dest)     flags.OF=(pdest^src)&(pdest^dest)&0x80
#define set_of_sub16(pdest,src,dest)    flags.OF=(pdest^src)&(pdest^dest)&0x8000

#define set_zf(dest)                    flags.ZF=!dest
#define set_pf(dest)                    flags.PF=ptable[(bit8u)dest]

#define set_sf8(dest)                   flags.SF=dest>=0x80
#define set_sf16(dest)                  flags.SF=dest>=0x8000

#define set_af(pdest,src,dest)          flags.AF=((pdest^src)^dest)&0x10

#define clr_cf()                        flags.CF=0
#define clr_of()                        flags.OF=0


#endif /* __CPU_FLAGS_H */
