project(clashOfScrums-view-shell)

file(GLOB_RECURSE SOURCES include/*.hxx src/*.cxx src/*.hxx)

#add clashOfScrums-model's include directory
include_directories(${clashOfScrums-model_INCLUDE_DIRS})

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories (${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME})

add_subdirectory(test)
