/** @file bit_operations.h 
 *
 * @brief Definition of all functions for the bitwise operations
 *
 */

#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H

#include <stdint.h>
#include "calc_status.h"

/**
 * @brief Bit shifting left first number by the number of bits (second number)
 *
 * @param f_num
 * @param s_num
 * @param p_result
 *
 * @return cacl_status_t
 */
calc_status_t l_shift(uint64_t f_num, uint64_t s_num, uint64_t * p_result);

/**
 * @brief Bit shifting right first number by the number of bits (second number)
 *
 * @param f_num
 * @param s_num
 * @param p_result
 *
 * @return cacl_status_t
 */
calc_status_t r_shift(uint64_t f_num, uint64_t s_num, uint64_t * p_result);

/**
 * @brief AND operation
 * 		  Compares each bit at the same position
 * 		  If both corresponding bits are set, the result will be 1
 *
 * @param f_num
 * @param s_num
 * @param p_result
 *
 * @return cacl_status_t
 */
calc_status_t op_and(uint64_t f_num, uint64_t s_num, uint64_t * p_result);

/**
 * @brief OR operation
 * 		  Compares each bit at the same position
 * 		  If any corresponding bits are set, result will be 1
 *
 * @param f_num
 * @param s_num
 * @param p_result
 *
 * @return cacl_status_t
 */
calc_status_t op_or(uint64_t f_num, uint64_t s_num, uint64_t * p_result);

/**
 * @brief XOR operation
 * 		  Compares each bit at the same position
 * 		  If the corresponding bits are different, result will be 1
 *
 * @param f_num
 * @param s_num
 * @param p_result
 *
 * @return calc_status_t
 */
calc_status_t op_xor(uint64_t f_num, uint64_t s_num, uint64_t * p_result);

/**
 * @brief Rotates bits to the left off one end of a value and wraps around
 * 		  to the other end
 *
 * @param f_num
 * @param s_num
 * @param p_result
 *
 * @return calc_status_t
 */
calc_status_t l_rotate(uint64_t f_num, uint64_t s_num, uint64_t * p_result);

/**
 * @brief Rotates bits to the right off one end of a value and wraps around
 * 		  to the other end
 *
 * @param f_num
 * @param s_num
 * @param p_result
 *
 * @return calc_status_t
 */
calc_status_t r_rotate(uint64_t f_num, uint64_t s_num, uint64_t * p_result);

#endif

/*** end of the file ***/
