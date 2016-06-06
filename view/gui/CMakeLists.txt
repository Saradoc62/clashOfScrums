project(clashOfScrums-view-gui)

file(GLOB_RECURSE SOURCES include/*.hxx src/*.cxx src/*.hxx)

find_package(Qt4 REQUIRED)
if(Qt4_FOUND)
    include_directories(${QT_INCLUDE_DIRS})
    include(${QT_USE_FILE})
	add_definitions(${QT_DEFINITIONS})
	set(CMAKE_AUTOUIC ON)
	set(CMAKE_AUTOMOC ON)
else()
    message("Error ! Need Qt to compile ${PROJECT_NAME}")
endif()

#add clashOfScrums-model's include directory
include_directories(${clashOfScrums-model_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories (${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})

# Expose clashOfScrums-view-gui's public includes (including Qt transitively) to other
# subprojects through cache variable.
set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
                                 ${QT_USE_FILE}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
