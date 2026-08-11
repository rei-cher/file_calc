/** @file directory.c
 *
 *  @brief Defines main logic for directory process
 *
 */

#include <linux/limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "files.h"
#include "errors.h"
#include "dir_status.h"
#include "directories.h"

static dir_status_t create_dir(const char * p_dir);
static dir_status_t validate_directory(const char * p_dir);

dir_status_t prepare_directories(const char * p_input_dir,
								 const char * p_output_dir)
{

	dir_status_t status = DIR_STATUS_OK;

	if ((NULL == p_input_dir) ||
		(NULL == p_output_dir))
	{
		status = DIR_STATUS_NULL_POINTER;
		goto END;
	}

	status = validate_directory(p_input_dir);

	if (DIR_STATUS_OK != status)
	{
		goto END;
	}

	status = validate_directory(p_output_dir);

	if (DIR_STATUS_DOESNT_EXIST == status)
	{
		status = create_dir(p_output_dir);
	}

END:
	return status;
}

dir_status_t process_directories(const char * p_input_dir,
								 const char * p_output_dir)
{
	dir_status_t status = DIR_STATUS_OK;
	file_status_t file_status = FILE_STATUS_OK;

	char input_path[PATH_MAX] = {0};

	DIR * p_dir = NULL;
	struct dirent * p_file = NULL;

	if ((NULL == p_input_dir) || 
		(NULL == p_output_dir))
	{
		status = DIR_STATUS_NULL_POINTER;
		goto END;
	}

	p_dir = opendir(p_input_dir);

	if (NULL == p_dir)
	{
		status = DIR_STATUS_OPEN_ERROR;
		goto END;
	}

	while (NULL != (p_file = readdir(p_dir)))
	{
		if ((0 == strcmp(p_file->d_name, ".")) ||
			(0 == strcmp(p_file->d_name, "..")))
		{
			continue;
		}
		snprintf(input_path,
				 sizeof(input_path),
				 "%s/%s",
				 p_input_dir,
				 p_file->d_name);

		file_status = process_file(input_path,
								   p_output_dir);

		if (FILE_STATUS_OK != file_status)
		{
			print_error(ERROR_TYPE_FILE, file_status);
		}
	}

END:
	if (NULL != p_dir)
	{
		closedir(p_dir);
		p_dir = NULL;
	}

	return status;
}

static dir_status_t create_dir(const char * p_dir)
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

static dir_status_t validate_directory(const char * p_dir)
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
