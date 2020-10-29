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
 * @file algebra.h
 * @author Lorenzo Calza
 * @date 22 Oct 2020
 * @brief Header file containing the declarations for algebraic and numeric utilities, such as GCD and LCM computation
 *
 */

#ifndef _ALEX_ALGEBRA_H
/**
 * @brief Include guard for this file
 */
#define _ALEX_ALGEBRA_H

/**
 * @brief Computes the greatest common divisor (GCD) for two given integers.
 *
 * The integers are required to be unsigned for practicality reasons.
 * Furthermore, while combinations of single \f$0\f$ values are acceptable, ie.
 * \f$\mathrm{gcd}(0,n)=n\f$ and \f$\mathrm{gcd}(m,0)=m\f$ (since any number divides
 * \f$0\f$ evenly). Nevertheless, the GCD of the pair \f$(0,0)\f$ is not defined because
 * any number divides evenly by \f$0\f$, thus making it impossible to determine the
 * largest of them.
 *
 * If `alex_gcd(0,0)` is called, `0` is returned, however this is not the actual result
 * since the GCD of two zeros is undefined. As such, the flag @ref ALEX_ALG_INV_OP_FLAG is
 * set to indicate that this is an invalid operation.
 *
 * @param m an integer
 * @param n an integer
 * @return their GCD
 *
 * @see alex_lcm()
 */
unsigned int alex_gcd(unsigned int m, unsigned int n);

/**
 * @brief Computes the least common multiple (LCM) for two given integers.
 *
 * The integers are required to be unsigned for practicality reasons.
 * Apart from that, all integer pairs are acceptable input, including combinations
 * where either or both integers are `0`.
 *
 * As such, the flag @ref ALEX_OK_FLAG is
 * set to indicate that this is an invalid operation.
 *
 * @param m an integer
 * @param n an integer
 * @return their LCM
 *
 * @see alex_gcd()
 */
unsigned int alex_lcm(unsigned int m, unsigned int n);

#endif
