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

#include "../include/flags.h"
#include "../include/diff.h"
#include "../include/integrate.h"

static double dx_step = ALEX_DEFAULT_DX;

double alex_secant_method(alex_func_1d f, alex_range *range, unsigned iterations) {
    if (iterations == 0) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0.;
    }

    double x0, x1, x2;
    x0 = range->min;
    x1 = range->max;

    for (int i = 0; i < iterations; ++i) {
        x2 = x1 - f(x1) * (x1 - x0) / (f(x1) - f(x0));
        x0 = x1;
        x1 = x2;
    }

    return x2;
}

double alex_diff(alex_func_1d f, double x) {
    return (f(x + dx_step) - f(x)) / dx_step;
}

void alex_set_dx(double dx) {
    if (dx < 0) {
        alex_set_flag(ALEX_NEG_DX);
        return;
    }
    dx_step = dx;
    alex_set_flag(ALEX_OK_FLAG);
}
double alex_get_dx(void) {
    return dx_step;
}