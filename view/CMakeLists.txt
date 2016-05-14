project(clashOfScrums-view)

file(GLOB_RECURSE SOURCES include/*.hxx src/*.cxx src/*.hxx)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories (${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME})

add_subdirectory(test)