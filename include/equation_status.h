/** @file equation_status.h
 *
 * @brief Defines flow status for equstion's operations
 *
 */

#ifndef EQUATION_STATUS_H
#define EQUATION_STATUS_H

typedef enum 
{
	EQ_STATUS_OK = 0,
	EQ_STATUS_NULL_POINTER,
	EQ_STATUS_READ_ERROR,
	EQ_STATUS_NOT_SOLVED
} equation_status_t;

#endif

/*** end of the file ***/
