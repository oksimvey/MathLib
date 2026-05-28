cmake_minimum_required(VERSION 3.20)  # 3.20+ tem melhor suporte C++23
project(MathLib LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)


add_executable(MathLib ${SRC_FILES}
        src/main/marco/mathlib/math/number/cas/nodes/SymbolicExpression.h
        src/main/marco/mathlib/math/number/cas/parser/NumericExpressionParser.h
        src/main/marco/mathlib/math/number/cas/parser/LinearAlgebraParser.h
        src/main/marco/mathlib/math/number/cas/parser/CalculusParser.h
        src/main/marco/mathlib/math/number/cas/parser/FullParser.h
        src/main/marco/mathlib/math/number/cas/parser/ParserUtils.h
        src/main/marco/mathlib/math/number/cas/nodes/SymbolicConstant.h
        src/main/marco/mathlib/math/number/cas/simplifier/NumericSimplifier.h
        src/main/marco/mathlib/math/number/cas/simplifier/ExpressionSimplifier.h
        src/main/marco/mathlib/math/number/cas/writter/NumericWritter.h)


target_include_directories(MathLib PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(MathLib PRIVATE
    -O3



    -Wall
    -Wextra
    -Wpedantic



    -Wshadow
    -Wconversion
    -Wsign-conversion



    -Wcast-qual
    -Wdiscarded-qualifiers
    -Wignored-qualifiers
    -Wwrite-strings



    -Wnon-virtual-dtor
    -Woverloaded-virtual
    -Wold-style-cast



    -Wswitch-enum
    -Wswitch-default
    -Wunused-parameter
)