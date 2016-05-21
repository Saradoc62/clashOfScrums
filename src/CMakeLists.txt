project(clashOfScrums)

find_package(Boost)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message("Error ! Need Boost to compile ${PROJECT_NAME}")
endif()

add_executable(${PROJECT_NAME} main.cxx)
target_link_libraries(${PROJECT_NAME} clashOfScrums-model clashOfScrums-view-shell)