/*                                                                              
 * cpu.c                                                                      
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

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>

#include "cpu.h"
#include "cpu_exec.h"
#include "cpu_regs.h"
#include "cpu_flags.h"
#include "cpu_ip.h"
#include "cpu_fetch.h"

#include "../mem/mem.h"

#include "ports.h"

void cpu_init()
{
	reg_eax = 0;
	
	reg_dl = 23;    /* Stepping ID */
	reg_dh = 3;	/* Device ID (80386) */
	
	cpu_set_segreg_val(CS, 0xffff);
	cpu_set_segreg_val(DS, 0);
	cpu_set_segreg_val(ES, 0);
	cpu_set_segreg_val(SS, 0);
		
	cpu_inflate_flags(0);
	cpu_set_ip_val(0);
}
