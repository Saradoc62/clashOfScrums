project(clashOfScrums-model-test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message("Error ! Need Boost to compile ${PROJECT_NAME}")
endif()

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(deckTest deckTest.cxx)
target_link_libraries(deckTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} clashOfScrums-model)

add_executable(boardTest boardTest.cxx)
target_link_libraries(boardTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} clashOfScrums-model)

add_executable(playerContextTest playerContextTest.cxx)
target_link_libraries(playerContextTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} clashOfScrums-model)
