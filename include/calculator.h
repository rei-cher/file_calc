/** @file calculator.h
 *
 * @brief Defines calculator interface
 *
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdint.h>
#include "calc_status.h"

/**
 * @brief List of all operators with assigned values
 */
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

/**
 * @brief List of integer types with assigned values
 */
typedef enum
{
	INTEGER_TYPE_SIGNED = 0x01U,
	INTEGER_TYPE_UNSIGNED = 0x02U
} integer_type_t;

/**
 * @brief Structure to define integer type based on the operator
 */
typedef union
{
	int64_t signed_value;
	uint64_t unsigned_value;
} value_t;

/**
 * @brief Structure to hold type and corresponding integer value
 */
typedef struct
{
	integer_type_t type;
	value_t	   value;
} integer_t;

/**
 * @brief Function that accepts operator
 * 		  Based on the operator, corresponding integer type will be returned
 *
 * @param operator
 *
 * @return interger_type_t
 */
integer_type_t get_integer_type(operator_t operator);

/**
 * @brief Function that calcualtes the result from operator and operands
 *
 * @param operator
 * @param p_f_integer
 * @param p_s_integer
 * @param p_result
 *
 * @return calc_status_t
 */
calc_status_t calculate_result(operator_t operator,
							   const integer_t * p_f_integer,
							   const integer_t * p_s_integer,
							   integer_t * p_result);

#endif

/*** end of the file ***/
