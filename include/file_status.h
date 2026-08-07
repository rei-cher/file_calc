/** @file file_status.h
 *
 * @brief Defines flow status for file's operations
 *
 */

#ifndef FILE_STATUS_H
#define FILE_STATUS_H

typedef enum
{
	FILE_STATUS_OK = 0,
	FILE_STATUS_NULL_POINTER,
	FILE_STATUS_DOESNT_EXISTS,
	FILE_STATUS_STAT_ERROR,
	FILE_STATUS_NOT_FILE,
	FILE_STATUS_WRONG_PERMISSIONS,
	FILE_STATUS_OPEN_ERROR,
	FILE_STATUS_READ_ERROR,
	FILE_STATUS_INVALID_MAGIC,
	FILE_STATUS_SEEK_ERROR
} file_status_t;

#endif

/*** end of the file ***/
