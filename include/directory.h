/** @file directory.h
 *
 * @brief Defines functions for directory.c
 *
 */

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "dir_status.h"

dir_status_t validate_directory(const char * p_dir);
dir_status_t create_dir(const char * p_dir);
#endif

/*** end of the file ***/
