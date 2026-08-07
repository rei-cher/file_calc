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
	OPERATOR_ADD = 0x01U,
	OPERATOR_SUBTRACT = 0x02U,
	OPERATOR_MULTIPLY = 0x03U,
	OPERATOR_DIVIDE = 0x04U,
	OPERATOR_MODULO = 0x05U,
	OPERATOR_LEFT_SHIFT = 0x06U,
	OPERATOR_RIGHT_SHIFT = 0x07U,
	OPERATOR_AND = 0x08U,
	OPERATOR_OR = 0x09U,
	OPERATOR_XOR = 0x0AU,
	OPERATOR_LEFT_ROTATE = 0x0BU,
	OPERATOR_RIGHT_ROTATE = 0x0CU
} operator_t;

typedef enum
{
	INTEGER_TYPE_SIGNED = 0x01U,
	INTEGER_TYPE_UNSIGNED = 0x02U
} integer_type_t;

typedef union
{
	int64_t signed_value;
	uint64_t unsigned_value;
} value_t;

typedef struct
{
	integer_type_t type;
	value_t	   value;
} integer_t;

integer_type_t get_integer_type(operator_t operator);

calc_status_t calculate_result(operator_t operator,
							   const integer_t * p_f_integer,
							   const integer_t * p_s_integer,
							   integer_t * p_result);

void print_result(const integer_t * p_result);

void print_error(calc_status_t status);

void print_usage(const char * p_name);

#endif

/*** end of the file ***/
