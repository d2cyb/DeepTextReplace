set(DeepTextReplace_BENCHMARK_NAME ${DeepTextReplace_NAME}_bench)

set(DeepTextReplace_BENCHMARK_SRC
    ${PROJECT_SOURCE_DIR}/tests/perf/example.cpp
)

set(BENCHMARK_ENABLE_TESTING off)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE INTERNAL "")

add_executable(${DeepTextReplace_BENCHMARK_NAME} ${DeepTextReplace_BENCHMARK_SRC})
target_link_libraries(${DeepTextReplace_BENCHMARK_NAME}
    benchmark
    benchmark_main
    ${CMAKE_THREAD_LIBS_INIT}
    ${PROJECT_NAME}
)
