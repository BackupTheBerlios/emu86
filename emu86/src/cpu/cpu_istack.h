/*
 * istack.h
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

#ifndef __CPU_ISTACK_H
#define __CPU_ISTACK_H

inline void cpu_push8(bit8u src);
inline void cpu_push16(bit16u src);

inline void cpu_pop8(bit8u *dest);
inline void cpu_pop16(bit16u *dest);

#endif /* __CPU_ISTACK_H */
