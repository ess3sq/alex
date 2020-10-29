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
 * @file flags.h
 * @author Lorenzo Calza
 * @date 21 Oct 2020
 * @brief Header file containing the flags and flag access routines for the integration library
 *
 * Flags are the way the library informs the user on the status success or failure and its potential
 * reason. ALl available flags are declared as macros in this header file.
 *
 * **Notes**
 * - Please refrain from setting the flag yourself.
 * - Please keep in mind that the current flag is updated every time a routine which is part of
 *   the ALEX library is called. As such, if you intend to check the flag set by a routine,
 *   make sure you either store it away in a second variable or check its value immediately before
 *   proceeding to further ALEX function calls.
 * - The functions which do not set any flags are those that perform no computations and do not
 *   modify the internal state of the framework. Usually their documentation contains a note about
 *   them not setting any flags
 *
 * **Flag index**
 *
 * Flags are typically positive integers with 3 digits, ie. between `100` and `999`, with the
 * exception of the default success flag @ref ALEX_OK_FLAG, which is defined as `0`.
 *
 * The first digit is indicative of the portion of the library which issues the flag:
 * - `0` ~ OK (default, all header files)
 * - `1` ~ internal error (utility, all header files)
 * - `2` ~ @ref linalg.h and @ref algebra.h
 * - `3` ~ @ref optimize.h
 * - `4` ~ @ref poly.h and @ref trig.h
 * - `5` ~ @ref func.h, @ref integrate.h and @ref cintegrate.h
 * - `6` ~ @ref diff.h and @ref cdiff.h
 * - `7` ~ @ref bignum.h
 * - `8` ~ @ref callback.h
 * - `9` ~ @ref logic.h
 */

#ifndef _ALEX_FLAGS_H
/**
 * @brief Include guard for this file
 */
#define _ALEX_FLAGS_H

/**
 * @brief Info flag indicating that all is well (status: OK) */
#define ALEX_OK_FLAG 0
/**
 * @brief Info flag indicating that dynamic allocation failed (see errno code for more information)
 */
#define ALEX_BAD_ALLOC_FLAG 101
/**
 * @brief Info flag indicating that a function was called with wrong args
 */
#define ALEX_INV_PARAM_FLAG 102
/**
 * @brief Info flag indicating that an algebraic operation was attempted on an illegal argument set (ie. 0 division)
 */
#define ALEX_ALG_INV_OP_FLAG 201
/**
 * @brief Info flag indicating that an operation was attempted with the coefficient's `index` argument greater
 * than the degree of the polynomial
 */
#define ALEX_POLY_INDEX_GT_DEG_FLAG 401
/**
 * @brief Infor flag indicating an overflow of the factorial value
 */
#define ALEX_FACT_OVERFLOW_FLAG 501
/**
 * @brief Info flag indicating that the creation of a range struct failed because of the args supplied
 */
#define ALEX_INV_RANGE_FLAG 506
/**
 * @brief Info flag indicating a call to @ref alex_set_dx() with a negative argument
 */
#define ALEX_NEG_DX 601

/**
 * @brief Returns the value of the flag which is currently set
 *
 * @return the current flag
 *
 * @see alex_set_flag()
 */
int alex_get_flag(void);

/**
 * @brief Sets the value of the flag
 *
 * This function should not be used externally because flags should only be set by routines
 * internal to ALEX.
 *
 * This value is originally initialized to @ref ALEX_OK_FLAG.
 *
 * @param flag the new flag
 *
 * @see alex_get_flag()
 */
void alex_set_flag(int flag);

#endif