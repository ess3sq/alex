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
 * @file poly.h
 * @author Lorenzo Calza
 * @date 22 Oct 2020
 * @brief Header file containing the declarations for polynomial utilities
 *
 * `n`-dimensional polynomials as well as operations on polynomial spaces are declared in this header file.
 */

#include "diff.h"
#include "func.h"

#ifndef _ALEX_POLY_H
/**
 * @brief Include guard for this file
 */
#define _ALEX_POLY_H

/**
 * @brief Represents a polynomial function of variable degree
 *
 * This struct object represents a polynomial of degree `deg` and
 * coefficients `coeffs[k]`, where the index `k` goes from `0` to `deg`.
 * This means, that `coeffs` must contain ~~exactly~~ _at least_
 * `deg + 1` doubles.
 *
 * From an implementation point of view, if the mathematical definition
 * of a polynomial of degree \f$n \geq 0\f$ is
 *
 * \f$P_n(x) = \sum_{k=0}^n c_kx^k\f$, where \f$c_k\in \mathbb{R}\f$ for
 * \f$k \in \{0,...,n\}\f$,
 *
 * such that if we interpret the index `k` as the summation variable \f$k\f$,
 * the real coeffiecient \f$c_k\f$ is represented by the array entry `coeffs[k]`
 * of type `double`.
 *
 * Do **not** create a @ref alex_poly struct object yourself!
 * Use @ref alex_make_poly() instead. This function ensures that the fields
 * `deg`, `coeffs` contain legal values.
 *
 * Any @ref alex_poly object pointer returned by the allocation function
 * @ref alex_make_poly() should be **freed** by calling @ref alex_free_poly() after
 * lifespan has exceeded its usefulness.
 *
 * @see alex_make_poly(), alex_free_poly(), alex_poly_deg(), alex_poly_coeff()
 */
typedef struct {
    /**
     * @brief The degree of the polynomial
     */
    unsigned int deg;
    /**
     * @brief The array containing the coefficients
     */
    double *coeffs;
} alex_poly;

/**
 * @brief Constructs a poly struct and returns a pointer to it
 *
 * This function calls `malloc` and `calloc`, as such that the returned pointer must be freed
 * after its usefulness has passed. Do **not** use `free(alex_poly *)`, but instead
 * see @ref alex_free_poly().
 *
 * If the size of `coeffs` is less than `deg` this function fails and causes undefined behaviour
 * due to out-of-bounds access (likely segmentation fault or use of garbage values).
 *
 * **Notes**
 *
 * The contents of the argument `coeffs` are copied over. As such, if the original version
 * does not serve any other purpose, it should be freed if it was dynamically allocated.
 *
 * @param deg the degree of the polynomial
 * @param coeffs the array containing the coefficients
 *
 * @returns the poly struct
 * @see alex_free_poly(), alex_poly_deg(), alex_poly_coeff(), alex_poly
 */
alex_poly *alex_make_poly(unsigned int deg, double coeffs[]);

/**
 * @brief Frees the memory occupied by this struct
 *
 * This function manages the `free()` calls required to deallocate the space
 * occupied by the struct itself and its potential fields.
 *
 * This function should always be used after the @ref alex_poly has survived past
 * its useful time in order to avoid unnecessary memory leaks.
 *
 * **Notes**
 * - Please do not call `free(alex_poly*)` yourself as a part of the struct's fields must
 *   be freed as well.
 * - This function is intended to manage the calls to `free()` for @ref alex_poly
 *   objects constructed with @ref alex_make_poly().
 * - This function will call `free()` blindly without checking whether `poly` is `NULL`
 *   or not eligible to calls to `free()`.
 *
 * @param poly pointer to the poly to be freed
 * @see alex_free_poly(), alex_poly
 */
void alex_free_poly(alex_poly *poly);

/**
 * @brief Pretty print function for polynomials
 *
 * This function is effectively equivalent to @ref alex_poly_printf() with
 * the format parameter `"%g"` for coefficients:
 *
 *     alex_poly_printf(poly, dest, "%g")
 *
 * **Notes**
 * - The printed string is appended at the end of the `dest` argument
 *   (concatenated, see `strcat()`). As such, you must make sure that the
 *   `dest` buffer is large enough. If it is not, buffer overflow will occur,
 *   probably causing internal "damage".
 * - See @ref alex_poly_printf() for an example and more information.
 *
 * @param poly the polynomial to print
 * @param dest the buffer
 * @return the polynomial printed into a `char *`
 *
 * @see alex_poly_printf(), alex_poly
 */
char *alex_poly_print(alex_poly *poly, char *dest);

