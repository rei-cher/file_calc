/**
 * @file errors.c
 * @brief Prints error based on the status and type
 * @author Drozdov Pavel
 * @version 1
 * @date 2026-08-10
 */

#include <stdio.h>

#include "errors.h"

static void print_dir_error(dir_status_t status);
static void print_file_error(file_status_t status);
static void print_equation_error(equation_status_t status);
static void print_calc_error(calc_statas_t status);

void print_error(error_type_t error_type, int status)
{
	switch(error_type)
	{
		case ERROR_TYPE_DIRECTORY:
			print_dir_error((dir_status_t)status);
			break;

		case ERROR_TYPE_FILE:
			print_file_error((file_status_t)status);
			break;

		case ERROR_TYPE_EQUATION:
			print_equation_error((equation_status_t)status);
			break;

		case ERROR_TYPE_CALCULATOR:
			print_calc_error((calc_status_t)status);
			break;
	}
}

static void print_dir_error(dir_status_t status)
{
    switch (status)
    {
        case DIR_STATUS_OK:
            break;

        case DIR_STATUS_NULL_POINTER:
            fprintf(stderr,
                    "Directory error: null pointer provided\n");
            break;

        case DIR_STATUS_DOESNT_EXIST:
            fprintf(stderr,
                    "Directory error: directory does not exist\n");
            break;

        case DIR_STATUS_NOT_DIRECTORY:
            fprintf(stderr,
                    "Directory error: path is not a directory\n");
            break;

        case DIR_STATUS_WRONG_PERMISSIONS:
            fprintf(stderr,
                    "Directory error: incorrect directory permissions\n");
            break;

        case DIR_STATUS_CANT_CREATE:
            fprintf(stderr,
                    "Directory error: could not create directory\n");
            break;

        default:
            fprintf(stderr,
                    "Directory error: unknown status\n");
            break;
    }
}

static void print_file_error(file_status_t status)
{
    switch (status)
    {
        case FILE_STATUS_OK:
            break;

        case FILE_STATUS_NULL_POINTER:
            fprintf(stderr,
                    "File error: null pointer provided\n");
            break;

        case FILE_STATUS_DOESNT_EXIST:
            fprintf(stderr,
                    "File error: file does not exist\n");
            break;

        case FILE_STATUS_NOT_FILE:
            fprintf(stderr,
                    "File error: path is not a regular file\n");
            break;

        case FILE_STATUS_WRONG_PERMISSIONS:
            fprintf(stderr,
                    "File error: incorrect file permissions\n");
            break;

        case FILE_STATUS_OPEN_ERROR:
            fprintf(stderr,
                    "File error: could not open file\n");
            break;

        case FILE_STATUS_READ_ERROR:
            fprintf(stderr,
                    "File error: could not read file\n");
            break;

        case FILE_STATUS_SEEK_ERROR:
            fprintf(stderr,
                    "File error: could not seek within file\n");
            break;

        case FILE_STATUS_INVALID_MAGIC:
            fprintf(stderr,
                    "File error: invalid file magic value\n");
            break;
        case FILE_STATUS_WRITE_ERROR:
            fprintf(stderr,
                    "File error: could not write file\n");
            break;

		case FILE_STATUS_NOT_EQU:
			fprintf(stderr,
					"File error: file is not equ\n");
			break;

        default:
            fprintf(stderr,
                    "File error: unknown status\n");
            break;
    }
}

static void print_equation_error(equation_status_t status)
{
    switch (status)
    {
        case EQ_STATUS_OK:
            break;

        case EQ_STATUS_NULL_POINTER:
            fprintf(stderr,
                    "Equation error: null pointer provided\n");
            break;

        case EQ_STATUS_READ_ERROR:
            fprintf(stderr,
                    "Equation error: could not read equation\n");
            break;

        case EQ_STATUS_INVALID_OPERATOR:
            fprintf(stderr,
                    "Equation error: invalid operator\n");
            break;

        case EQ_STATUS_NOT_SOLVED:
            fprintf(stderr,
                    "Equation error: equation could not be solved\n");
            break;

        case EQ_STATUS_WRITE_ERROR:
            fprintf(stderr,
                    "Equation error: could not write solved equation\n");
            break;

        default:
            fprintf(stderr,
                    "Equation error: unknown status\n");
            break;
    }
	FILE_STATUS_NOT_EQU
}

static void print_calc_error(calc_status_t status)
{
    switch (status)
    {
        case CALC_STATUS_OK:
            break;
       
		case CALC_STATUS_NULL_POINTER:
			fprintf(stderr,
					"Calculator error: null pointer provided\n");
			break;

		case CALC_STATUS_OVERFLOW:
			fprintf(stderr,
					"Calculator error: integer overflow\n");
			break;

		case CALC_STATUS_DIVIDE_BY_ZERO:
			fprintf(stderr,
					"Calculator error: division by zero\n");
			break;

		case CALC_STATUS_INVALID_SHIFT:
			fprintf(stderr,
					"Calcualtor error: ivalid shift\n");
			break;

		case CALC_STATUS_INVALID_ARGUMENT_COUNT:
			fprintf(stderr,
					"Calculator error: invalud number of arguments\n");
			break;

		case CALC_STATUS_INVALID_INTEGER:
			fprintf(stderr,
					"Calculator error: invalid integer\n");
			break;

		case CALC_STATUS_INVALID_OPERATOR:
			fprintf(stderr,
					"Calculator error: invalid operator\n");
			break;

		case CALC_STATUS_INTEGER_OUT_OF_RANGE:
			fprintf(stderr,
					"Calculator error: integer is out of range\n");
			break;

		case CALC_STATUS_INVALID_INTEGER_TYPE:
			fprintf(stderr,
					"Calculator error: invalid integer type\n");
			break;
	
		default:
            fprintf(stderr,
                    "Calculator error: unknown status\n");
            break;
    }
}
/*** end of the file ***/
