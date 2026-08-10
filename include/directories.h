/** @file directories.h
 *
 * @brief Defines functions for directory.c
 *
 */

#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include "dir_status.h"

/**
 * @brief Taked input and output directories.
 * 		  Validated them
 * 		  If ouput directory doesnt exist, creates it 
 *
 * @param p_input_dir
 * @param p_output_dir
 *
 * @return Directory status 
 */
dir_status_t prepare_directories(const char * p_input_dir,
								 const char * p_output_dir);

/**
 * @brief Takes input and output directories.
 * 		  Opens input directory and read files from that directory
 * 		  Each file is being sent to process_file
 *
 * @param p_input_dir
 * @param p_output_dir
 *
 * @return Directory status
 */
dir_status_t process_directories(const char * p_input_dir,
							   const char * p_output_dir);
#endif

/*** end of the file ***/
