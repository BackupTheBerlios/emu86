/*
 * cpu_ibinarith.c
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
#include "cpu_regs.h"

inline void cpu_add8(bit8u *dest, bit8u src)
{
	bit8u tmp = *dest;

	*dest += src;

	set_cf_add(tmp, *dest);
	set_zf(*dest);
	set_sf8(*dest);
	set_af(tmp, src, *dest);
	set_of_add8(tmp, src, *dest);
	set_pf(*dest);
}

inline void cpu_add16(bit16u *dest, bit16u src)
{
	bit16u tmp = *dest;

	*dest += src;

	set_cf_add(tmp, *dest);			
	set_zf(*dest);
	set_sf16(*dest);			
	set_af(tmp, src, *dest);
	set_of_add16(tmp, src, *dest);		
	set_pf(*dest);
}

inline void cpu_adc8(bit8u *dest, bit8u src)
{
        bit8u tmp = *dest;

        *dest += src + flags.CF;

        set_cf_adc8(*dest);
        set_zf(*dest);
        set_sf8(*dest);
        set_af(tmp, src, *dest);
        set_of_add8(tmp, src, *dest);
        set_pf(*dest);
}

inline void cpu_adc16(bit16u *dest, bit16u src)
{
        bit16u tmp = *dest;

	src += flags.CF;

        *dest += src;

        set_cf_adc16(*dest);
        set_zf(*dest);
        set_sf16(*dest);
        set_af(tmp, src, *dest);
        set_of_add16(tmp, src, *dest);
        set_pf(*dest);
}

inline void cpu_sbb8(bit8u *dest, bit8u src)
{
	bit8u tmp = *dest;

	src += flags.CF;

	*dest -= src;

	set_cf_sbb8(*dest);
	set_zf(*dest);
	set_sf8(*dest);
	set_af(tmp, src, *dest);
	set_of_sub8(tmp, src, *dest);
	set_pf(*dest);
}

inline void cpu_dec8(bit8u *dest)
{
        bit8u tmp = *dest;

        (*dest)--;

        set_zf(*dest);
        set_sf8(*dest);
        set_af(tmp, 1, *dest);
        set_of_sub8(tmp, 1, *dest);
        set_pf(*dest);
}

inline void cpu_dec16(bit16u *dest)
{
	bit16u tmp = *dest;
	
	(*dest)--;
	
        set_zf(*dest);
        set_sf16(*dest);
        set_af(tmp, 1, *dest);
        set_of_sub16(tmp, 1, *dest);
 	set_pf(*dest);
}

inline void cpu_inc8(bit8u *dest)
{
	bit8u tmp = *dest;

	(*dest)++;

	set_cf_add(tmp, *dest);	
	set_zf(*dest);
	set_sf8(*dest);
	set_af(tmp, 1, *dest);
	set_of_add8(tmp, 1, *dest);
	set_pf(*dest);					
}

inline void cpu_inc16(bit16u *dest)
{
        bit16u tmp = *dest;

	(*dest)++;

	set_cf_add(tmp, *dest);
	set_zf(*dest);
	set_sf16(*dest);
	set_af(tmp, 1, *dest);
	set_of_add16(tmp, 1, *dest);
	set_pf(*dest);
}

inline void cpu_cmp8(bit8u dest, bit8u src)
{
	bit8u tmp = dest;

	dest -= src;

	set_cf_sub(tmp, src);
	set_zf(dest);
	set_sf8(dest);
	set_af(tmp, src, dest);
	set_of_sub8(tmp, src, dest);
	set_pf(dest);
}

inline void cpu_cmp16(bit16u dest, bit16u src)
{
        bit16u tmp = dest;

        dest -= src;

        set_cf_sub(tmp, src);
        set_zf(dest);
        set_sf16(dest);
        set_af(tmp, src, dest);
        set_of_sub16(tmp, src, dest);
        set_pf(dest);
}

inline void cpu_sub8(bit8u *dest, bit8u src)
{
        bit8u tmp = *dest;

        *dest -= src;

        set_cf_sub(tmp, src);
        set_zf(*dest);
        set_sf8(*dest);
        set_af(tmp, src, *dest);
        set_of_sub8(tmp, src, *dest);
        set_pf(*dest);
}

inline void cpu_sub16(bit16u *dest, bit16u src)
{
        bit16u tmp = *dest;

        *dest -= src;

        set_cf_sub(tmp, src);
        set_zf(*dest);
        set_sf16(*dest);
        set_af(tmp, src, *dest);
        set_of_sub16(tmp, src, *dest);
        set_pf(*dest);
}

inline void cpu_div8(bit16u dest)
{
	reg_al = ((reg_ax / dest) & 0xFF);
	reg_ah = reg_ax % dest;
}

inline void cpu_div16(bit16u dest)
{
	bit32u dividend;
	bit32u res;
	
	dividend = (reg_dx << 16) + reg_ax;

	if (!dest)
		cpu_int(0); /* div by zero */
	else
	{
		res = dividend / dest;
		if (res > 0xFFFF)
		{
			cpu_int(0);
		}
		else
		{
			reg_dx = dividend % dest;
			reg_ax = res;
		}
	}
}
		
inline void cpu_mul8(bit8u src)
{
	reg_ax = reg_al * src;
	flags.CF = flags.OF = reg_ah;
}

