//  Copyright (c) 2014 Jakub Filipowicz <jakubf@gmail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef P_EMDAS_H
#define P_EMDAS_H

#include <inttypes.h>

#include "emdas.h"

extern char *emdas_p_emdas_mnemo[EMD_OP_MAX];

void emdas_p_emdas_build_arg(struct emdas_buf *buf, uint16_t vop, struct emdas_op *op, uint16_t *varg);

#endif

// vim: tabstop=4 shiftwidth=4 autoindent
