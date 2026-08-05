/** @file equations.c
 *
 * @brief Defines logical operations for equiation process
 *
 */

#include "equations.h"
#include "equation_status.h"

#define SINGLE_OBJECT_COUNT 1U

static equation_status_t validate_format(p_file, p_equation)
{
	equation_status_t status = EQ_STATUS_OK;

	if (SINGLE_OBJECT_COUNT != fread(&p_equation->id, sizeof(p_equation->id), SINGLE_OBJECT_COUNT, p_file))
	{
		status = EQ_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_equation->flag, sizeof(p_equation->flag), SINGLE_OBJECT_COUNT, p_file))
	{
		status = EQ_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_equation->equaltion.first_operand,
					sizeof(p_equation->equation.first_operand),
					SINGLE_OBJECT_COUNT,
					p_file))
	{
		status = EQ_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_equation->equation.operator,
					sizeof(p_equation->equation.operator),
					SINGLE_OBJECT_COUNT,
					p_file))
	{
		status = EQ_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(&p_equation->equation.second_operand,
					sizeof(p_equation->equation.second_operand),
					SINGLE_OBJECT_COUNT,
					p_file))
	{
		status = EQ_STATUS_READ_ERROR;
		goto END;
	}

	if (SINGLE_OBJECT_COUNT != fread(p_equation->padding,
					sizeof(p_equation->padding),
					SINGLE_OBJECT_COUNT,
					p_file))
	{
		status = EQ_STATUS_READ_ERROR;
		goto END;
	}

END:
	return status;
}

equation_status_t read_equation(FILE * p_file, equation_t * p_equation)
{
	equation_status_t status = EQ_STATUS_OK;

	if ((NULL == p_file) ||
		(NULL == p_equation))
	{
		status = EQ_STATUS_NULL_POINTER;
		goto END;
	}

	status = validate_format(p_file, p_equation);

END:
	return status;	
}

equation_status_t calculate_equation(const equation_t * p_equation,
									 solved_t * p_solved)
{
	equation_status_t status = EQ_STATUS_OK;

	

END:
	return status;
}

/*** end of the file ***/