/**
 * @brief Pretty print function for polynomials with format specifier
 *
 * This function prints the polynomial object with a custom format specifier
 * for the coefficients. The function @ref alex_poly_print() internally
 * calls this function and passes it the format `"%g"`.
 *
 * Any format string which is acceptable to display values of type `double`
 * (such as `"%f"`, `"%g"`, `"%e"`...), including precision specifiers
 * (ie. `"%.10f"`).
 *
 * **Example**
 *
 * If the format `"%g"` is chosen (see @ref alex_poly_print()) for the
 * polynomial with coefficients `{1., 2., 3., 4.}`, the print-out will be:
 *
 *     + 1x^0 + 2x^1 + 3x^2 + 4x^3
 *
 * **Notes**
 * - The printed string is appended at the end of the `dest` argument
 *   (concatenated, see `strcat()`). As such, you must make sure that the
 *   `dest` buffer is large enough. If it is not, buffer overflow will occur,
 *   probably causing internal "damage".
 *
 * @param poly the polynomial to print
 * @param dest destination buffer
 * @param format the format specifier for the coefficients
 * @return the polynomial printed into a `char *`
 *
 * @see alex_poly_print(), alex_poly
 */
char *alex_poly_printf(alex_poly *poly, char *dest, const char *format);

/**
 * @brief The degree of the polynomial
 *
 * Returns the degree of the polynomial, aka. the @ref alex_poly.deg field.
 *
 * @param poly the polynomial
 * @return the degree
 *
 * @see alex_poly_lead(), alex_poly_trail(), alex_poly_coeff(), alex_poly
 */
unsigned int alex_poly_deg(alex_poly *poly);

/**
 * @brief Returns the leading coefficient
 *
 * A polynomial's leading coefficient is the coefficient
 * of it's highest order term, as in \f$c_n\f$ for a polynomial
 * of degree \f$n\f$ according to our notation (see @ref alex_poly).
 *
 * This is equivalent to
 *
 *     alex_poly_coeff(poly, alex_poly_deg(poly))
 *
 * @param poly the polynomial
 * @return the leading coefficient
 *
 * @see alex_poly_deg(), alex_poly_trail(), alex_poly_coeff(), alex_poly
 */
double alex_poly_lead(alex_poly *poly);

/**
 * @brief Returns the trailing coefficient
 *
 * A polynomial's trailing coefficient is the constant coefficient,
 * as in \f$c_0\f$ for a polynomial of degree \f$n\f$ according to our
 * notation (see documentation for @ref alex_poly).
 *
 * This is equivalent to
 *
 *     alex_poly_coeff(poly, 0)
 *
 * @param poly the polynomial
 * @return the trailing coefficient
 *
 * @see alex_poly_deg(), alex_poly_lead(), alex_poly_coeff(), alex_poly
 */
double alex_poly_trail(alex_poly *poly);


/**
 * @brief Provides index-access to the polynomials coefficients
 *
 * Returns the coefficient at `index` (see @ref alex_poly for more information).
 * `index` should **not** be greater than the degree of the polynomial (@ref alex_poly.deg).
 * If it is, this function will be returning the leading coefficient (@ref alex_poly_lead()) and set @ref alex_get_flag()
 * to @ref ALEX_POLY_INDEX_GT_DEG.
 *
 * @param poly the polynomial
 * @param index the index of the coefficient
 *
 * @return the coefficient corresponding to `index`
 *
 * @see alex_poly_deg(), alex_poly_lead(), alex_poly_trail(), alex_poly
 */
double alex_poly_coeff(alex_poly *poly, unsigned int index);

/**
 * @brief Evaluates the polynomial function at a given point
 *
 * This evaluates the polynomial function value at the location `x`.
 *
 * @param poly the polynomial
 * @param x the location at which the function should be evalued
 * @return the function value
 *
 * @see alex_poly_coeff(), alex_poly
 */
double alex_poly_eval(alex_poly *poly, double x);

/**
 * @brief Determines the derivative of the polynomial function
 *
 * This function simply takes the polynomial in its representation
 *
 * \f$p(x)=\sum_{k=0}^n a_kx^k\f$
 *
 * and applies the differentiation formula for polynomials
 *
 * \f$p(x)=\sum_{k=0}^{n-1} a_{k+1}x^k\f$.
 *
 * The coefficients of the resulting function are then wrapped within a new @ref alex_poly object,
 * and this object is returned.
 *
 * @param poly the polynomial to differentiate
 * @return the first derivative
 *
 * @see alex_poly_integ(), alex_poly
 */
alex_poly *alex_poly_diff(alex_poly *poly);

