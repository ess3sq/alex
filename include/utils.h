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
 * @file utils.h
 * @author Lorenzo Calza
 * @date 21 Oct 2020
 * @brief Header file containing the declarations for utility functions
 *
 * **Notes**
 * - Read the docs carefully before using any of these.
 * - These functions are intended for internal use and may be designed in such
 *   a way that would cause the program to fail if they are used for other purposes
 * - They were added because the implementation of the ALEX C Library makes use of them.
 *   It is possible that they be released as a proper stand-alone library in the future,
 *   if this header gets large and useful enough to warrant it.
 */

#include <stddef.h>

#ifndef _ALEX_UTILS_H
/**
 * @brief Include guard for this file
 */
#define _ALEX_UTILS_H

/**
 * @brief Macro that switches the values of two integer variables.
 */
#define alex_swap_int(m,n) {int tmp_swap_var = m; m = n; n = tmp_swap_var;}

/**
 * @brief Macro that switches the values of two variables of any type.
 *
 * The only limitation is that their type be the same and be specified
 * as the `type` variable. Of course, if pointers are passed, only
 * the pointer values are swapped, not the actual content they point at.
 */
#define alex_swap(m,n,type) {type tmp_swap_var = m; m = n; n = tmp_swap_var;}

/**
 * @brief Clears chunk of memory (ie. sets all bytes to 0)
 *
 * This function will overwrite the block starting at the location at which `ptr`
 * points to, and ending at `ptr + size`.
 *
 * This is equivalent to
 *
 * `alex_mset(ptr, size, 0);`
 *
 * @param ptr the pointer to the chunk of memory
 * @param size how many bytes should be cleared
 */
void alex_mclear(void *ptr, size_t size);

/**
 * @brief Initializes chunk of memory (ie. sets all bytes to a chosen value)
 *
 * This function will overwrite the block starting at the location at which `ptr`
 * points to, and ending at `ptr + size`.
 *
 * A shorthand form for
 *
 * `alex_mset(ptr, size, 0);`
 *
 * is provided by the function
 *
 * `alex_mclear(ptr, size);`
 *
 * @param ptr the pointer to the chunk of memory
 * @param size how many bytes should be cleared
 * @param val the value each byte should be set to
 */
void alex_mset(void *ptr, size_t size, char val);

#endif