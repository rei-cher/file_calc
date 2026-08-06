/** @file files.c
 *
 * @brief Defines logical operations for file handling
 *
 */

#include <sys/stat.h>

#include "files.h"
#include "file_status.h"

static file_status_t read_header(FILE * p_file, file_header_t * p_header);
static file_status_t process_equations(FILE * p_file, uint64_t num_of_eq);

file_status_t validate_file(const char * p_file_path)
{
	struct stat file_stat_t = {0};

	file_status_t status = FILE_STATUS_OK;

	if (NULL == p_file_path)
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}

	if (0 != stat(p_file_path, &file_stat_t))
	{
		status = FILE_STATUS_DOESNT_EXIST;
		goto END;
	}

	if (0 == S_ISREG(file_stat_t.st_mode))
	{
		status = FILE_STATUS_NOT_FILE;
		goto END;
	}

	if (0644U != (file_stat_t.st_mode & 0644U))
	{
		status = FILE_STATUS_WRONG_PERMISSIONS;
		goto END;
	}

END:
	return status;

}

file_status_t process_file(const char * p_filename)
{
	FILE * p_file = NULL;
	file_header_t file_header = {0};
	file_status_t status = FILE_STATUS_OK;

	if (NULL == p_filename)
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}

	p_file = fopen(p_filename, "rb");

	if (NULL == p_file)
	{
		fclose(p_file);
		p_file = NULL;
		status = FILE_STATUS_OPEN_ERROR;
		goto END;
	}

	status = read_header(p_file, &file_header);

	if (FILE_STATUS_OK != status)
	{
		goto END;
	}

	if (0x55BB77DDU != file_header.magic)
	{
		status = FILE_STATUS_INVALID_MAGIC;
		goto END;
	}

	if (0 != fseek(p_file, file_header.eq_offset, SEEK_SET))
	{
		status = FILE_STATUS_SEEK_ERROR;
		goto END;
	}

	// TODO: calcualte_equations -> implement accepting pointer to output file
	if (FILE_STATUS_OK == status)
	{
		calculate_equations(p_file, file_header.num_of_eq);
	}

END:
	if (NULL != p_file)
	{
		fclose(p_file);
		p_file = NULL;
	}

	return status;
}

file_status_t create_file(const char * p_file_path)
{
	file_status_t status = FILE_STATUS_OK;
}

static file_status_t read_header(FILE * p_file, file_header_t * p_header)
{
	file_status_t status = FILE_STATUS_OK;

	if ((NULL == p_file) ||
		(NULL == p_header))
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}

	if (1U != fread(&p_header->magic, sizeof(p_header->magic), 1U, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (1U != fread(&p_header->file_id, sizeof(p_header->file_id), 1U, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (1U != fread(&p_header->num_of_eq, sizeof(p_header->num_of_eq), 1U, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (1U != fread(&p_header->flag, sizeof(p_header->flag), 1U, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (1U != fread(&p_header->eq_offset, sizeof(p_header->eq_offset), 1U, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (1U != fread(&p_header->op_headers, sizeof(p_header->opt_headers), 1U, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

END:
	return status;
}
/*** end of the file ***/
