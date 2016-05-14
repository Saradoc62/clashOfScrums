cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(src)
add_subdirectory(model)
add_subdirectory(view)

enable_testing()
add_test(NAME dummyTestModel COMMAND dummyTestModel)
add_test(NAME deckTest COMMAND deckTest)
add_test(NAME dummyTestView COMMAND dummyTestView)
