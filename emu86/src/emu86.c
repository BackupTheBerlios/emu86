#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>

#include "common.h"

#include "cpu/cpu.h"
#include "mem/mem.h"
#include "hardware/PIT/8254.h"
#include "hardware/PIC/8259A.h"
#include "hardware/PPI/8255A.h"


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
	FILE *f;

	initscr();                                                            
	cbreak();
        noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);  

	cpu_init();
	pit_init();
	pic_init();
	dma_init();
	ppi_init();
	mem_init();

//	f=fopen("../rom/wdbios.rom","r");fread(mem+0xc8000,8192,1,f);fclose(f);
	f=fopen("../rom/basicc11.f6","r");fread(mem+0xf6000,8192,1,f);fclose(f);
	f=fopen("../rom/basicc11.f8","r");fread(mem+0xf8000,8192,1,f);fclose(f);
	f=fopen("../rom/basicc11.fa","r");fread(mem+0xfa000,8192,1,f);fclose(f);
	f=fopen("../rom/basicc11.fc","r");fread(mem+0xfc000,8192,1,f);fclose(f);
	f=fopen("../rom/pc081682.bin","r");fread(mem+0xfe000,8192,1,f);fclose(f);
	
	mainloop();
	endwin();
	return 0;
}

void shutdown()
{
	endwin();
	exit(0);
}
