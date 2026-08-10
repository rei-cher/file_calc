/**
 * @file errors.h
 * @brief Defines error printing functions
 * @author Drozdov Pavel
 * @version 1
 * @date 2026-08-10
 */

#ifndef ERRORS_H
#define ERRORS_H

#include "dir_status.h"
#include "file_status.h"
#include "equation_status.h"
#include "calc_status.h"

/**
 * @brief List of error types
 */
typedef enum
{
	ERROR_TYPE_DIRECTORY = 0,
	ERROR_TYPE_FILE,
	ERROR_TYPE_EQUATION,
	ERROR_TYPE_CALCULATOR
} error_type_t;

/**
 * @brief Prints descriptive error based on the error type
 *
 * @param error_type
 * @param status
 */
void print_error(error_type_t error_type, int status);

#endif

/*** end of the file ***/
