project(clashOfScrums-view-test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message("Error ! Need Boost to compile ${PROJECT_NAME}")
endif()

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(dummyViewTest test.cxx)
target_link_libraries(dummyViewTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})