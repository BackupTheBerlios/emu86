/*
 * 8259A.h
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

#ifndef __8259A_H
#define __8259A_H

#ifndef LOG_CHAN
# define LOG_CHAN "PIC"
#endif

#include "emu86.h"
#include "common.h"

void pic_init();
void pic_write(bit8u port, bit8u data);
void pic_read(bit8u port, bit8u *dest);
void pic_interrupt(bit8u interrupt);

#endif /* __8259A_H */
