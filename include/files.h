/** @file files.h
 *
 * @brief Defines functions for files.c
 *
 */

#ifndef FILES_H
#define FILES_H

#include "file_status.h"

file_status_t validate_file(const char * p_file);
file_status_t create_file(const char * p_file);

#endif

/*** end of the file ***/
