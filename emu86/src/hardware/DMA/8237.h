/*                                                                              
 * 8237.h                                                                      
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

#ifndef __8237_H
#define __8237_H

#ifndef LOG_CHAN
# define LOG_CHAN "DMA"
#endif

#include "emu86.h"
#include "common.h"

void dma_init();
void dma_write_offset(bit8u c, bit8u offset);
void dma_read_offset(bit8u c, bit8u *dest);
void dma_write_wordcount(bit8u c, bit8u wordcount);
void dma_read_wordcount(bit8u c, bit8u *dest);
void dma_write_command_reg(bit8u val);
void dma_read_status_reg(bit8u *dest);
void dma_write_req_reg(bit8u val);
void dma_write_mask_reg(bit8u val);
void dma_write_mode_reg(bit8u val);
void dma_clear_flipflop();
void dma_clear_cr();
void dma_clear_mr();
void dma_master_clear(bit8u val);

#endif /* __8237_H */
