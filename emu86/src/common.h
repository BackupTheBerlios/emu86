/*                                                                              
 * common.h                                                                     
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

#ifndef __COMMON_H
#define __COMMON_H

typedef  unsigned char     bit8u;
typedef    signed char     bit8s;
typedef unsigned short     bit16u;
typedef   signed short     bit16s;
typedef  unsigned long     bit32u;
typedef    signed long     bit32s;
typedef         double     real64;
typedef unsigned long long bit64u;
typedef   signed long long bit64s;

/**
 * Holds a word which can be accessed through a low and a high byte
 */

typedef union {
        struct {
                bit8u lob, hib;
        };
        bit16u val;
} c_bit16u;

/**
 * Holds a dword which can be accessed through a low word and a high word
 */

typedef union {
	struct {
		bit16u low, hiw;
	};
        struct {
                c_bit16u c_low, c_hiw;
        };
        bit32u val;
} c_bit32u;

#endif /* __COMMON_H */
