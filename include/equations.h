/** @file equations.h
 *
 * @brief Defines functions for equations.c
 *
 */

#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <stdint.h>
#include <stdio.h>
#include "equation_status.h"

#define PADDING_SIZE 10

typedef struct
{
	int64_t first_operand;
	uint8_t operator;
	int64_t second_operand;
} serialized_eq_t;

typedef struct 
{
	uint32_t id;
	uint8_t flag;
	serialized_eq_t equation;
	uint8_t padding[PADDING_SIZE];
} equation_t;

typedef struct
{
	uint32_t id;
	uint8_t flags;
	uint8_t type;
	int64_t solution;
} solved_t;

equation_status_t read_equation(FILE * p_file, equation_t * p_equation);

equation_status_t calculate_equation(const equation_t * p_equation,
									 solved_t * p_solved);

#endif

/*** end of the file ***/
