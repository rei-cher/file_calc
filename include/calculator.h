/** @file calculator.h
 *
 * @brief Defines calculator interface
 *
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdint.h>
#include "calc_status.h"

typedef enum
{
	OPERATOR_ADD = 0,
	OPERATOR_SUBTRACT,
	OPERATOR_MULTIPLY,
	OPERATOR_DIVIDE,
	OPERATOR_MODULO,
	OPERATOR_AND,
	OPERATOR_OR,
	OPERATOR_XOR,
	OPERATOR_LEFT_SHIFT,
	OPERATOR_RIGHT_SHIFT,
	OPERATOR_LEFT_ROTATE,
	OPERATOR_RIGHT_ROTATE
} operator_t;

typedef enum
{
	INTEGER_TYPE_SIGNED = 0,
	INTEGER_TYPE_UNSIGNED
} integer_type_t;

typedef union
{
	int32_t signed_value;
	uint32_t unsigned_value;
} value_t;

typedef struct
{
	integer_type_t type;
	value_t	   value;
} integer_t;

calc_status_t get_operator(const char * p_operator_string,
						   operator_t * p_operator);

integer_type_t get_integer_type(operator_t operator);

calc_status_t validate_integers(const char * p_f_input,
								const char * p_s_input,
								integer_type_t integer_type,
								integer_t * p_f_integer,
								integer_t * p_s_integer);

calc_status_t calculate_result(operator_t operator,
							   const integer_t * p_f_integer,
							   const integer_t * p_s_integer,
							   integer_t * p_result);

void print_result(const integer_t * p_result);

void print_error(calc_status_t status);

void print_usage(const char * p_name);

#endif

/*** end of the file ***/
