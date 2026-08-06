/** @file directory.c
 *
 *  @brief Defines main logic for directory process
 *
 */

#include <sys/stat.h>

#include "dir_status.h"
#include "directories.h"

dir_status_t create_dir(const char * p_dir)
{
	dir_status_t status = DIR_STATUS_OK;

	if (NULL == p_dir)
	{
		status = DIR_STATUS_NULL_POINTER;

		goto END;
	}

	if (0 != mkdir(p_dir, 0755))
	{
		status = DIR_STATUS_CANT_CREATE;
	}

END:
	return status;
}

dir_status_t validate_directory(const char * p_dir)
{
	struct stat dir_stat_t = {0};

	dir_status_t status = DIR_STATUS_OK;

	if (NULL == p_dir)
	{
		status = DIR_STATUS_NULL_POINTER;

		goto END;
	}

	if (0 != stat(p_dir, &dir_stat_t))
	{
		status = DIR_STATUS_DOESNT_EXIST;		
		goto END;
	}

	if  (0 == S_ISDIR(dir_stat_t.st_mode))
	{
		status = DIR_STATUS_NOT_DIRECTORY;

		goto END;
	}
	
	if ((DIR_STATUS_OK == status) && 
		(0755U != (dir_stat_t.st_mode & 0755U)))
	{
		status = DIR_STATUS_WRONG_PERMISSIONS;
		goto END;
	}

END:
	return status;
}


/*** end of the file ***/
