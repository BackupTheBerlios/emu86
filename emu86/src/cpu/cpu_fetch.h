/*                                                                              
 * cpu_fetch.h                                                                  
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

#ifndef __CPU_FETCH_H
#define __CPU_FETCH_H

#define fetchb()  *(((bit8u*) ip.ptr)++)
#define fetchw()  *(((bit16u*)ip.ptr)++)
#define fetchdw() *(((bit32u*)ip.ptr)++)

#define fetchw_offs8()  (bit8u  *) (sreg_ds.ptr + fetchw())
#define fetchw_offs16() (bit16u *) (sreg_ds.ptr + fetchw()) 

#endif /* __CPU_FETCH_H */
