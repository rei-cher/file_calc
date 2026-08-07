/** @file calc_operations.h
 *
 * @brief Definition of all functions for arithmetical operations
 *
 */

#ifndef CALC_OPERATIONS_H
#define CALC_OPERATIONS_H

#include <stdint.h>
#include "calc_status.h"

calc_status_t add(int64_t f_num, int64_t s_num, int64_t * result);
calc_status_t subtract(int64_t f_num, int64_t s_num, int64_t * result);
calc_status_t multiply(int64_t f_num, int64_t s_num, int64_t * result);
calc_status_t divide(int64_t f_num, int64_t s_num, int64_t * result);
calc_status_t modulo(int64_t f_num, int64_t s_num, int64_t * result);

#endif

/*** end of the file ***/
