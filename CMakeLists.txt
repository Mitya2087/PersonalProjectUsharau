cmake_minimum_required(VERSION 3.14)
project(ExtendedCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src/backend)
include_directories(${CMAKE_SOURCE_DIR}/src/cli)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)

# Backend source files (shared logic)
set(BACKEND_SOURCES
    src/backend/MathUtils.cpp
    src/backend/ExpressionEvaluator.cpp
    src/backend/History.cpp
    src/backend/Sorter.cpp
    src/backend/CalculatorEngine.cpp
)

# Utils sources
set(UTILS_SOURCES
    src/utils/ArgumentParser.cpp
)

# Console (CLI) calculator executable
set(CLI_SOURCES
    src/cli/Modes.cpp
    src/cli/CalculatorApp.cpp
    src/cli/DateMode.cpp
    src/cli/main_cli.cpp
)

add_executable(calculator
    ${CLI_SOURCES}
    ${BACKEND_SOURCES}
    ${UTILS_SOURCES}
)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executable
add_executable(calculator_tests
    src/tests/test_calculator.cpp
    ${BACKEND_SOURCES}
    ${UTILS_SOURCES}
    src/cli/Modes.cpp
    src/cli/CalculatorApp.cpp
    src/cli/DateMode.cpp
)

target_link_libraries(calculator_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(calculator_tests)
