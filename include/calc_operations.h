/** @file calc_operations.h
 *
 * @brief Definition of all functions for arithmetical operations
 *
 */

#ifndef CALC_OPERATIONS_H
#define CALC_OPERATIONS_H

#include <stdint.h>
#include "calc_status.h"

/**
 * @brief Adds two numbers
 *
 * @param f_num
 * @param s_num
 * @param result
 *
 * @return calc_status_t
 */
calc_status_t add(int64_t f_num, int64_t s_num, int64_t * result);

/**
 * @brief Subtracts second number from the first number
 *
 * @param f_num
 * @param s_num
 * @param result
 *
 * @return cacl_status_t
 */
calc_status_t subtract(int64_t f_num, int64_t s_num, int64_t * result);

/**
 * @brief Multiplies numbers
 *
 * @param f_num
 * @param s_num
 * @param result
 *
 * @return calc_status_t
 */
calc_status_t multiply(int64_t f_num, int64_t s_num, int64_t * result);

/**
 * @brief Divides first number by second
 *
 * @param f_num
 * @param s_num
 * @param result
 *
 * @return calc_status_t
 */
calc_status_t divide(int64_t f_num, int64_t s_num, int64_t * result);

/**
 * @brief Modulos first number by second
 *
 * @param f_num
 * @param s_num
 * @param result
 *
 * @return calc_status_t
 */
calc_status_t modulo(int64_t f_num, int64_t s_num, int64_t * result);

#endif

/*** end of the file ***/
