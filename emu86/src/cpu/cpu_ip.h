/*
 * cpu_ip.h
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

#ifndef __CPU_IP_H
#define __CPU_IP_H

typedef struct {
	bit16u	 val;
	bit8u	*ptr;	
} instr_ptr;

extern instr_ptr ip;

inline void cpu_set_ip_val(bit16u val);
inline void cpu_sync_ip_val();
inline void cpu_sync_ip_ptr();

#endif /* __CPU_IP_H */
