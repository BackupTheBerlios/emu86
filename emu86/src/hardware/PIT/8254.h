/*
 * 8254.h
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

#ifndef __8254_H
#define __8254_H

#ifndef LOG_CHAN
# define LOG_CHAN "PIT"
#endif /* LOG_CHAN */

#include "emu86.h"
#include "common.h"

void pit_write_cw(bit8u val);
void pit_write_timer(bit8u t, bit8u data);
void pit_read_latch(bit8u t, bit8u *data);
void reprogram_counter(bit8u t, bit16u val);
void start(bit8u t);
void pit_read_count(bit8u t, bit8u *data);
void pit_init();
void pit_tick();

#endif /* __8254_H */
