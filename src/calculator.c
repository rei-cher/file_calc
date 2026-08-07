/** @file calculator.c
 *
 * @brief Main program flow controls
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "bit_operations.h"
#include "calc_operations.h"
#include "calc_status.h"
#include "calculator.h"

#define FIRST_CHARACTER 0


static calc_status_t calculate_arit(operator_t operator,
								  const integer_t * p_f_integer,
								  const integer_t * p_s_integer,
								  integer_t * p_result);

static calc_status_t calculate_bit(operator_t operator,
								 const integer_t * p_f_integer,
								 const integer_t * p_s_integer,
								 integer_t * p_result);

integer_type_t get_integer_type(operator_t operator)
{
	integer_type_t integer_type = INTEGER_TYPE_SIGNED;

	switch (operator)
	{
		case OPERATOR_AND:
		case OPERATOR_OR:
		case OPERATOR_XOR:
		case OPERATOR_LEFT_SHIFT:
		case OPERATOR_LEFT_ROTATE:
		case OPERATOR_RIGHT_SHIFT:
		case OPERATOR_RIGHT_ROTATE:
			integer_type = INTEGER_TYPE_UNSIGNED;
			break;

		case OPERATOR_ADD:
		case OPERATOR_SUBTRACT:
		case OPERATOR_MULTIPLY:
		case OPERATOR_MODULO:
		case OPERATOR_DIVIDE:
		default:
			integer_type = INTEGER_TYPE_SIGNED;
			break;

	}

	return integer_type;
}

calc_status_t calculate_result(operator_t operator,
							   const integer_t * p_f_integer,
							   const integer_t * p_s_integer,
							   integer_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;
	integer_type_t result_type = INTEGER_TYPE_SIGNED;

	if ((NULL == p_f_integer) || (NULL == p_s_integer) || (NULL == p_result))
	{
		status = CALC_STATUS_NULL_POINTER;
		goto END;
	}

	if ((OPERATOR_ADD <= operator) &&
		(OPERATOR_MODULO >= operator))
	{
		status = calculate_arit(operator, p_f_integer, p_s_integer, p_result);
	}
	else if ((OPERATOR_LEFT_SHIFT <= operator) &&
			 (OPERATOR_RIGHT_ROTATE >= operator))
	{
		status = calculate_bit(operator, p_f_integer, p_s_integer, p_result);
	}
	else
	{
		status = CALC_STATUS_INVALID_OPERATOR;
	}

END:
	return status;
}

static calc_statuc calculate_arit(operator_t operator,
								  const integer_t * p_f_integer,
								  const integer_t * p_s_integer,
								  integer_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;
	integer_type_t result_type = INTEGER_TYPE_SIGNED;

	if ((NULL == p_f_integer) || 
		(NULL == p_s_integer) ||
		(NULL == p_result))
	{
		status = CALC_STATUS_NULL_POINTER;
		goto END;
	}

	switch (operator)
	{
		case OPERATOR_ADD:
			status = add (
					p_f_integer->value.signed_value,
					p_s_integer->value.signed_value,
					&p_result->value.signed_value);
			break;
	
		case OPERATOR_SUBTRACT:
			status = subtract (
					p_f_integer->value.signed_value,
					p_s_integer->value.signed_value,
					&p_result->value.signed_value);
			break;
		
		case OPERATOR_MULTIPLY:
			status = multiply (
					p_f_integer->value.signed_value,
					p_s_integer->value.signed_value,
					&p_result->value.signed_value);
			break;
			
		case OPERATOR_DIVIDE:
			status = divide (
					p_f_integer->value.signed_value,
					p_s_integer->value.signed_value,
					&p_result->value.signed_value);
			break;
			
		case OPERATOR_MODULO:
			status = modulo (
					p_f_integer->value.signed_value,
					p_s_integer->value.signed_value,
					&p_result->value.signed_value);
			break;

		default:
			status = CALC_STATUS_INVALID_OPERATOR;
			goto END;
	}
	
	if (CALC_STATUS_OK == status)
	{
		result_type = INTEGER_TYPE_SIGNED;
		p_result->type = result_type;
	}

END:
	return status;
}

static calc_statuc calculate_bit(operator_t operator,
								 const integer_t * p_f_integer,
								 const integer_t * p_s_integer,
								 integer_t * p_result)
{
	calc_status_t status = CALC_STATUS_OK;
	integer_type_t result_type = INTEGER_TYPE_SIGNED;

	if ((NULL == p_f_integer) || 
		(NULL == p_s_integer) ||
		(NULL == p_result))
	{
		status = CALC_STATUS_NULL_POINTER;
		goto END;
	}

	switch (operator)
	{
		case OPERATOR_AND:
			status = op_and (
					p_f_integer->value.unsigned_value,
					p_s_integer->value.unsigned_value,
					&p_result->value.unsigned_value);
			break;
			
		case OPERATOR_OR:
			status = op_or (
					p_f_integer->value.unsigned_value,
					p_s_integer->value.unsigned_value,
					&p_result->value.unsigned_value);
			break;
			
		case OPERATOR_XOR:
			status = op_xor (
					p_f_integer->value.unsigned_value,
					p_s_integer->value.unsigned_value,
					&p_result->value.unsigned_value);
			break;
			
		case OPERATOR_LEFT_SHIFT:
			status = l_shift (
					p_f_integer->value.unsigned_value,
					p_s_integer->value.unsigned_value,
					&p_result->value.unsigned_value);
			break;
			
		case OPERATOR_RIGHT_SHIFT:
			status = r_shift (
					p_f_integer->value.unsigned_value,
					p_s_integer->value.unsigned_value,
					&p_result->value.unsigned_value);
			break;
			
		case OPERATOR_LEFT_ROTATE:
			status = l_rotate (
					p_f_integer->value.unsigned_value,
					p_s_integer->value.unsigned_value,
					&p_result->value.unsigned_value);
			break;
		
		case OPERATOR_RIGHT_ROTATE:
			status = r_rotate (
					p_f_integer->value.unsigned_value,
					p_s_integer->value.unsigned_value,
					&p_result->value.unsigned_value);
			break;

		default:
			status = CALC_STATUS_INVALID_OPERATOR;
			goto END;
	}

	if (CALC_STATUS_OK == status)
	{
		result_type = INTEGER_TYPE_UNSIGNED;
		p_result->type = result_type;
	}

END:
	return status;
}

void print_usage(const char * p_name)
{
	printf("Incorrect supply of arguments.\n");
	printf("Usage: %s <number> <operator> <number>\n", p_name);
	printf("Arithmetic operators: + - * / %%\n");
	printf("Bitwise operators: & | ^ << >> <<< >>>\n");
}

void print_error(calc_status_t status)
{
	switch (status)
	{
		case CALC_STATUS_INVALID_OPERATOR:
			printf("Error: unsupported operator\n");
			break;

		case CALC_STATUS_INVALID_INTEGER:
		   printf("Error: invalid integer type\n");
	   	   break;

		case CALC_STATUS_INTEGER_OUT_OF_RANGE:
		   printf("Error: integer is out of the range\n");
		   break;

		case CALC_STATUS_DIVIDE_BY_ZERO:
		   printf("Error: division or modulo by zero\n");
		   break;

		case CALC_STATUS_OVERFLOW:
		   printf("Error: overflow or underflow\n");
		   break;

		case CALC_STATUS_INVALID_SHIFT:
		   printf("Error: shift should be in range from 0 to 31\n");
		   break;

		case CALC_STATUS_NULL_POINTER:
		   printf("Error: null pointer\n");
		   break;
		
		case CALC_STATUS_OK:
		   break;

		default:
		   printf("Error: unknown error\n");
		   break;
	}
}

void print_result(const integer_t * p_result)
{
	if (INTEGER_TYPE_SIGNED == p_result->type)
	{
		printf("%d\n", p_result->value.signed_value);
	}
	else
	{
		printf("%u\n", p_result->value.unsigned_value);
	}
}
/*** end of the file ***/
