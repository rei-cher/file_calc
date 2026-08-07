/** @file bit_operations.c
 *
 * @brief Perform bitwise operations
 *
 */

#include <stdint.h>
#include <stdio.h>
#include "calc_status.h"
#include "bit_operations.h"

#define UINT64_BIT_COUNT (64U)
#define ZERO_UNSIGNED (0U)

calc_status_t l_shift(uint64_t f_num, uint64_t s_num, uint64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;
	
	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else if (UINT64_BIT_COUNT <= s_num)
	{
		status = CALC_STATUS_INVALID_SHIFT;
	}
	else
	{
		* p_result = f_num << s_num;
	}

	return status;
}

calc_status_t r_shift(uint64_t f_num, uint64_t s_num, uint64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else if (UINT64_BIT_COUNT <= s_num)
	{
		status = CALC_STATUS_INVALID_SHIFT;
	}
	else
	{
		* p_result = f_num >> s_num;
	}

	return status;
}

calc_status_t op_and(uint64_t f_num, uint64_t s_num, uint64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else
	{
		* p_result = f_num & s_num;
	}

	return status;
}

calc_status_t op_or(uint64_t f_num, uint64_t s_num, uint64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else
	{
		* p_result = f_num | s_num;
	}

	return status;
}

calc_status_t op_xor(uint64_t f_num, uint64_t s_num, uint64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else
	{
		* p_result = f_num ^ s_num;
	}

	return status;
}

calc_status_t l_rotate(uint64_t f_num, uint64_t s_num, uint64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;
	uint64_t num_of_rotations;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else
	{
		num_of_rotations = s_num % UINT64_BIT_COUNT;

		if (ZERO_UNSIGNED == num_of_rotations)
		{
			* p_result = f_num;
		}
		else
		{
			* p_result = (f_num << num_of_rotations) |
						 (f_num >> (UINT64_BIT_COUNT - num_of_rotations));
		}
	}

	return status;
}

calc_status_t r_rotate(uint64_t f_num, uint64_t s_num, uint64_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;
	uint64_t num_of_rotations;

	if (NULL == p_result)
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else
	{
		num_of_rotations = s_num % UINT64_BIT_COUNT;

		if (ZERO_UNSIGNED == num_of_rotations)
		{
			* p_result = f_num;
		}
		else
		{
			* p_result = (f_num >> num_of_rotations) |
						 (f_num << (UINT64_BIT_COUNT - num_of_rotations));
		}
	}

	return status;
}

/*** end of the file ***/
