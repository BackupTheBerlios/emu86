/*
 * 765.c
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

#include "765.h"

typedef struct _fdc {
	bit8u	DOR;
} FDC;

FDC fdc;

void fdc_init()
{
	timer_init(TIMER_FDC, *fdc_timer_handler, 50000);
	timer_start(TIMER_FDC);
}

void fdc_write_dor(bit8u val)
{
	fdc.DOR = val;
	DEBUG("[FDC] wrote DOR (%02x)\n", val);
}

void fdc_read_dor(bit8u *val)
{
	*val = fdc.DOR;
	DEBUG("[FDC] read DOR (%02x)\n", *val);
}

void fdc_timer_handler()
{
	DEBUG("[FDC] timer handler..\n");
	timer_reset(TIMER_FDC);
}
