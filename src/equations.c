/** @file equations.c
 *
 * @brief Defines logical operations for equiation process
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "file_status.h"
#include "equations.h"
#include "equation_status.h"
#include "calculator.h"

#define SINGLE_OBJECT_COUNT 1U

static equation_status_t validate_format(p_file, p_equation);
static equation_status_t solve_equation(equation_t * p_equation,
										integer_t * p_result);

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

equation_status_t calculate_equations(FILE * p_file, uint64_t num_of_eq)
{
	equation_t unsolved_eq = {0};
	solved_t solved_eq = {0};
	integer_t result = {0};

	integer_type_t integer_type = INTEGER_TYPE_SIGNED;
	file_status_t status = FILE_STATUS_OK;
	equation_status_t eq_status = EQ_STATUS_OK;
	calc_status_t calc_status = CALC_STATUS_OK;
	
	integer_t result = {0};

	if (NULL == p_file)
	{
		status = FILE_STATUS_NULL_POINTER;
		goto END;
	}



	for (uint64_t index = 0U; index < num_of_eq; index++)
	{
		unsolved_eq = (equation_t){0};
		solved_eq = (solved_t){0};

		eq_status = read_equation(p_file, &unsolved_eq);

		if (EQ_STATUS_OK != eq_status)
		{
			status = FILE_STATUS_READ_ERROR;
			goto END;
		}

		solved_eq.id = unsolved_eq.id;

		eq_status = solve_equation(&unsolved_eq, &result);

		if (EQ_STATUS_OK == eq_status)
		{
			solved_eq.flag = 0x01U;
		}
		else
		{
			solved_eq.flag = 0x00U;
		}
	}

END:
	return status;
}

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

// TODO:
// 	parse equation
// 	get_operator()
// 	based on the operator determin integer type for 
// 		result, first int, second int
// 	once determined
// 	calculate()
static equation_status_t solve_equation(equation_t * p_equation,
										integer_t * p_result)
{

}
/*** end of the file ***/
