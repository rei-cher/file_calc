/** @file dir_status.h
 *
 * @brief Defines flow status for directory operations
 *
 */

#ifndef DIR_STATUS_H
#define DIR_STATUS_H

/**
 * @brief Directory status list
 */
typedef enum
{
	DIR_STATUS_OK = 0,
	DIR_STATUS_NULL_POINTER,
	DIR_STATUS_DOESNT_EXIST,
	DIR_STATUS_STAT_ERROR,
	DIR_STATUS_NOT_DIRECTORY,
	DIR_STATUS_WRONG_PERMISSIONS,
	DIR_STATUS_CANT_CREATE,
	DIR_STATUS_OPEN_ERROR
} dir_status_t;

#endif

/*** end of the file ***/
