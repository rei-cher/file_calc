/** @file main.c
 *
 * @brief Program entry point
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "directories.h"
#include "dir_status.h"
#include "errors.h"

#define PROGRAM_NAME 0
#define INPUT_DIR 1
#define OUTPUT_DIR 2
#define NUMBER_OF_ARGUMENTS 3

/**
 * @brief Prints usage
 *
 * @param p_name
 */
static void print_usage(const char * p_name)
{
	printf("Usage: %s <input directory> <output directory>\n", p_name);
}

int main(int argc, char ** argv)
{
	int exit_status = EXIT_FAILURE;

	dir_status_t dir_status = DIR_STATUS_OK;

	if (NUMBER_OF_ARGUMENTS != argc)
	{
		fprintf(stderr, "Incorrect number of arguments\n");
		print_usage(argv[PROGRAM_NAME]);
		goto END;
	}

	dir_status = prepare_directories(argv[INPUT_DIR],
									 argv[OUTPUT_DIR]);

	if (DIR_STATUS_OK != dir_status)
	{
		print_error(ERROR_TYPE_DIRECTORY, dir_status);
		goto END;
	}

	dir_status = process_directories(argv[INPUT_DIR],
									 argv[OUTPUT_DIR]);

	if (DIR_STATUS_OK != dir_status)
	{
		print_error(ERROR_TYPE_DIRECTORY, dir_status);
		goto END;
	}

	exit_status = EXIT_SUCCESS;

END:
	return exit_status;
}

/*** end of the file ***/
