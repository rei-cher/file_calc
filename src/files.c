/** @file files.c
 *
 * @brief Defines logical operations for file handling
 *
 */

#include <linux/limits.h>
#include <string.h>
#include <sys/stat.h>

#include "files.h"
#include "equations.h"
#include "file_status.h"
#include "errors.h"

#define SINGLE_OBJECT_COUNT 1U
#define EXTENSION_SIZE 4U

static file_status_t read_header(FILE * p_file, file_header_t * p_header);

static file_status_t validate_file(const char * p_file_path);

static file_status_t write_header(FILE * p_filen, file_header_t * p_header);

static file_status_t get_filename(const char * p_file_path,
								  const char ** pp_file_name);

file_status_t process_file(const char * p_input_dir,
						   const char * p_output_dir)
{
	FILE * p_input_file = NULL;
	FILE * p_output_file = NULL;
	const char * p_file_name = NULL;

	file_header_t file_header = {0};	
	file_status_t status = FILE_STATUS_OK;
	equation_status_t eq_status = EQ_STATUS_OK;

	char output_path[PATH_MAX] = {0};

	if ((NULL == p_input_dir) ||
		(NULL == p_output_dir))
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}

	status = validate_file(p_input_dir);
	if (FILE_STATUS_OK != status)
	{
		goto END;
	}

	status = get_filename(p_input_dir, &p_file_name);
	if (FILE_STATUS_OK != status)
	{
		goto END;
	}

	p_input_file = fopen(p_input_dir, "rb");

	if (NULL == p_input_file)
	{
		status = FILE_STATUS_OPEN_ERROR;
		goto END;
	}

	fprintf(stdout, "Processing file %s\n", p_input_dir);
	status = read_header(p_input_file, &file_header);

	if (FILE_STATUS_OK != status)
	{
		goto END;
	}

	if (0xDD77BB55U != file_header.magic)
	{
		status = FILE_STATUS_INVALID_MAGIC;
		goto END;
	}

	snprintf(output_path,
			 sizeof(output_path),
			 "%s/%.*s_solved.equ",
			 p_output_dir,
			 (int)(strlen(p_file_name) - EXTENSION_SIZE),
			 p_file_name);

	p_output_file = fopen(output_path, "wb");

	if (NULL == p_output_file)
	{
		status = FILE_STATUS_OPEN_ERROR;
		goto END;
	}

	file_header.flag = 0x01U;

	status = write_header(p_output_file, &file_header);

	if (FILE_STATUS_OK != status)
	{
		goto END;
	}

	if (0 != fseek(p_input_file, file_header.eq_offset, SEEK_SET))
	{
		status = FILE_STATUS_SEEK_ERROR;
		goto END;
	}

	eq_status = calculate_equations(p_input_file, 
									p_output_file, 
									file_header.num_of_eq);

	if (EQ_STATUS_OK != eq_status)
	{
		print_error(ERROR_TYPE_EQUATION, eq_status);
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

END:
	if (NULL != p_input_file)
	{
		fclose(p_input_file);
		p_input_file = NULL;
	}

	if (NULL != p_output_file)
	{
		fclose(p_output_file);
		p_output_file = NULL;
	}

	return status;
}

static file_status_t validate_file(const char * p_file_path)
{
	struct stat file_stat_t = {0};
	const char * p_extension = NULL;

	file_status_t status = FILE_STATUS_OK;

	if (NULL == p_file_path)
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}

	p_extension = strrchr(p_file_path, '.');
	if ((NULL == p_extension) ||
		(0 != strcmp(p_extension, ".equ")))
	{
		status = FILE_STATUS_NOT_EQU;
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

static file_status_t write_header(FILE * p_file, 
								  file_header_t * p_header)
{
	file_status_t status = FILE_STATUS_OK;

	if ((NULL == p_file) ||
		(NULL == p_header))
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fwrite(&p_header->magic, sizeof(p_header->magic), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_WRITE_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fwrite(&p_header->file_id, sizeof(p_header->file_id), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_WRITE_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fwrite(&p_header->num_of_eq, sizeof(p_header->num_of_eq), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_WRITE_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fwrite(&p_header->flag, sizeof(p_header->flag), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_WRITE_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fwrite(&p_header->eq_offset, sizeof(p_header->eq_offset), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_WRITE_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fwrite(&p_header->opt_headers, sizeof(p_header->opt_headers), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_WRITE_ERROR;
		goto END;
	}

END:
	return status;
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

	if (SINGLE_OBJECT_COUNT != fread(&p_header->magic, sizeof(p_header->magic), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_header->file_id, sizeof(p_header->file_id), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_header->num_of_eq, sizeof(p_header->num_of_eq), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_header->flag, sizeof(p_header->flag), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_header->eq_offset, sizeof(p_header->eq_offset), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_header->opt_headers, sizeof(p_header->opt_headers), SINGLE_OBJECT_COUNT, p_file))
	{
		status = FILE_STATUS_READ_ERROR;
		goto END;
	}

END:
	return status;
}

static file_status_t get_filename(const char * p_file_path,
								  const char ** pp_file_name)
{
	file_status_t status = FILE_STATUS_OK;

	if ((NULL == p_file_path) ||
		(NULL == pp_file_name))
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}

	* pp_file_name = strchr(p_file_path, '/');
	
	if (NULL != pp_file_name)
	{
		(* pp_file_name)++;
	}
	else
	{
		* pp_file_name = p_file_path;
	}

END:
	return status;
}

/*** end of the file ***/
