#include "cpu.h"

#include "hardware/DMA/8237.h"
#include "hardware/FDC/765.h"
#include "hardware/MDA/6845.h"
#include "hardware/PIC/8259A.h"
#include "hardware/PIT/8254.h"
#include "hardware/PPI/8255A.h"

void port_out(bit16u port, bit8u data)
{
	switch (port)
	{
		/* 000-00F  8237 DMA controller */
	
		case 0x000: /* Channel 0 address register */
			dma_write_offset(0,data);
			break;
		case 0x001: /* Channel 0 word count */
			dma_write_wordcount(0,data);
			break;
		case 0x002: /* Channel 1 address register */
			dma_write_offset(1,data);
			break;
		case 0x003: /* Channel 1 word count */
			dma_write_wordcount(1,data);
			break;
		case 0x004: /* Channel 2 address register */
			dma_write_offset(2,data);
			break;
		case 0x005: /* Channel 2 word count */
			dma_write_wordcount(2,data);
			break;
		case 0x006: /* Channel 3 address register */
			dma_write_offset(3,data);
			break;
		case 0x007: /* Channel 3 word count */
			dma_write_wordcount(3,data);
			break;
		case 0x008: /* Status/command register */
			dma_write_command_reg(data);
			break;
		case 0x009: /* Request register */
			dma_write_req_reg(data);
			break;
		case 0x00A: /* Mask register */
			dma_write_mask_reg(data);
			break;
		case 0x00B: /* Mode register */
			dma_write_mode_reg(data);
			break;
		case 0x00C: /* Clear MSB/LSB flip flop */
			dma_clear_flipflop();
			break;
		case 0x00D: /* Master clear temp register */
			dma_clear_cr();
			break;
		case 0x00E: /* Clear mask register */
			dma_clear_mr();
			break;
		case 0x00F: /* Multiple mask register */
			dma_master_clear(data);
			break;
		
		/* 020-02F  8259A Master Programmable Interrupt Controller */

		case 0x020: pic_write(port, data); break;
		case 0x021: pic_write(port, data); break;
		
		/* 040-05F  8253 or 8254 Programmable Interval Timer */
		
		case 0x040:
			pit_write_timer(0,data);
			break;
		case 0x041: pit_write_timer(1,data); break;
		case 0x042: pit_write_timer(2,data); break;
		case 0x043: pit_write_cw(data); break;

		case 0x060: ppi_write_port_a(data); break;
		case 0x061: ppi_write_port_b(data); break;

		case 0x3B4: mda_select_reg(data); break;
		case 0x3B5: mda_write_reg(data); break;

		default:
			EMU_DEBUG("sent %02x to unmapped port %03x", data, port);
			break;
	}
}

void port_in(bit16u port, bit8u *data)
{
	switch (port)
	{
		case 0x000: dma_read_offset(0, data); break;
		case 0x001: dma_read_wordcount(0, data); break;
		case 0x002: dma_read_offset(1, data); break;
		case 0x003: dma_read_wordcount(1, data); break;  
		case 0x004: dma_read_offset(2, data); break;
		case 0x005: dma_read_wordcount(2, data); break;
		case 0x006: dma_read_offset(3, data); break;
		case 0x007: dma_read_wordcount(3, data); break;
		case 0x008: dma_read_status_reg(data); break;
		
		case 0x040: pit_read_latch(0, data); break;
		case 0x041: pit_read_latch(1, data); break;
		case 0x042: pit_read_latch(2, data); break;
	
		case 0x020: pic_read(port, data); break;
		case 0x021: pic_read(port, data); break;
		
		case 0x060: ppi_read_port_a(data); break;
		case 0x062: ppi_read_port_c(data); break;
		
		case 0x3BA: mda_read_status(data); break;
		
		default:
			EMU_DEBUG("tried to read from unmapped port %03x", port);
			*data = 0;
			break;
	}
}


