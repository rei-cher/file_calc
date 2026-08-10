/** @file equations.c
 *
 * @brief Defines logical operations for equiation process
 *
 */

#include <stdint.h>
#include <stdio.h>

#include "equations.h"
#include "equation_status.h"
#include "calculator.h"

#define SINGLE_OBJECT_COUNT 1U

static equation_status_t validate_format(FILE * p_file, equation_t * p_equation);
static equation_status_t solve_equation(equation_t * p_equation,
										integer_t * p_result);
static equation_status_t read_equation(FILE * p_file, equation_t * p_equation);
static equation_status_t get_equation_operator(uint8_t operator_code,
											   operator_t * p_operator);


equation_status_t calculate_equations(FILE * p_input_file,
									  FILE * p_output_file,
									  uint64_t num_of_eq)
{
	equation_t unsolved_eq = {0};
	solved_t solved_eq = {0};
	integer_t result = {0};

	equation_status_t status = EQ_STATUS_OK;

	if ((NULL == p_input_file) ||
		(NULL == p_output_file))
	{
		status = EQ_STATUS_NULL_POINTER;
		goto END;
	}

	for (uint64_t index = 0U; index < num_of_eq; index++)
	{
		unsolved_eq = (equation_t){0};
		solved_eq = (solved_t){0};

		status = validate_equation_format(p_input_file, &unsolved_eq);

		if (EQ_STATUS_OK != eq_status)
		{
			status = EQ_STATUS_READ_ERROR;
			goto END;
		}

		solved_eq.id = unsolved_eq.id;

		status = solve_equation(&unsolved_eq, &result);

		if (EQ_STATUS_OK == eq_status)
		{
			solved_eq.flag = 0x01U;
			solved_eq.type = result.type;
			solved_eq.solution = result.value;
		}
		else
		{
			solved_eq.flag = 0x00U;
			solved_eq.type = 0x00U;
			solved_eq.solution = 0U;
		}

		file_status = write_solved_eq(p_output_file, &solved_eq);

		if (FILE_STATUS_OK != file_status)
		{
			// TODO: set status to something
			goto END;
		}
	}

END:
	return status;
}

static equation_status_t validate_equation_format(FILE * p_file, equation_t *  p_equation)
{
	equation_status_t status = EQ_STATUS_OK;
	
	if ((NULL == p_file) ||
		(NULL == p_equation))
	{
		status = EQ_STATUS_NULL_POINTER;
		goto END;
	}


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

	if (SINGLE_OBJECT_COUNT != fread(&p_equation->equation.first_operand,
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

static equation_status_t solve_equation(equation_t * p_equation,
										integer_t * p_result)
{
	integer_type_t integer_type = INTEGER_TYPE_SIGNED;
	calc_status_t calc_status = CALC_STATUS_OK;
	equation_status_t status = EQ_STATUS_OK;
	operator_t operator = OPERATOR_ADD;

	integer_t first_int = {0};
	integer_t second_int = {0};

	if ((NULL == p_equation) ||
		(NULL == p_result))
	{
		status = EQ_STATUS_NULL_POINTER;
		goto END;
	}

	status = get_equation_operator(p_equation->equation.operator,
								   &operator);

	if (EQ_STATUS_OK != status)
	{
		goto END;
	}

	integer_type = get_integer_type(operator);

	first_int.type = integer_type;
	second_int.type = integer_type;

	first_int.value = p_equation->equation.first_operand;
	second_int.value = p_equation->equation.second_operand;

	calc_status = calculate_result(operator,
								   &first_int,
								   &second_int,
								   p_result);

	if (CALC_STATUS_OK != calc_status)
	{
		status = EQ_STATUS_NOT_SOLVED;
		goto END;
	}

END:
	return status;
}

static equation_status_t get_equation_operator(uint8_t operator_code,
											   operator_t * p_operator)
{
	equation_status_t status = EQ_STATUS_OK;

	if (NULL == p_operator)
	{
		status = EQ_STATUS_NULL_POINTER;
		goto END;
	}
	
	if ((OPERATOR_ADD > operator_code) || 
		(OPERATOR_RIGHT_ROTATE < operator_code))
	{
		status = EQ_STATUS_INVALID_OPERATOR;
		goto END;
	}

	* p_operator = (operator_t)operator_code;

END:
	return status;
}
/*** end of the file ***/
