/*                                                                              
 * mem.h                                                                      
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

#ifndef __MEM_H
#define __MEM_H

#include "common.h"

#define MEMBASE mem

extern bit8u mem[1024*1024];

void mem_init();

#endif /* __MEM_H */
