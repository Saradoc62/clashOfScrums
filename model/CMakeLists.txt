project(clashOfScrums-model)

find_package(Boost COMPONENTS system filesystem)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message("Error ! Need Boost to compile ${PROJECT_NAME}")
endif()

file(GLOB_RECURSE SOURCES include/*.hxx src/*.cxx src/*.hxx)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories (${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_subdirectory(test)