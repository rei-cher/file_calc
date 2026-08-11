cmake_minimum_required(VERSION 3.22)

project(
    file_calc
    VERSION 1.0.0
    LANGUAGES C)

# cmake-format: off
set(CMAKE_C_STANDARD          17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS        OFF)

# Define executable name
set(EXECUTABLE_NAME  filecalc)

add_executable(
	${EXECUTABLE_NAME}
	src/main.c
	src/calculator.c
	src/directories.c
	src/files.c
	src/equations.c
	src/calc_operations.c
	src/bit_operations.c
	src/errors.c
)

target_include_directories(
	${EXECUTABLE_NAME}
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)

target_compile_options(
	${EXECUTABLE_NAME}
	PRIVATE
		-Wall
		-Wextra
		-Wpedantic
)
