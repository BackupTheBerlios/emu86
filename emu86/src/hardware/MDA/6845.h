/*
 * 6845.h
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

#ifndef __6845_H
#define __6845_H

#ifndef LOG_CHAN
# define LOG_CHAN ""
#endif /* LOG_CHAN */

#include "emu86.h"
#include "common.h"

void mda_read_status(bit8u *data);
void mda_select_reg(bit8u data);
void mda_write_reg(bit8u data);
void mda_textmode_out();

#endif /* __6845_H */

