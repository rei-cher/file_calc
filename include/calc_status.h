/** @file calc_status.h
 *
 * @ brief Defines base structure to track the state of calculation
 *
 *
 */

#ifndef CALC_STATUS_H
#define CALC_STATUS_H

typedef enum
{
	CALC_STATUS_OK = 0,
	CALC_STATUS_NULL_POINTER,
	CALC_STATUS_OVERFLOW,
	CALC_STATUS_DIVIDE_BY_ZERO,
	CALC_STATUS_INVALID_SHIFT,
	CALC_STATUS_INVALID_ARGUMENT_COUNT,
	CALC_STATUS_INVALID_INTEGER,
	CALC_STATUS_INVALID_OPERATOR,
	CALC_STATUS_INTEGER_OUT_OF_RANGE,
	CALC_STATUS_INVALID_INTEGER_TYPE
} calc_status_t;

#endif

/*** end of the file ***/
