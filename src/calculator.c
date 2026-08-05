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

// TODO: determine if needed for the new approach
static calc_status_t parse_signed_integer(const char * p_input, int32_t * p_value)
{
	calc_status_t status = CALC_STATUS_OK;

	char * p_end = NULL;
	long long parsed_value = 0LL;

	if ((NULL == p_input) || (NULL == p_value))
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else
	{
		errno = 0;

		parsed_value = strtoll(p_input, &p_end, 10);

		if((p_end == p_input) || ('\0' != * p_end))
		{
			status = CALC_STATUS_INVALID_INTEGER;
		}
		else if ((ERANGE == errno) || 
				 (parsed_value < (long long)INT32_MIN) ||
				 (parsed_value > (long long)INT32_MAX))
		{
			status = CALC_STATUS_INTEGER_OUT_OF_RANGE;
		}
		else
		{
			* p_value = (int32_t)parsed_value;
		}
	}

	return status;
}

// TODO: determine if needed for the new approach
static calc_status_t parse_unsigned_integer(const char * p_input, uint32_t * p_value)
{
	calc_status_t status = CALC_STATUS_OK;

	char * p_end = NULL;
	unsigned long long parsed_value = 0ULL;

	if ((NULL == p_input) || (NULL == p_value))
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	else if ('-' == p_input[FIRST_CHARACTER])
	{
		status = CALC_STATUS_INTEGER_OUT_OF_RANGE;
	}
	else
	{
		errno = 0;

		parsed_value = strtoull(p_input, &p_end, 10);

		if((p_end == p_input) || ('\0' != * p_end))
		{
			status = CALC_STATUS_INVALID_INTEGER;
		}
		else if ((ERANGE == errno) || 
				 (parsed_value > (unsigned long long)UINT32_MAX))
		{
			status = CALC_STATUS_INTEGER_OUT_OF_RANGE;
		}
		else
		{
			* p_value = (int32_t)parsed_value;
		}
	}

	return status;
}

static calc_status_t validate_signed_integers(const char * p_f_input,
											  const char * p_s_input,
											  integer_t * p_f_integer,
											  integer_t * p_s_integer)
{
	calc_status_t status = CALC_STATUS_OK;

	int32_t f_value = 0;
	int32_t s_value = 0;

	if ((NULL == p_f_input) || (NULL == p_s_input) ||
		(NULL == p_f_integer) || (NULL == p_s_integer))
	{
		status = CALC_STATUS_NULL_POINTER;
	}

	if (CALC_STATUS_OK == status)
	{
		status = parse_signed_integer(p_f_input, &f_value);
	}
	
	if (CALC_STATUS_OK == status)
	{
		status = parse_signed_integer(p_s_input, &s_value);
	}

	if (CALC_STATUS_OK == status)
	{
		p_f_integer->type = INTEGER_TYPE_SIGNED;
		p_f_integer->value.signed_value = f_value;

		p_s_integer->type = INTEGER_TYPE_SIGNED;
		p_s_integer->value.signed_value = s_value;
	}

	return status;

}

static calc_status_t validate_unsigned_integers(const char * p_f_input,
											  const char * p_s_input,
											  integer_t * p_f_integer,
											  integer_t * p_s_integer)
{
	calc_status_t status = CALC_STATUS_OK;

	uint32_t f_value = 0U;
	uint32_t s_value = 0U;

	if ((NULL == p_f_input) || (NULL == p_s_input) ||
		(NULL == p_f_integer) || (NULL == p_s_integer))
	{
		status = CALC_STATUS_NULL_POINTER;
	}

	if (CALC_STATUS_OK == status)
	{
		status = parse_unsigned_integer(p_f_input, &f_value);
	}
	
	if (CALC_STATUS_OK == status)
	{
		status = parse_unsigned_integer(p_s_input, &s_value);
	}

	if (CALC_STATUS_OK == status)
	{
		p_f_integer->type = INTEGER_TYPE_UNSIGNED;
		p_f_integer->value.unsigned_value = f_value;

		p_s_integer->type = INTEGER_TYPE_UNSIGNED;
		p_s_integer->value.unsigned_value = s_value;
	}

	return status;
}

// TODO: remove (?)
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

// TODO: refactor to compare over codes
calc_status_t get_operator(const char * p_operator_string,
						   operator_t * p_operator)
{
	calc_status_t status = CALC_STATUS_OK;

	if ((NULL == p_operator_string) || (NULL == p_operator))
	{
		status = CALC_STATUS_NULL_POINTER;
	}
		
	if (CALC_STATUS_OK == status)
	{
		switch (p_operator_string[FIRST_CHARACTER])
		{
			case '+':
				if ('\0' == p_operator_string[FIRST_CHARACTER+1])
				{
					* p_operator = OPERATOR_ADD;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}
				break;

			case '-':
				if ('\0' == p_operator_string[FIRST_CHARACTER+1])
				{
					* p_operator = OPERATOR_SUBTRACT;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}
				break;
			
			case '*':
				if ('\0' == p_operator_string[FIRST_CHARACTER+1])
				{
					* p_operator = OPERATOR_MULTIPLY;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}
				break;
			
			case '/':
				if ('\0' == p_operator_string[FIRST_CHARACTER+1])
				{
					* p_operator = OPERATOR_DIVIDE;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}
				break;
			
			case '%':
				if ('\0' == p_operator_string[FIRST_CHARACTER+1])
				{
					* p_operator = OPERATOR_MODULO;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}
				break;

			case '&':
				if ('\0' == p_operator_string[FIRST_CHARACTER+1])
				{
					* p_operator = OPERATOR_AND;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}
				break;

			case '|':
				if ('\0' == p_operator_string[FIRST_CHARACTER+1])
				{
					* p_operator = OPERATOR_OR;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}
				break;
			
			case '^':
				if ('\0' == p_operator_string[FIRST_CHARACTER+1])
				{
					* p_operator = OPERATOR_XOR;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}
				break;
			
			case '>':
				if (0 == strcmp(p_operator_string, ">>"))
				{
					* p_operator = OPERATOR_RIGHT_SHIFT;
				}
				else if (0 == strcmp(p_operator_string, ">>>"))
				{
					* p_operator = OPERATOR_RIGHT_ROTATE;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}

				break;
			
			case '<':
				if (0 == strcmp(p_operator_string, "<<"))
				{
					* p_operator = OPERATOR_LEFT_SHIFT;
				}
				else if (0 == strcmp(p_operator_string, "<<<"))
				{
					* p_operator = OPERATOR_LEFT_ROTATE;
				}
				else
				{
					status = CALC_STATUS_INVALID_OPERATOR;
				}

				break;

			default:
				status = CALC_STATUS_INVALID_OPERATOR;
				break;
		}	
	}

	return status;
}

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

