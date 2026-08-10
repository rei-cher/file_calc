/** @file equations.h
 *
 * @brief Defines functions for equations.c
 *
 */

#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <stdint.h>
#include <stdio.h>

#include "calculator.h"
#include "equation_status.h"

#define PADDING_SIZE 10

/**
 * @brief Structure for serialized equation
 * 		  operand -> 8 bytes
 * 		  operator -> 1 byte
 * 		  operand -> 8 bytes
 */
typedef struct
{
	value_t first_operand;
	uint8_t operator;
	value_t second_operand;
} serialized_eq_t;

/**
 * @brief Structure for unsolved equation
 * 		  equation id -> 4 bytes
 * 		  flag -> 1 bute
 * 		  equation -> 17 bytes
 * 		  padding -> 10 bytes
 */
typedef struct 
{
	uint32_t id;
	uint8_t flag;
	serialized_eq_t equation;
	uint8_t padding[PADDING_SIZE];
} equation_t;

/**
 * @brief Structure for solved equation
 * 		  equation id -> 4 bytes
 * 		  flags -> 1 byte (solved/not solved)
 * 		  type -> 1 byte (int64_t/uint64_t)
 * 		  solution -> 8 bytes
 */
typedef struct
{
	uint32_t id;
	uint8_t flag;
	uint8_t type;
	value_t solution;
} solved_t;

/**
 * @brief Accepting input file, output file, and number of equations (from
 * 		  file header). Iterating over each equation:
 * 		  	validating equation format
 * 		  	if validates -> copies id equation 
 *			solves equation
 *			after solving, writes it into the output file
 *
 * @param p_input_file
 * @param P_output_file
 * @param num_of_eq
 *
 * @return Equation status
 */
equation_status_t calculate_equations(FILE * p_input_file, 
									  FILE * P_output_file,
									  uint64_t num_of_eq);

#endif

/*** end of the file ***/
