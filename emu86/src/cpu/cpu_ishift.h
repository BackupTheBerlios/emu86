/*
 * cpu_ishift.h
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

#ifndef __CPU_ISHIFT_H
#define __CPU_ISHIFT_H

inline void cpu_sal8(bit8u *dest, bit8u src);
inline void cpu_sal16(bit16u *dest, bit8u src);
 
inline void cpu_shr8(bit8u *dest, bit8u src);
inline void cpu_shr16(bit16u *dest, bit8u src);

inline void cpu_sar8(bit8u *dest, bit8u src);
inline void cpu_sar16(bit16u *dest, bit8u src);

inline void cpu_rol8(bit8u *dest, bit8u src);
inline void cpu_rol16(bit16u *dest, bit8u src);

inline void cpu_ror8(bit8u *dest, bit8u src);

#endif /* __CPU_ISHIFT */
