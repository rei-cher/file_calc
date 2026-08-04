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
	FILE_SATATUS_NULL_POINTER;
} file_status_t;

typedef struct
{
	uint32_t magic = 0U;
	uint64_t file_id = 0U;
	uint64_t num_of_eq = 0U;
	uint8_t flag = 0U;
	uint32_t eq_offset = 0U;
	uint16_t opt_headers = 0U;
} file_header_t;

#endif

/*** end of the file ***/
