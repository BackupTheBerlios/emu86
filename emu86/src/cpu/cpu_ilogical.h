/*
 * cpu_ilogical.h
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

#ifndef __CPU_ILOGICAL_H
#define __CPU_ILOGICAL_H

inline void cpu_and8(bit8u *dest, bit8u src);
inline void cpu_and16(bit16u *dest, bit16u src);

inline void cpu_test8(bit8u dest, bit8u src);

inline void cpu_or8(bit8u *dest, bit8u src);
inline void cpu_or16(bit16u *dest, bit16u src);

inline void cpu_xor8(bit8u *dest, bit8u src);
inline void cpu_xor16(bit16u *dest, bit16u src);

#endif /* __CPU_ILOGICAL_H */ 
