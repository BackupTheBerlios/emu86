/*
 * 765.h
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

#ifndef __765_H
#define __765_H

#ifndef LOG_CHAN
# define LOG_CHAN "FDC"
#endif /* LOG_CHAN */

#include "emu86.h"
#include "common.h"
#include "timer.h" 

void fdc_timer_handler();

#endif /* __765_H */
