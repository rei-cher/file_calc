/** @file file_status.h
 *
 * @brief Defines flow status for file's operations
 *
 */

#ifndef FILE_STATUS_H
#define FILE_STATUS_H

/**
 * @brief File status list
 */
typedef enum
{
	FILE_STATUS_OK = 0,
	FILE_STATUS_NULL_POINTER,
	FILE_STATUS_DOESNT_EXIST,
	FILE_STATUS_STAT_ERROR,
	FILE_STATUS_NOT_FILE,
	FILE_STATUS_WRONG_PERMISSIONS,
	FILE_STATUS_OPEN_ERROR,
	FILE_STATUS_READ_ERROR,
	FILE_STATUS_WRITE_ERROR,
	FILE_STATUS_INVALID_MAGIC,
	FILE_STATUS_SEEK_ERROR,
	FILE_STATUS_NOT_EQU
} file_status_t;

#endif

/*** end of the file ***/
