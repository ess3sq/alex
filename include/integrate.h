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

#include "func.h"

/**
 * @file integrate.h
 * @author Lorenzo Calza
 * @date 21 Oct 2020
 * @brief Header file containing the declarations for the integration library
 *
 * One and multi-dimensional methods for the integration of real functions
 * are declared in this header file.
 *
 * **Notes**
 * - See the article Wikipedia article [Numerical integration](https://en.wikipedia.org/wiki/Numerical_integration)
 *   for information on the mathematical algorithms and rules imüplemented in this library.
 */

#ifndef _ALEX_INTEGRATE_H
/**
 * @brief Include guard for this file
 */
#define _ALEX_INTEGRATE_H

/**
 * @brief Default number of bins `nbins`.
 *
 * This value is way lower than it should be for appropriate results. It is recommended that you
 * experiment with your system and your case (function type and [range](@ref alex_range)) in order to
 * find the right value for `nbins`.
 *
 * @see alex_set_bins(), alex_get_bins(), alex_integrate_bins()
 */
#define ALEX_DEFAULT_NBINS 1000ul

/**
 * @brief Sets the number of bins to be used in calls to bin integration functions
 *
 * @param n the number of bins
 * @see alex_get_bins(), alex_integrate_bins()
 */
void alex_set_bins(unsigned long n);

/**
 * @brief Returns the number of bins to be used in calls to bin integration functions
 *
 * @returns the number of bins
 * @see alex_set_bins(), alex_integrate_bins()
 */
unsigned long alex_get_bins(void);

/**
 * @brief Performs one-dimensional integration of a given real function
 *
 * This function performs the one-dimensional integration of a give function \f$f\f$
 * in the given range, ie. if `a = range->min` and `b = range->max` the return
 * value will be a discretization of the Riemann integral.
 *
 * \f$ I_f(a,b)=\int_a^b f(x)\mathrm dx \f$.
 *
 * The discretization deconstructs the continuous integral \f$[a,b]\f$ into \f$n\f$ smaller
 * intervals of the width \f$ \delta = \frac{b-a}n\f$, ie. \f$ W_i=[x_i, x_i + \delta] \f$,
 * where \f$ x_i \in X\setminus\{b\}\f$,
 * \f$X = \{a, a+\delta, a+2\delta,...,b\} \f$, and \f$ a + m \delta = b\f$. As such,
 * this function computes the value
 *
 * \f$ J_f(a,b) = \sum_{x\in X} x\cdot f(x)\f$
 *
 * The number \f$m\f$ is represented by the variable `nbins`, which can be accessed with its
 * getters and setters (see below).
 * The step \f$\delta\f$ is inversely proportional to \f$m\f$, which means that theoretically, it
 * makes sense to set this number as high as possible. Nevertheless, benchmarking results
 * show that if it is set too high, the step \f$\delta\f$ becomes too small and higher computational
 * errors occur due to the operating system's limited precision with extremely small floating
 * point values.
 *
 * On our system, we find that this function yields the best possible results when integrating a
 * standard distribution function (gaussian with \f$\sigma = 1\f$ and \f$\mu = 0\f$) if `nbins`
 * is set to a value of the order of \f$10000000\f$ (10 millions).
 *
 * @param f the @ref alex_func_1d() representing the integrand \f$f:\mathbb{R}\rightarrow\mathbb{R}\f$
 * @param range the integration interval
 *
 * @returns the bins integral
 * @see alex_func_1d(), alex_get_bins(), alex_set_bins(), alex_make_range(), alex_range
 */
double alex_integrate_bins(alex_func_1d f, alex_range *range);
//double alex_integrate_bins2D(alex_func2d f, alex_range *rangeX, alex_func1d callback, *rangeY);
/*double alex_integrate_bins3D(alex_func1d f, alex_range *range);
double alex_integrate_bins(alex_func1d f, alex_range *range);*/

/**
 * @deprecated Yields sub-optimal results (see @ref alex_integrate_trap() for a better approximation)
 *
 * This function performs an approximation of the one-dimensional integral of a given function \f$f\f$
 * in the given range, ie. if `a = range->min` and `b = range->max`.
 *
 * This approximation uses the rectangle rule (interpolation method), ie.
 *
 * \f$ I_f(a,b)=\int_a^b f(x)\mathrm dx \approx (b-a)\cdot f\left(\frac{a+b}{2}\right) \f$
 *
 * without extension, and
 *
 * \f$ I_f(a,b)=\int_a^b f(x)\mathrm dx \approx (b-a)\cdot f\left(\frac{a}{2} + \sum_{k=1}^{n-1} \left(a+k\frac{b-a}{n} \right) + \frac{b}{2} \right) \f$
 *
 * with the composite rule.
 *
 * @param f the @ref alex_func_1d() representing the integrand \f$f:\mathbb{R}\rightarrow\mathbb{R}\f$
 * @param range the integration interval
 * @param subintervals the number of subintervals for the compound rule. To use it without
 * extension, pass `subintervals = 0` (not recommended)
 *
 * @returns the approximated integral
 *
 * @see alex_func_1d(), alex_integrate_trap(), alex_integrate_bins(), alex_make_range(), alex_range
 */
double alex_integrate_rect(alex_func_1d f, alex_range *range, int subintervals);

/**
 * @brief Performs approximation of one-dimensional integration of a given real function
 *
 * This function performs an approximation of the one-dimensional integral of a given function \f$f\f$
 * in the given range, ie. if `a = range->min` and `b = range->max`.
 *
 * This approximation uses the trapezoidal rule (interpolation method), ie.
 *
 * \f$ I_f(a,b)=\int_a^b f(x)\mathrm dx \approx (b-a)\cdot (\frac{f(a)+f(b)}{2}) \f$
 *
 * without extension, and
 *
 * \f$ I_f(a,b)=\int_a^b f(x)\mathrm dx \approx (b-a)\cdot (\frac{f(a)}{2} + \sum_{k=1}^{n-1}\left( f \left( a+k\frac{b-a}{n} \right) \right) + \frac{f(b)}{2}) \f$
 *
 * with the composite rule.
 *
 * @param f the @ref alex_func_1d() representing the integrand \f$f:\mathbb{R}\rightarrow\mathbb{R}\f$
 * @param range the integration interval
 * @param subintervals the number of subintervals for the compound rule. To use it without
 * extension, pass `subintervals = 0` (not recommended)
 *
 * @returns the approximated integral
 *
 * @see alex_func_1d(), alex_integrate_rect(), alex_integrate_bins(), alex_make_range(), alex_range
 */
double alex_integrate_trap(alex_func_1d f, alex_range *range, int subintervals);

#endif