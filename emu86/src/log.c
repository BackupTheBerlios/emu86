/*                                                                              
 * log.c                                                                     
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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "emu86.h"
#include "log.h"

static int	logging;
static FILE	*log_file_fd = NULL;

int log_init(int enable, char *log_file)
{
	if ((logging = enable))
	{
		if (!(log_file_fd = fopen (log_file, "w")))
		{
			fprintf(stderr, "Can't open %s: %s", log_file, strerror(errno));
			return 0;
		}

		EMU_INFO("%s %s (%s %s) started", PACKAGE, VERSION, __DATE__, __TIME__);
	}
	return 1;
}

void log(char *pfx, char *log_chan, char *fmt, ...)
{                                                                                       
        char    buf[4096];                                                              
        size_t  buf_len = 0;                                                            
        va_list args;                                                                   
                                                                                        
        if (strlen(log_chan))                                                                   
                buf_len = snprintf(buf, sizeof(buf) - 1, "%s: [%s] ", pfx, log_chan);   
        else                                                                            
                buf_len = snprintf(buf, sizeof(buf) - 1, "%s: ", pfx);                  
                                                                                        
        va_start(args, fmt);                                                            
        vsnprintf(buf + buf_len, sizeof(buf) - buf_len - 1, fmt, args);                 
        va_end(args);

	if (logging)
	{
		fprintf(log_file_fd, buf);
		fprintf(log_file_fd, "\n");
		fflush(log_file_fd);
	}
}
