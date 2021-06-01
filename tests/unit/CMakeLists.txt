set(CMAKE_AUTOMOCK ON)

set(NOD_TESTS_NAME ${NOD_NAME}_unit)

set(NOD_TEST_SRC
    ${PROJECT_SOURCE_DIR}/tests/unit/example_test.cpp
)

set(NOD_GMOCK_DIR ${CMAKE_SOURCE_DIR}/3rd-party/googletest/googlemock)
set(NOD_GTEST_DIR ${CMAKE_SOURCE_DIR}/3rd-party/googletest/googletest)


include_directories(
    PRIVATE ${CMAKE_SOURCE_DIR}/include/${NOD_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src/
    PRIVATE ${NOD_GMOCK_DIR}
    PRIVATE ${NOD_GMOCK_DIR}/include
    PRIVATE ${NOD_GTEST_DIR}
    PRIVATE ${NOD_GTEST_DIR}/include
)

enable_testing()
add_test(NAME ${NOD_TESTS_NAME}
    COMMAND $<TARGET_FILE:${NOD_TESTS_NAME}>
)
add_executable(${NOD_TESTS_NAME} ${NOD_TEST_SRC})
target_link_libraries(${NOD_TESTS_NAME}
    gtest
    gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
    ${PROJECT_NAME}
)
