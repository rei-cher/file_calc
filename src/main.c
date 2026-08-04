/** @file main.c
 *
 * @brief Program entry point
 *
 */

#include <stdlib.h>
#include "directory.h"
#include "dir_status.h"

#define PROGRAM_NAME 0
#define INPUT_DIR 1
#define OUTPUT_DIR 2
#define NUMBER_OF_ARGUMENTS 3

static void print_usage(const char * p_name)
{
	printf("Usage: %s <input directory> <output directory>\n", p_name);
}

int main(int argc, char ** argv)
{
	int exit_status = EXIT_FAILURE;
	// TODO: move validation logic into directory.c
	// have function (validate_directories(const char agrv[input], const char argv[output]))
	// return dir_status_t
	dir_status_t input_dir_status = DIR_STATUS_OK;
	dir_status_t output_dir_status = DIR_STATUS_OK;

	if (NUMBER_OF_ARGUMENTS != argc)
	{
		printf("Incorrect number of argumentn");
		print_usage(argv[PROGRAM_NAME]);
		goto END;
	}

	input_dir_status = validate_directory(argv[INPUT_DIR]);

	if (DIR_STATUS_OK != input_dir_status)
	{
		print_error(input_dir_status);
		goto END;
	}

	output_dir_status = validate_directory(argv[OUTPUT_DIR]);
	if (DIR_STATUS_DOESNT_EXIST != output_dir_status)
	{
		status = create_dir(argv[OUTPUT_DIR]);
	}

	if (DIR_STATUS_OK != output_dir_status)
	{
		print_error(output_dir_status);
	}

END:
	return exit_status;
}

/*** end of the file ***/
