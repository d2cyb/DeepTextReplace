set(NOD_BENCHMARK_NAME ${NOD_NAME}_bench)

set(NOD_BENCHMARK_SRC
    ${PROJECT_SOURCE_DIR}/tests/perf/example.cpp
)

set(BENCHMARK_ENABLE_TESTING off)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE INTERNAL "")

add_executable(${NOD_BENCHMARK_NAME} ${NOD_BENCHMARK_SRC})
target_link_libraries(${NOD_BENCHMARK_NAME}
    benchmark
    benchmark_main
    ${CMAKE_THREAD_LIBS_INIT}
    ${PROJECT_NAME}
)
