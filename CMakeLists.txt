cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

#manage resources in project
set(RESOURCES_PATH ${CMAKE_SOURCE_DIR}/resources/)
configure_file (
  ${RESOURCES_PATH}/configuration.h.in
  ${EXECUTABLE_OUTPUT_PATH}/configuration.h
)
include_directories(${EXECUTABLE_OUTPUT_PATH})

# Clean target of unit coverage
set(INPUT_CMAKE_DIR ${CMAKE_SOURCE_DIR}/cmake)
set(OUTPUT_CMAKE_DIR ${CMAKE_BINARY_DIR}/cmake)
configure_file(${INPUT_CMAKE_DIR}/coverage-clean.cmake.in ${OUTPUT_CMAKE_DIR}/coverage-clean.cmake IMMEDIATE @ONLY)
add_custom_target(coverage-clean COMMAND "${CMAKE_COMMAND}" -P ${OUTPUT_CMAKE_DIR}/coverage-clean.cmake)

add_subdirectory(src)
add_subdirectory(model)
add_subdirectory(view)

enable_testing()
add_test(NAME deckTest COMMAND deckTest)
add_test(NAME boardTest COMMAND boardTest)
add_test(NAME playerContextTest COMMAND playerContextTest)
add_test(NAME dummyTestView COMMAND dummyTestView)
