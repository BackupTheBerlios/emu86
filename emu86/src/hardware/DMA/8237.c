/*                                                                              
 * 8237.c                                                                      
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

#include "8237.h"

typedef struct _dma_controller {
	bit8u mem2mem_dma;
	bit8u ch0_addr_hold;
	bit8u disabled;
	bit8u compressed_timing_mode;
	bit8u rotating_priority;
	bit8u ext_write_mode;
	bit8u drq_sensing_active_high;
	bit8u back_sensing_active_high;

	bit8u status_reg;
} DMA_controller;

#define XFER_VERIFY 0
#define XFER_WRITE  1
#define XFER_READ   2

#define MODE_DEMAND  0
#define MODE_SINGLE  1
#define MODE_BLOCK   2
#define MODE_CASCADE 3

typedef struct _dma_channel {
	bit16u offset;
	bit16u page;
	bit16u wordcount;

	bit8u wordcount_lsb;
	bit8u offset_lsb;

	bit8u xfer_type;
	bit8u mode;

	bit8u auto_init;
	bit8u addr_inc;

	bit8u masked;
} DMA_channel;

DMA_controller dma_controller;
DMA_channel dma_channel[8];

void dma_init()
{
	bit8u i;

	dma_controller.status_reg=0x0F;

	for (i = 0; i < 3; i++)
	{
		dma_channel[i].offset_lsb = 1;
		dma_channel[i].wordcount_lsb = 1;
	}
}

void dma_write_offset(bit8u c, bit8u offset)
{
	if (dma_channel[c].offset_lsb)
	{
		dma_channel[c].offset_lsb = 0;
		dma_channel[c].offset = (dma_channel[c].offset & 0xFF00) | 
		                        offset;
		EMU_DEBUG("wrote lsb %02x offset for channel %x (%04x)", 
		          offset, c, dma_channel[c].offset);
	}
	else
	{
		dma_channel[c].offset_lsb = 1;
		dma_channel[c].offset = (dma_channel[c].offset & 0x00FF) | 
		                        (offset << 8);
                EMU_DEBUG("wrote msb %02x offset for channel %x (%04x)", 
		          offset, c, dma_channel[c].offset);
	}
}

void dma_read_offset(bit8u c, bit8u *dest)
{
	*dest = dma_channel[c].offset;
	EMU_DEBUG("offset of channel %x (%x) read", c, *dest);
}

void dma_write_wordcount(bit8u c, bit8u wordcount)
{

        if (dma_channel[c].wordcount_lsb)
        {
                dma_channel[c].wordcount_lsb = 0;
                dma_channel[c].wordcount = (dma_channel[c].wordcount & 0xFF00) |
                                           wordcount;
                EMU_DEBUG("wrote lsb %02x wordcount for channel %x (%04x)",
                      wordcount, c, dma_channel[c].wordcount);
        }
        else
        {
                dma_channel[c].wordcount_lsb = 1;
                dma_channel[c].wordcount = (dma_channel[c].wordcount & 0x00FF) |
                                           (wordcount << 8);
                EMU_DEBUG("wrote msb %02x wordcount for channel %x (%04x)",
                          wordcount, c, dma_channel[c].wordcount);
        }
}

void dma_read_wordcount(bit8u c, bit8u *dest)
{
        *dest = dma_channel[c].wordcount;
	EMU_DEBUG("wordcount of channel %x (%x) read", c, *dest);
}

void dma_write_command_reg(bit8u val)
{
	dma_controller.mem2mem_dma              = val & 0x01;
	dma_controller.ch0_addr_hold            = val & 0x02;
	dma_controller.disabled	                = val & 0x04;
	dma_controller.compressed_timing_mode   = val & 0x08;
	dma_controller.rotating_priority        = val & 0x10;
	dma_controller.ext_write_mode	        = val & 0x20;
	dma_controller.drq_sensing_active_high  = val & 0x40;
	dma_controller.back_sensing_active_high = val & 0x80;
	
	EMU_DEBUG("wrote command register: (%02x)\n"
	          "    memory-to-memory DMA:        %s\n"
	          "    Ch0 address hold:            %s\n"
	          "    controller disabled:         %s\n"
	          "    compressed timing mode:      %s\n"
	          "    rotating priority:           %s\n"
	          "    extended write mode:         %s\n"
	          "    DRQ sensing as active high:  %s\n"
	          "    BACK sensing as active high: %s",
	      val,
	      dma_controller.mem2mem_dma ? "enabled" : "disabled",
	      dma_controller.ch0_addr_hold ? "enabled" : "disabled",
	      dma_controller.disabled ? "yes" : "no",
	      dma_controller.compressed_timing_mode ? "yes" : "no",
	      dma_controller.rotating_priority ? "enabled" : "disabled",
	      dma_controller.ext_write_mode ? "1" : "late write",
	      dma_controller.drq_sensing_active_high ? "1" : "low",
	      dma_controller.back_sensing_active_high ? "1" : "low");
}

void dma_read_status_reg(bit8u *dest)
{
	*dest = dma_controller.status_reg;
	EMU_DEBUG("read status (%02x)", *dest);
}

void dma_write_req_reg(bit8u val)
{
	EMU_DEBUG("wrote request register (%02x)", val);
}

void dma_write_mask_reg(bit8u val)
{
	bit8u c;

	c = val & 0x03;

	dma_channel[c].masked = val & 0x04;
	
	EMU_DEBUG("channel %x %s", c,
	      dma_channel[c].masked ? "masked" : "unmasked");
}

void dma_write_mode_reg(bit8u val)
{
	bit8u c;

	c = val & 0x03;

	dma_channel[c].xfer_type = (val >> 2) & 0x03;
	dma_channel[c].auto_init = val & 0x10;
	dma_channel[c].addr_inc = val & 0x20;
	dma_channel[c].mode = (val >> 6) & 0x03;

	EMU_DEBUG("wrote mode register (%02x)\n"
	      "    channel: %d\n"
	      "    xfer type: %s\n"
	      "    auto initialization: %s\n"
	      "    address %s\n"
	      "    mode: %s", 
	      val, c,

	      dma_channel[c].xfer_type == 0 ? "verify" :
	      dma_channel[c].xfer_type == 1 ? "write"  : "read",
	      
	      dma_channel[c].auto_init ? "enabled" : "disabled",
	      dma_channel[c].addr_inc  ? "increment" : "decrement",
	      
	      dma_channel[c].mode == 0 ? "demand" :
	      dma_channel[c].mode == 1 ? "single" :
	      dma_channel[c].mode == 2 ? "block"  : "cascade");
}
	
void dma_clear_flipflop()
{
	EMU_DEBUG("flipflop cleared");
}

void dma_clear_cr()
{
	EMU_DEBUG("control register cleared");
}

void dma_clear_mr()
{
	EMU_DEBUG("mask register cleared");
}

void dma_master_clear(bit8u val)
{
	EMU_DEBUG("master clear (%02x)", val);
}
