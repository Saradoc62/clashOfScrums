project(clashOfScrums)

find_package(Qt4 REQUIRED)
if(Qt4_FOUND)
    include(${QT_USE_FILE})
else()
    message("Error ! Need Qt to compile ${PROJECT_NAME}")
endif()

add_executable(${PROJECT_NAME} main.cxx)
target_link_libraries(${PROJECT_NAME} clashOfScrums-model clashOfScrums-view-shell clashOfScrums-view-gui)