/*
 * 8255A.h
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

#ifndef __8255A_H
#define __8255A_H

#ifndef LOG_CHAN
# define LOG_CHAN "PPI"
#endif /* LOG_CHAN */

#include "emu86.h"
#include "common.h"

void ppi_init();
void ppi_write_port_a(bit8u val);
void ppi_read_port_a(bit8u *val);
void ppi_write_port_b(bit8u val);
void ppi_read_port_c(bit8u *dest);

#endif /* __8255A_H */
