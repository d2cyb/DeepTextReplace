set(CMAKE_AUTOMOCK ON)

set(DeepTextReplace_TESTS_NAME ${DeepTextReplace_NAME}_unit)

set(DeepTextReplace_TEST_SRC
    ${PROJECT_SOURCE_DIR}/tests/unit/Settings_test.cpp
    ${PROJECT_SOURCE_DIR}/tests/unit/EditFiles_test.cpp
)

set(DeepTextReplace_GMOCK_DIR ${CMAKE_SOURCE_DIR}/3rd-party/googletest/googlemock)
set(DeepTextReplace_GTEST_DIR ${CMAKE_SOURCE_DIR}/3rd-party/googletest/googletest)

include_directories(
    PRIVATE ${CMAKE_SOURCE_DIR}/include/${DeepTextReplace_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src/
    PRIVATE ${DeepTextReplace_GMOCK_DIR}
    PRIVATE ${DeepTextReplace_GMOCK_DIR}/include
    PRIVATE ${DeepTextReplace_GTEST_DIR}
    PRIVATE ${DeepTextReplace_GTEST_DIR}/include
)

enable_testing()
add_test(NAME ${DeepTextReplace_TESTS_NAME}
    COMMAND $<TARGET_FILE:${DeepTextReplace_TESTS_NAME}>
)
add_executable(${DeepTextReplace_TESTS_NAME} ${DeepTextReplace_TEST_SRC})
target_link_libraries(${DeepTextReplace_TESTS_NAME}
    gtest
    gtest_main
    ${CMAKE_THREAD_LIBS_INIT}
    ${PROJECT_NAME}
)
