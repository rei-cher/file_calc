/** @file directories.h
 *
 * @brief Defines functions for directory.c
 *
 */

#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include "dir_status.h"

dir_status_t prepare_directories(const char * p_input_dir,
								 const char * p_output_dir);

dir_status_t process_directories(const char * p_input_dir,
							   const char * p_output_dir);
#endif

/*** end of the file ***/
