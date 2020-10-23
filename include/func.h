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
 * @file func.h
 * @author Lorenzo Calza
 * @date 22 Oct 2020
 * @brief Header file containing the declarations of function types
 *
 * This header contains the `typedef` statements which define shorthand types
 * for `double` functions for later convenience, as well as the type @ref alex_range,
 * which is used by several other components of this library.
 *
 * **Notes**
 *
 * Chances are, that if you are using other components of the library which interact
 * with types defined in this file, you may not need to `#include` this header since
 * other headers such as @ref diff.h, @ref integrate.h and @ref poly.h already
 * `#include` it.
 */

#ifndef _ALEX_FUNC_H
/**
 * @brief Include guard for this file
 */
#define _ALEX_FUNC_H

/**
 * @brief Represents a real interval
 *
 * The given struct is used to store and pass arguments to the integration routines
 * declared in this header. As such, since integrals do not account for the mathematical
 * distinction between the continuous integrals \f$(a,b)\f$ (open) and \f$[a,b]\f$
 * (closed) as well as other combinations of semi-open intervals, this struct is
 * used to represent all of them.
 *
 * **Notes**
 * - Do **not** create a @ref alex_range struct object yourself!
 *   Use @ref alex_make_range() instead. This function ensures that the fields
 *   `min`, `max` contain legal values (as in `min` <= `max`). If this is
 *   not the point, the @ref alex_range will not be created and the flag
 *   @ref ALEX_INV_RANGE_FLAG is set.
 * - Any @ref alex_range object pointer returned by the allocation function
 *   @ref alex_make_range() should be **freed** manually (as in call to `free(...)`) after its
 *   lifespan has exceeded its usefulness.
 *
 * @see alex_make_range(), alex_range_abs()
 */
typedef struct {
    /**
     * Start of the interval
     */
    double min;
    /**
     * End of the interval
     */
    double max;
} alex_range;

/**
 * @brief Constructs a range struct and returns a pointer to it
 *
 * This function calls `malloc`, as such that the returned pointer must be freed
 * after its usefulness has passed.
 *
 * If `min` > `max` this fails and returns NULL. In this case, the value returned
 * by alex_get_flag() is set to @ref ALEX_INV_RANGE_FLAG.
 *
 * @param min the starting value
 * @param max the ending value
 *
 * @returns the range struct
 * @see alex_range_abs(), alex_range
 */
alex_range *alex_make_range(double min, double max);

/**
 * @brief Returns the interval width
 *
 * This function returns the difference `max - min`, aka. the interval width.
 *
 * **Notes**
 *
 * This function does not set any flags
 *
 * @returns the interval width
 * @see alex_make_range(), alex_range
 */
double alex_range_abs(alex_range *range);

/**
 * @brief Typedef for a function taking a double and returning a double
 *
 * Represents a real function \f$f:\mathbb{R}\rightarrow\mathbb{R}\f$.
 *
 * @see alex_func_2d(), alex_func_3d(), alex_func_nd()
 */
typedef double (*alex_func_1d)(double);

/**
 * @brief Typedef for a function taking two doubles and returning a double
 *
 * Represents a real function \f$f:\mathbb{R}^2\rightarrow\mathbb{R}\f$.
 * @see alex_func_1d(), alex_func_3d(), alex_func_nd()
 */
typedef double (*alex_func_2d)(double, double);

/**
 * @brief Typedef for a function taking three doubles and returning a double
 *
 * Represents a real function \f$f:\mathbb{R}^3\rightarrow\mathbb{R}\f$.
 * @see alex_func_1d(), alex_func_2d(), alex_func_nd()
 */
typedef double (*alex_func_3d)(double, double, double);

/**
 * @brief Typedef for a function taking `n` doubles and returning a double
 *
 * Represents a real function \f$f:\mathbb{R}^n\rightarrow\mathbb{R}\f$.
 *
 * **Notes**
 * - The array `v` have ~~exactly~~ _at least_ `n` entries.
 * - More than that, and all those after `v[n-1]`
 *   are ignored, less than that and undefined behavior (segmentation fault and/or memory corruption),
 *   will occur upon calling any routine
 *   which takes an arg of type @ref alex_func_nd and a respective array `double[]`.
 *
 * @param n the dimension of the domain
 * @param v `n`-dimensional array containing the values of the `n` variables
 *
 * @see alex_func_1d(), alex_func_2d(), alex_func_3d()
 */
typedef double (*alex_func_nd)(int n, double v[]);

#endif