/**
 * @brief Determines the antiderivative (indefinite integral) of the polynomial function
 *
 * This function simply takes the polynomial in its representation
 *
 * \f$p(x)=\sum_{k=0}^n a_kx^k\f$
 *
 * and applies the differentiation formula for polynomials
 *
 * \f$p(x)= C + \sum_{k=0}^{n+1} a_k \frac{x^{k+1}}{k+1}\f$.
 *
 * The (real) integration constant \f$C\f$ is arbitrary and corresponds to the argument `double c`.
 *
 * The coefficients of the resulting function are then wrapped within a new @ref alex_poly object,
 * and this object is returned.
 *
 * @param poly the polynomial to integrate
 * @param c the integration constant
 * @return the antiderivative
 *
 * @see alex_poly_diff(), alex_poly
 */
alex_poly *alex_poly_integ(alex_poly *poly, double c);

/**
 * @brief Determines the definite integral of the polynomial function
 * over a given range
 *
 * This function simply takes the polynomial in its representation
 *
 * \f$p(x)=\sum_{k=0}^n a_kx^k\f$
 *
 * and integrates it over the given range (@ref alex_range).
 *
 * This function is effectively equivalent to
 *
 *     double integral;
 *     alex_poly *antid;
 *
 *     antid = alex_poly_integ(poly, 0.);
 *     integral = alex_poly_eval(antid, range->max) - alex_poly_eval(antid, range->min)
 *
 *     alex_free_poly(antid);
 *
 * @param poly the polynomial to integrate
 * @param range the integration interval
 * @return the definite integral
 *
 * @see alex_poly_integ(), alex_poly
 */
double alex_poly_integ_range(alex_poly *poly, alex_range *range);

/**
 * @deprecated See the rest of the documentation for why this is deprecated
 *
 * @brief Returns @ref alex_func_1d object representing this polynomial function.
 *
 * This function will return the required function pointer in order for it to
 * be passed to other routines of this library.
 *
 * Theoretically, due to the absence of lambdas in C, this function will always return
 * a pointer to the same function object of type @ref alex_func_1d. The way this is implemented
 * is by setting an `static` variable of type @ref alex_poly* internal to the implementation to
 * the argument. That means that if you perform two subsequent calls to this function, the value
 * will be overwritten by the second call, meaning that the object returned by the first call
 * will be working exactly like the second.
 *
 * For this reason, this implementation is sub-optimal and **deprecated**. If you require a more stable
 * way to construct @ref alex_func_1d objects, define a function yourself in this way:
 *
 *     alex_poly *poly;
 *     // ... call to alex_make_poly(...) with the desired arguments
 *
 *     double my_poly_func(double x) {
 *         return alex_poly_eval(poly, x);
 *     }
 *
 *     //...
 *     alex_func_1d f = &my_poly_func;
 *
 *
 * @param poly the struct representing the polynomial
 * @return the @ref alex_func_1d object
 *
 * @see alex_func_1d, alex_poly
 */
alex_func_1d alex_poly_func(alex_poly *poly);

/**
 * @brief Indicates whether or not this polynomial is constant
 *
 * A constant polynomial is a polynomial of degree \f$0\f$, as in \f$P(x)=C\f$ for
 * \f$C \in \mathbb{R}\f$.
 *
 * This is equivalent to
 *
 *     alex_poly_deg(poly) == 0
 *
 * @param poly the polynomial
 * @return ´0´ if the polynomial is not constant, non-zero otherwise
 *
 * @see alex_poly_deg(), alex_poly_trail(), alex_poly_coeff(), alex_poly()
 */
int alex_poly_isconst(alex_poly *poly);

/**
 * @brief Compares two polynomials by their coefficients
 *
 * This function has the following output cases:
 * - \f$0\f$ - `p` and `q` have the same degree and all coefficients are equal
 * - \f$\mathrm{deg}(p) + 1 - h\f$ - `p` and `q` have the same length and \f$ c_i(p) = c_i(q)\:\forall i \in \{0,1,...,h\}\f$
 * - \f$\mathrm{deg}(p) - \mathrm{deg}(p)\f$  - `p` and `q` have different degrees
 *
 * @param p first polynomial
 * @param q second polynomial
 * @return `0` if `p` and `q` have the same coefficients
 *
 * @see alex_poly_coeff(), alex_poly_deg(), alex_poly()
 */
int alex_poly_cmp(alex_poly *p, alex_poly *q);

/**
 * @brief Duplicates the polynomial
 *
 * This function copies over the memory of the argument polynomial into a new object and returns a pointer to it.
 *
 * @param poly the original object
 * @return the copy of the object
 *
 * @see alex_make_poly(), alex_poly
 */
alex_poly *alex_poly_cpy(alex_poly *poly);

#endif