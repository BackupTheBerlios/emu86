/*
 * cpu_iflow.h
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

#ifndef __CPU_IFLOW_H
#define __CPU_IFLOW_H

inline void cpu_djmp8(bit8s dest);
inline void cpu_djmp16(bit16s dest);

inline void cpu_ijmp16(bit16u dest);

inline void cpu_int(bit8u i);

inline void cpu_call_far(bit16u destcs, bit16u destip);

#endif /* __CPU_IFLOW_H */
