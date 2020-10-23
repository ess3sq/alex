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

/**
 * @file diff.h
 * @author Lorenzo Calza
 * @date 22 Oct 2020
 * @brief Header file containing the declarations for general calculus utilities
 *
 * This header contains both differential calculus routines as well as general numeric
 * calculus operations.
 */

#include "func.h"

#ifndef _ALEX_DIFF_H
/**
 * @brief Include guard for this file
 */
#define _ALEX_DIFF_H

#define ALEX_DEFAULT_DX 1e-9

/**
 * @brief Uses the secant method to determine a root of the function
 *
 * This function uses an iterative algorithm (the secant method, see
 * [Wikipedia](https://en.wikipedia.org/wiki/Secant_method) to determine a root
 * which lies within a given interval.
 *
 * The algorithm assumes that there is a root within the given range. The smaller the range,
 * the fewer iterations are required to determine a reasonable approximation. Similarly,
 * more iterations yield a more precise result at the cost of further computational time.
 *
 * **Example**
 *
 * Let us consider \f$f = x^2 - 612\f$. We can search for a root within the interval \f$[10,30}\f$:
 *
 *     alex_range *r = alex_make_range(10, 30);
 *     double approx = alex_secant_method(&test_secant, r, 5);
 *     printf("Root of test func: %.10f\n", approx);
 *     free(r);
 *
 * This will output
 *
 *     Root of test func: 24.73863375
 *
 * to `stdout`. As it turns out, this is a surprisingly good approximation, considering it took us only 5
 * iterations, making the analytical (exact) solution \f$x_{\pm} = \pm 6 \sqrt 7\f$ aka.
 * \f$x_+= 6\sqrt{17}\approx 24.738633753709...\f$ quite close. If we were to add more iterations, possibly
 * hundreds, we could get even preciser results at almost no cost, considering a regular computer's
 * computational power.
 *
 * **Notes**
 *
 * Results will vary from system to system. The above test was conducted on a Windows 10 machine, x86, 16GB RAM.
 * We recommend that you investigate the optimal parameters (`range`, `iterations`) for your case before
 * accepting a result.
 *
 * @param f the function \f$f:\mathbb{R}\rightarrow\mathbb{R}\f$
 * @param range the interval which we must search
 * @param iterations number of iterations
 * @return the approximated root
 */
double alex_secant_method(alex_func_1d f, alex_range *range, unsigned iterations);

/**
 * @brief Computes slope of a function at a given point
 *
 * This function returns the derivative (slope) of a given function @ref alex_func_1d. If the
 * function is not continuos / smooth at the point \f$x\f$, the result may not
 * be mathematically accurate.
 *
 * @param f the function to differentiate
 * @param x where to differentiate
 * @return the slope at x
 */
double alex_diff(alex_func_1d f, double x);

/**
 * @brief Sets the `dx`-step for numeric differentiation of functions
 *
 * @param dx the `dx`-step
 * @see alex_set_dx(), alex_diff()
 */
void alex_set_dx(double dx);

/**
 * @brief Returns the `dx`-step for numeric differentiation of functions
 *
 * @returns the `dx`-step
 * @see alex_set_dx(), alex_diff()
 */
double alex_get_dx(void);

#endif
