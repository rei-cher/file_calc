/** @file calc_operations.h
 *
 * @brief Definition of all functions for arithmetical operations
 *
 */

#ifndef CALC_OPERATIONS_H
#define CALC_OPERATIONS_H

#include <stdint.h>
#include "calc_status.h"

calc_status_t add(int32_t f_num, int32_t s_num, int32_t * result);
calc_status_t subtract(int32_t f_num, int32_t s_num, int32_t * result);
calc_status_t multiply(int32_t f_num, int32_t s_num, int32_t * result);
calc_status_t divide(int32_t f_num, int32_t s_num, int32_t * result);
calc_status_t modulo(int32_t f_num, int32_t s_num, int32_t * result);

#endif

/*** end of the file ***/
