/** @file files.h
 *
 * @brief Defines logical operations for file handling
 *
 */

#include "file_status.h"
#include "files.h"

file_status_t validate_file(const char * p_file)
{
	file_status_t status = FILE_STATUS_OK;

	if (NULL == p_file)
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}



END:
	return status;

}

/*** end of the file ***/
