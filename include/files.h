/** @file files.h
 *
 * @brief Defines functions for files.c
 *
 */

#ifndef FILES_H
#define FILES_H

#include <stdint.h>
#include <stdio.h>
#include "file_status.h"

typedef struct
{
	uint32_t magic;
	uint64_t file_id;
	uint64_t num_of_eq;
	uint8_t flag;
	uint32_t eq_offset;
	uint16_t opt_headers;
} file_header_t;

/**
 *	Function: validate_file
 *	Purpose: Should be used to validate file existance in the input directory
 *	and should not be used over created files in output directory
 */

file_status_t create_file(const char * p_file_path);
file_status_t process_file(const char * p_input_file,
						   const char * p_output_file);

#endif

/*** end of the file ***/
