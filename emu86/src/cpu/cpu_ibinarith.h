/*
 * cpu_ibinarith.h
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

#ifndef __CPU_IBINARITH_H
#define __CPU_IBINARITH_H

inline void cpu_add8(bit8u *dest, bit8u src);
inline void cpu_add16(bit16u *dest, bit16u src);

inline void cpu_adc8(bit8u *dest, bit8u src);
inline void cpu_adc16(bit16u *dest, bit16u src);

inline void cpu_sbb8(bit8u *dest, bit8u src);

inline void cpu_dec8(bit8u *dest);
inline void cpu_dec16(bit16u *dest);

inline void cpu_inc8(bit8u *dest);
inline void cpu_inc16(bit16u *dest);

inline void cpu_cmp8(bit8u dest, bit8u src);
inline void cpu_cmp16(bit16u dest, bit16u src);

inline void cpu_sub8(bit8u *dest, bit8u src);
inline void cpu_sub16(bit16u *dest, bit16u src);

inline void cpu_div8(bit16u dest);
inline void cpu_div16(bit16u dest);
		
inline void cpu_mul8(bit8u src);

#endif /* __CPU_IBINARITH_H */
