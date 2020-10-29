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
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "../include/poly.h"
#include "../include/utils.h"
#include "../include/flags.h"

#define ALEX_POLY_PRINT_BUFSIZE 100

static alex_poly *pub_poly;

alex_poly *alex_make_poly(unsigned int deg, double coeffs[]) {
    alex_poly *poly = malloc(sizeof(alex_poly));
    if (poly == NULL) {
        alex_set_flag(ALEX_BAD_ALLOC_FLAG);
        return NULL;
    }

    poly->deg = deg;
    poly->coeffs = calloc(deg + 1, sizeof(double));

    if (poly->coeffs == NULL) {
        alex_set_flag(ALEX_BAD_ALLOC_FLAG);
        return NULL;
    }

    for (int i = 0; i <= deg; ++i) {
        poly->coeffs[i] = coeffs[i];
    }

    alex_set_flag(ALEX_OK_FLAG);
    return poly;
}

void alex_free_poly(alex_poly *poly) {
    if (poly == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return;
    }
    else if (poly == pub_poly)
        pub_poly = NULL;

    free(poly->coeffs);
    free(poly);
    alex_set_flag(ALEX_OK_FLAG);
}

char *alex_poly_print(alex_poly *poly, char *dest) {
    return alex_poly_printf(poly, dest, "%g"); // flags set by alex_poly_printf()
}

char *alex_poly_printf(alex_poly *poly, char *dest, const char *format) {
    for (unsigned int i = 0; i <= poly->deg; ++i) {
        strcat(dest, poly->coeffs[i] < 0 ? "- " : "+ ");
        sprintf(dest + strlen(dest), format, fabs(poly->coeffs[i]));
        sprintf(dest + strlen(dest), "x^%u ", i);
    }
    return dest;
}

unsigned int alex_poly_deg(alex_poly *poly) {
    if (poly == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0;
    }

    alex_set_flag(ALEX_OK_FLAG);
    return poly->deg;
}

double alex_poly_coeff(alex_poly *poly, unsigned int index) {
    if (index > poly->deg) {
        alex_set_flag(ALEX_POLY_INDEX_GT_DEG_FLAG);
        return alex_poly_lead(poly);
    }

    alex_set_flag(ALEX_OK_FLAG);
    return poly->coeffs[index];
}

double alex_poly_eval(alex_poly *poly, double x) {
    double res = 0;

    for (int i = 0; i < poly->deg + 1; ++i) {
        res += poly->coeffs[i] * pow(x, i);
    }

    alex_set_flag(ALEX_OK_FLAG);
    return res;
}

alex_poly *alex_poly_diff(alex_poly *poly) {
    if (poly->deg == 0) {
        double *coeffs = malloc(sizeof(double));
        if (coeffs == NULL) {
            alex_set_flag(ALEX_BAD_ALLOC_FLAG);
            return NULL;
        }
        *coeffs = 0.;
        return alex_make_poly(0u, coeffs);
    }

    double *coeffs = calloc(poly->deg, sizeof(double));
    if (coeffs == NULL) {
        alex_set_flag(ALEX_BAD_ALLOC_FLAG);
        return NULL;
    }

    for (int i = 0; i <= poly->deg - 1; ++i) {
        coeffs[i] = poly->coeffs[i + 1] * ((double) i + 1);
    }

    alex_poly *diff = alex_make_poly(poly->deg - 1, coeffs);
    if (diff == NULL) {
        return NULL; // flag already set by alex_make_poly()
    }

    alex_set_flag(ALEX_OK_FLAG);
    return diff;
}

alex_poly *alex_poly_integ(alex_poly *poly, double c) {
    if (poly == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return NULL;
    }

    double *coeffs = calloc(poly->deg + 2, sizeof(double));
    if (coeffs == NULL) {
        alex_set_flag(ALEX_BAD_ALLOC_FLAG);
        return NULL;
    }

    coeffs[0] = c;
    for (int i = 0; i < poly->deg + 1; ++i) {
        coeffs[i + 1] = poly->coeffs[i] / ((double) (i + 1));
    }

    alex_poly *integ = alex_make_poly(poly->deg + 1, coeffs);
    if (integ == NULL) {
        return NULL; // flag already set by alex_make_poly()
    }

    alex_set_flag(ALEX_OK_FLAG);
    return integ;
}

double alex_poly_integ_range(alex_poly *poly, alex_range *range) {
    if (range == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0.;
    }

    double integral;
    alex_poly *integ = alex_poly_integ(poly, 0.);

    if (integ == NULL) {
        return 0; // flag already set by alex_poly_integ()
    }

    integral = alex_poly_eval(integ, range->max) - alex_poly_eval(integ, range->min);
    alex_free_poly(integ);

    alex_set_flag(ALEX_OK_FLAG);
    return integral;
}

static double _poly_func(double x) {
    return alex_poly_eval(pub_poly, x);
}

alex_func_1d alex_poly_func(alex_poly *poly) {
    if (poly == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return NULL;
    }

    pub_poly = poly;
    alex_set_flag(ALEX_OK_FLAG);
    return &_poly_func;
}

double alex_poly_lead(alex_poly *poly) {
    if (poly == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0.;
    }

    alex_set_flag(ALEX_OK_FLAG);
    return poly->coeffs[poly->deg];
}

double alex_poly_trail(alex_poly *poly) {
    if (poly == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0.;
    }

    alex_set_flag(ALEX_OK_FLAG);
    return poly->coeffs[0];
}

int alex_poly_isconst(alex_poly *poly) {
    if (poly == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0;
    }

    alex_set_flag(ALEX_OK_FLAG);
    return poly->deg == 0;
}

int alex_poly_cmp(alex_poly *p, alex_poly *q) {
    if (p == NULL || q == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0;
    }
    alex_set_flag(ALEX_OK_FLAG);

    if (p->deg != q->deg) {
        return p->deg - q->deg;
    }

    for (int i = 0; i <= p->deg; ++i) {
        if (p->coeffs[i] != q->coeffs[i])
            return p->deg + 1 - i;
    }

    return 0;
}

alex_poly *alex_poly_cpy(alex_poly *poly) {
    if (poly == NULL) {
        alex_set_flag(ALEX_INV_PARAM_FLAG);
        return 0;
    }

    alex_poly *poly_cpy = alex_make_poly(poly->deg, poly->coeffs);
    if (poly_cpy == NULL) {
        return NULL; //flag already set by alex_make_poly()
    }

    alex_set_flag(ALEX_OK_FLAG);
    return poly_cpy;
}
