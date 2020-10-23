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
 */

#ifndef _ALEX_UTILS_H
/**
 * @brief Include guard for this file
 */
#define _ALEX_UTILS_H

/**
 * @brief Clears memory
 *
 * This function will overwrite the block starting at the location at which `ptr`
 * points to, and ending at `ptr + size`.
 *
 * @param ptr the pointer to the chunk of memory
 * @param size how many bytes should be cleared
 */
void alex_mclear(void *ptr, size_t size);

#endif