calc_status_t validate_integers(const char * p_f_input,
								const char * p_s_input,
								integer_type_t integer_type,
								integer_t * p_f_integer,
								integer_t * p_s_integer)
{
	calc_status_t status = CALC_STATUS_OK;

	if ((NULL == p_f_input) || (NULL == p_s_input) ||
		(NULL == p_f_integer) || (NULL == p_s_integer))
	{
		status = CALC_STATUS_NULL_POINTER;
	}
	
	if (INTEGER_TYPE_SIGNED == integer_type)
	{
		status = validate_signed_integers(p_f_input, 
										  p_s_input,
										  p_f_integer,
										  p_s_integer);
	}
	else if (INTEGER_TYPE_UNSIGNED == integer_type)
	{
		status = validate_unsigned_integers(p_f_input,
											p_s_input,
											p_f_integer,
											p_s_integer);
	}
	else
	{
		status = CALC_STATUS_INVALID_INTEGER_TYPE;
	}

	return status;


}

// TODO: split switch statement to call 2 different functions based on the operation type
// bitwise or arithmetic
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
	}

	if (CALC_STATUS_OK == status)
	{
		switch (operator)
		{
			case OPERATOR_ADD:
				result_type = INTEGER_TYPE_SIGNED;
				status = add (
						p_f_integer->value.signed_value,
						p_s_integer->value.signed_value,
						&p_result->value.signed_value);
				break;
		
			case OPERATOR_SUBTRACT:
				result_type = INTEGER_TYPE_SIGNED;
				status = subtract (
						p_f_integer->value.signed_value,
						p_s_integer->value.signed_value,
						&p_result->value.signed_value);
				break;
			
			case OPERATOR_MULTIPLY:
				result_type = INTEGER_TYPE_SIGNED;
				status = multiply (
						p_f_integer->value.signed_value,
						p_s_integer->value.signed_value,
						&p_result->value.signed_value);
				break;
			
			case OPERATOR_DIVIDE:
				result_type = INTEGER_TYPE_SIGNED;
				status = divide (
						p_f_integer->value.signed_value,
						p_s_integer->value.signed_value,
						&p_result->value.signed_value);
				break;
			
			case OPERATOR_MODULO:
				result_type = INTEGER_TYPE_SIGNED;
				status = modulo (
						p_f_integer->value.signed_value,
						p_s_integer->value.signed_value,
						&p_result->value.signed_value);
				break;
			
			case OPERATOR_AND:
				result_type = INTEGER_TYPE_UNSIGNED;
				status = op_and (
						p_f_integer->value.unsigned_value,
						p_s_integer->value.unsigned_value,
						&p_result->value.unsigned_value);
				break;
			
			case OPERATOR_OR:
				result_type = INTEGER_TYPE_UNSIGNED;
				status = op_or (
						p_f_integer->value.unsigned_value,
						p_s_integer->value.unsigned_value,
						&p_result->value.unsigned_value);
				break;
			
			case OPERATOR_XOR:
				result_type = INTEGER_TYPE_UNSIGNED;
				status = op_xor (
						p_f_integer->value.unsigned_value,
						p_s_integer->value.unsigned_value,
						&p_result->value.unsigned_value);
				break;
			
			case OPERATOR_LEFT_SHIFT:
				result_type = INTEGER_TYPE_UNSIGNED;
				status = l_shift (
						p_f_integer->value.unsigned_value,
						p_s_integer->value.unsigned_value,
						&p_result->value.unsigned_value);
				break;
			
			case OPERATOR_RIGHT_SHIFT:
				result_type = INTEGER_TYPE_UNSIGNED;
				status = r_shift (
						p_f_integer->value.unsigned_value,
						p_s_integer->value.unsigned_value,
						&p_result->value.unsigned_value);
				break;
			
			case OPERATOR_LEFT_ROTATE:
				result_type = INTEGER_TYPE_UNSIGNED;
				status = l_rotate (
						p_f_integer->value.unsigned_value,
						p_s_integer->value.unsigned_value,
						&p_result->value.unsigned_value);
				break;
			
			case OPERATOR_RIGHT_ROTATE:
				result_type = INTEGER_TYPE_UNSIGNED;
				status = r_rotate (
						p_f_integer->value.unsigned_value,
						p_s_integer->value.unsigned_value,
						&p_result->value.unsigned_value);
				break;

			default:
				status = CALC_STATUS_INVALID_OPERATOR;
				break;
		}

		if (CALC_STATUS_OK == status)
		{
			p_result->type = result_type;
		}
	}

	return status;
}


/*** end of the file ***/
