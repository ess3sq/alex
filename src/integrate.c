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

#include <stdlib.h>

#include "../include/integrate.h"
#include "../include/diff.h"
#include "../include/func.h"
#include "../include/flags.h"

static unsigned long nbins = ALEX_DEFAULT_NBINS;

void alex_set_bins(unsigned long n) {
    alex_set_flag(ALEX_OK_FLAG);
    nbins = n;
}

unsigned long alex_get_bins(void) {
    return nbins;
}

alex_range *alex_make_range(double min, double max) {
    if (max < min) {
        alex_set_flag(ALEX_INV_RANGE_FLAG);
        return NULL;
    }

    alex_range *r = malloc(sizeof(alex_range));
    if (!r) {
        alex_set_flag(ALEX_BAD_ALLOC_FLAG);
        return NULL;
    }
    r->max = max;
    r->min = min;
    alex_set_flag(ALEX_OK_FLAG);
    return r;
}

double alex_range_abs(alex_range *range) {
    return range->max - range->min;
}

double alex_integrate_bins(alex_func_1d f, alex_range *range) {
    int n = alex_get_bins();
    double area = 0, cur = range->min, step = alex_range_abs(range) / n;
    while (cur <= range->max) {
        area += step * f(cur);
        cur += step;
    }

    alex_set_flag(ALEX_OK_FLAG);
    return area;
}

/*
double alex_integrate_bins2D(alex_func2d f, alex_range *rangeX, alex_func1d callback, *rangeY) {
    alex_integrate_bins()
}
*/

double alex_integrate_rect(alex_func_1d f, alex_range *range, int subintervals) {
    if (subintervals < 0) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0;
    }

    alex_set_flag(ALEX_OK_FLAG);

    double head = (range->max - range->min),
            body = (range->min + range->max);

    if (!subintervals) {
        return head * f(body / 2);
    }

    head /= subintervals;

    double mid = 0;
    for (int k = 1; k <= subintervals - 1; ++k) {
        mid += range->min + k*head;
    }

    body = f(body / 2 + mid);
    return head * body;
}

double alex_integrate_trap(alex_func_1d f, alex_range *range, int subintervals) {
    if (subintervals < 0) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0;
    }

    alex_set_flag(ALEX_OK_FLAG);

    double head = (range->max - range->min),
    body = f(range->min) + f(range->max);

    if (!subintervals) {
        return head * body / 2;
    }

    head /= subintervals;

    double mid = 0;
    for (int k = 1; k <= subintervals - 1; ++k) {
        mid += f(range->min + k*head);
    }
    body = body / 2 + mid;
    return head * body;
}