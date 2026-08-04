/** @file directories.h
 *
 * @brief Defines functions for directory.c
 *
 */

#ifndef DIRECTORIES_H
#define DIRECTORIES_H

#include "dir_status.h"

dir_status_t validate_directories(const char * p_dir);
dir_status_t create_dir(const char * p_dir);

#endif

/*** end of the file ***/
