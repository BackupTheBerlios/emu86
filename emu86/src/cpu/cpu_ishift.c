/*
 * cpu_ishift.c
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

/**
 * The shift and rotate instructions reposition the bits within the specified 
 * operand.
 *
 * These instructions fall into the following classes:
 *
 *  - Shift instructions
 *  - Double shift instructions
 *  - Rotate instructions
 */

/**
 * SAL (Shift Arithmetic Left) shifts the destination byte, word, or doubleword
 * operand left by one or by the number of bits specified in  the count operand 
 * (an immediate  value  or the  value contained  in CL).  The processor shifts 
 * zeros in from the right  (low-order) side of  the operand as  bits exit from 
 * the left (high-order) side.
 */

inline void cpu_sal8(bit8u *dest, bit8u src)
{
	bit8u tmp = *dest;
	
	*dest <<= (src & 0x1F);

	set_of_sal8(tmp, src, *dest);
	set_cf_sal8(src, *dest);
        set_af(tmp, src, *dest);
	set_sf8(*dest);
	set_zf(*dest);
        set_pf(*dest);
}

inline void cpu_sal16(bit16u *dest, bit8u src)
{
        bit16u tmp = *dest;

	*dest <<= (src & 0x1F);

	set_cf_sal16(src, *dest);
	set_zf(*dest);
	set_sf16(*dest);
	set_af(tmp, src, *dest);
	set_of_sal16(tmp, src, *dest);
	set_pf(*dest);
}

/**
 * SHL (Shift Logical Left) is a synonym for SAL (refer to SAL).
 */

#define cpu_shl8 cpu_sal8
#define cpu_shl16 cpu_sal16

/**
 * SHR (Shift Logical Right) shifts  the  destination byte, word, or doubleword
 * operand right by one or by the number of bits specified in the count operand
 * (an  immediate value  or the value contained  in CL).  The  processor shifts 
 * zeros in from the left side of the operand as bits exit from the right side. 
 */
 
inline void cpu_shr8(bit8u *dest, bit8u src)
{
	bit8u tmp = *dest;

	src &= 0x1F;

	*dest >>= src;

	set_zf(*dest);
	set_cf_shr8(tmp,src);
	set_pf(*dest);
	set_sf8(*dest);
	set_of_shr8(tmp, src);
}

inline void cpu_shr16(bit16u *dest, bit8u src)
{
	bit16u tmp = *dest;

	src &= 0x1F;

	*dest >>= src;

	set_zf(*dest);
	set_cf_shr16(tmp,src);
	set_pf(*dest);
	set_sf8(*dest);
	set_of_shr16(tmp, src);
}

/**
 * SAR (Shift Arithmetic Right)   shifts   the  destination   byte,   word,  or 
 * doubleword operand to the right by one or by the number of bits specified in  * the  count  operand  (an immediate value or the value contained in CL).  The
 * processor preserves the sign of the operand by shifting in zeros on the left
 * (high-order)  side  if the  value is  positive or by shifting by ones if the
 * value is negative. 
 */

inline void cpu_sar8(bit8u *dest, bit8u src)
{
	bit8u tmp = *dest;

	src &= 0x1F;

	if (src < 8)
		if (tmp & 0x80)
			*dest = (tmp >> src) | (0xff << (8 - src));
		else
			*dest = (tmp >> src);
	else
    		if (tmp & 0x80)
			*dest = 0xff;
		else
			*dest = 0;

	if (src < 8)
		flags.CF = ((tmp >> (src - 1)) & 0x01);
	else
		if (tmp & 0x80)
			flags.CF = 1;
		else
			flags.CF = 0;

	set_zf(*dest);
	set_sf8(*dest);
	if (src == 1)
		clr_of();
	set_pf(*dest);
}

inline void cpu_sar16(bit16u *dest, bit8u src)
{
        bit16u tmp = *dest;

        src &= 0x1F;

        if (src < 8)
                if (tmp & 0x80)
                        *dest = (tmp >> src) | (0xff << (8 - src));
                else
                        *dest = (tmp >> src);
        else
                if (tmp & 0x80)
                        *dest = 0xff;
                else
                        *dest = 0;

        if (src < 8)
                flags.CF = ((tmp >> (src - 1)) & 0x01);
        else
                if (tmp & 0x80)
                        flags.CF = 1;
                else
                        flags.CF = 0;

        set_zf(*dest);
        set_sf16(*dest);
        if (src == 1)
                clr_of();
        set_pf(*dest);
}


/**
 * ROL (Rotate Left) rotates the byte, word, or  doubleword destination operand
 * left  by one or  by the  number of  bits specified in the count  operand (an
 * immediate value or  the value contained in CL). For each rotation specified,
 * the high-order  bit that  exits from  the left of the operand returns at the
 * right to become the new low-order bit of the operand. 
 */

inline void cpu_rol8(bit8u *dest, bit8u src)
{
	src &= 0x07;

	*dest = (*dest<<src) | (*dest >> (8 - src));

	set_cf_rol8(*dest);
	set_of_rol8(*dest, src);
}

inline void cpu_rol16(bit16u *dest, bit8u src)
{
	src &= 0x07;

	*dest = (*dest<<src) | (*dest >> (16 - src));

	set_cf_rol16(*dest);
	set_of_rol16(*dest, src);
}

/**
 * ROR (Rotate Right) rotates the byte, word, or doubleword destination operand
 * right by  one or  by  the  number of  bits specified  in  the  count operand
 * (an  immediate  value  or  the  value contained  in  CL).  For each rotation
 * specified,  the low-order  bit  that  exits from  the  right  of the operand
 * returns at the left to become the new high-order bit of the operand.
 */

inline void cpu_ror8(bit8u *dest, bit8u src)
{
	src &= 0x07;
	
	*dest = (*dest>>src) | (*dest << (8 - src));
	
	set_cf_ror8(*dest);
	set_of_ror8(*dest, src);
}

