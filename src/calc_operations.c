/** @file calc_operations.c
 *
 * @brief Perform basic arithmetic operations
 */

#include <stdint.h>
#include <stdio.h>
#include "calc_status.h"
#include "calc_operations.h"

calc_status_t add(int64_t f_num, int64_t s_num, int64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else if (((0 < s_num) && ((INT64_MAX - s_num) < f_num)) ||
			 ((0 > s_num) && ((INT64_MIN -s_num) > f_num)))
	{
		status = CALC_STATUS_OVERFLOW;
	}
	else
	{
		* p_result = f_num + s_num;
	}

	return status;
}

calc_status_t subtract(int64_t f_num, int64_t s_num, int64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else if (((0 < s_num) && ((INT64_MIN + s_num) > f_num)) ||
		   	 ((0 > s_num) && ((INT64_MAX + s_num) < f_num)))
	{
		status = CALC_STATUS_OVERFLOW;
	}
	else
	{
		* p_result = f_num - s_num;
	}

	return status;
}

calc_status_t multiply(int64_t f_num, int64_t s_num, int64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else if (((-1 == f_num) && (INT64_MIN == s_num)) ||
			 ((-1 == s_num) && (INT64_MIN == f_num)) ||
			 ((0 < f_num) && (0 < s_num) && ((INT64_MAX / s_num) < f_num)) ||
			 ((0 < f_num) && (0 > s_num) && ((INT64_MAX / f_num) > s_num)) ||
			 ((0 > f_num) && (0 < s_num) && ((INT64_MAX / s_num) > f_num)) ||
			 ((0 > f_num) && (0 > s_num) && ((INT64_MAX / s_num) > f_num)))
	{
		status = CALC_STATUS_OVERFLOW;
	}
	else
	{
		* p_result = f_num * s_num;
	}

	return status;
}

calc_status_t divide(int64_t f_num, int64_t s_num, int64_t *p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else if (0 == s_num){
		printf("Error: can not divide by 0\n");
		status = CALC_STATUS_DIVIDE_BY_ZERO;
	}
	else if ((INT64_MIN == f_num) && (-1 == s_num)){
		status = CALC_STATUS_OVERFLOW;
	}
	else
	{
		* p_result = f_num / s_num;
	}

	return status;
}

calc_status_t modulo(int64_t f_num, int64_t s_num, int64_t *p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else if (0 == s_num){
		printf("Error: can not divide by 0\n");
		status = CALC_STATUS_DIVIDE_BY_ZERO;
	}
	else if ((INT64_MIN == f_num) && (-1 == s_num)){
		status = CALC_STATUS_OVERFLOW;
	}
	else
	{
		* p_result = f_num % s_num;
	}

	return status;
}

/*** end of the file ***/
