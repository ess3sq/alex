/*
 *   ALEX is a C library and framework for mathematical operations
 *   Copyright (C) 2020  Lorenzo Calza
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License along
 *   with this program; if not, write to the Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "../include/algebra.h"
#include "../include/utils.h"
#include "../include/flags.h"

unsigned int alex_gcd(unsigned int m, unsigned int n) {
    if (m == 0 && n == 0) {
        alex_set_flag(ALEX_ALG_INV_OP_FLAG);
        return 0;
    }
    else if(n < m) {
        alex_swap_int(m,n);
    }
    alex_set_flag(ALEX_OK_FLAG);

    int r;
    while(1) {
        r = m % n;
        if (r == 0) return n;
        m = n;
        n = r;
    }
}

unsigned int alex_lcm(unsigned int m, unsigned int n) {
    alex_set_flag(ALEX_OK_FLAG);
    if (m == 0 && n == 0) return 0;
    return m*n/alex_gcd(m,n);
}
