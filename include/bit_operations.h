/** @file bit_operations.h 
 *
 * @brief Definition of all functions for the bitwise operations
 *
 */

#ifndef BIT_OPERATIONS_H
#define BIT_OPERATIONS_H

#include <stdint.h>
#include "calc_status.h"

calc_status_t l_shift(uint64_t f_num, uint64_t s_num, uint64_t * p_result);
calc_status_t r_shift(uint64_t f_num, uint64_t s_num, uint64_t * p_result);
calc_status_t op_and(uint64_t f_num, uint64_t s_num, uint64_t * p_result);
calc_status_t op_or(uint64_t f_num, uint64_t s_num, uint64_t * p_result);
calc_status_t op_xor(uint64_t f_num, uint64_t s_num, uint64_t * p_result);
calc_status_t l_rotate(uint64_t f_num, uint64_t s_num, uint64_t * p_result);
calc_status_t r_rotate(uint64_t f_num, uint64_t s_num, uint64_t * p_result);

#endif

/*** end of the file ***/
