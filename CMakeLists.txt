cmake_minimum_required(VERSION 3.10)

# Project name
project(Compiler)
include_directories(${CMAKE_SOURCE_DIR})

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Find Flex and Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# Generate lexer and parser
FLEX_TARGET(Lexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/y.tab.h)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

# Add source files
add_executable(compiler
        ${FLEX_Lexer_OUTPUTS}
        ${BISON_Parser_OUTPUTS}
        ast.c
        ast.h
)

# Include parser header
target_include_directories(compiler PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
