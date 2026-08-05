/** @file equations.c
 *
 * @brief Defines logical operations for equiation process
 *
 */

#include "equations.h"
#include "equation_status.h"

equation_status_t read_eqation(FILE * p_file, equation_t * p_equation)
{
	equation_status_t status = EQ_STATUS_OK;

	if ((NULL == p_file) ||
		(NULL == p_equation))
	{
		status = EQ_STATUS_NULL_POINTER;
		goto END;
	}

	if (1U != fread(&p_equation->id, sizeof(p_equation->id), 1U, p_file))
	{
		status = EQ_STATUS_READ_ERROR;
		goto END;
	}

END:
	return status;	
}

/*** end of the file ***/
