/*                                                                              
 * emu86.c                                                                      
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
#include <string.h>
#include <curses.h>
#include <errno.h>

#include "emu86.h"
#include "common.h"

#include "cpu/cpu.h"
#include "mem/mem.h"
#include "hardware/PIT/8254.h"
#include "hardware/PIC/8259A.h"
#include "hardware/PPI/8255A.h"
#include "hardware/FDC/765.h"

int load_rom(char *filename, int offset, int size, char *md5)
{
	FILE	*f;
	size_t 	 n;

	EMU_DEBUG("Loading rom %s (%d bytes) into 0x%.5x", filename, size, offset);

	f = fopen(filename,"r");
	
	if (!f)
	{
		EMU_FATAL(("fopen(%s, \"r\") failed: %s", filename, strerror(errno)));
	}
	
	/* TODO: check md5 hash */
	
	n = fread(MEMBASE + offset, 1, size, f);

	if (n != size)
	{
		EMU_FATAL("couldn't read %d bytes from \"%s\"", size, filename);
	}
	
	fclose(f);
}

void mainloop()
{
	int got;
	int u = 1;                                                              
        int z = 0;    
	int o = 0;
        for(;;)                                                                 
        {
		o++;
		if (o == 1000) {
			got = getch();
			if (got != ERR) {
				DEBUG("got: %x\n", got);
				if (got == 'a')
				{
					ppi_write_port_a(0x3b);
					pic_interrupt(1);
				} else
				{
					ppi_write_port_a(0x3b | 0x80);
					pic_interrupt(1);
				}
			}
		 	o= 0;
		}
                z++;
		process_timers(50);
                cpu_exec_in();                                                  
                pit_tick();                                                     
                if (z  == 100000)                                               
                {                                                               
                z = 0;                                                          
                mda_textmode_out();                                             
                }                                                               
                u++;                                                            
                if (u > 3) u=1;                                                 
                if (!(u % 2))                                                   
                        pit_tick();                                             
        }                         
}

int main()
{
	log_init(1, "emu86.log");

        mem_init();

/*	load_rom("../rom/wdbios.rom", 0xc8000, 8192, "a39b2b1c3e298b3599995c353d16c3ad");*/
	load_rom("../rom/basicc11.f6", 0xf6000, 8192, "69e2bd1d08c893cbf841607c8749d5bd");
	load_rom("../rom/basicc11.f8", 0xf8000, 8192, "5f85ff5ea352c1ec11b084043fbb549e");
	load_rom("../rom/basicc11.fa", 0xfa000, 8192, "04a285d5dc8d86c60679e8f3c779dcc4");
	load_rom("../rom/basicc11.fc", 0xfc000, 8192, "b086a6980fc5736098269e62b59726ef");
	load_rom("../rom/pc081682.bin", 0xfe000, 8192, "1584aeaadebba4bc95783f1fa0fa3db8");

        cpu_init();
        pit_init();
        pic_init();
        dma_init();
        ppi_init();
        fdc_init();

        initscr();
        cbreak();
        noecho();
        nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
	

	mainloop();
	endwin();
	return 0;
}

void shutdown()
{
	endwin();
	exit(0);
}
