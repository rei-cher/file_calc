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
 * @brief Accepts input and output file
 * 		  Each file is being validate
 * 		  From input file the header is read and magic numbner is compared
 * 		  Calls calcualte_equations after reading input file header
 *
 * @param p_input_file
 * @param p_output_file
 *
 * @return File status
 */
file_status_t process_file(const char * p_input_file,
						   const char * p_output_file);

#endif

/*** end of the file ***/
