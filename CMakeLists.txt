cmake_minimum_required(VERSION 3.10)

project(DeepTextReplace
        VERSION 0.0.1
        LANGUAGES CXX)

set(DeepTextReplace_NAME ${PROJECT_NAME})
set(DeepTextReplace_EXECUTABLE_NAME ${PROJECT_NAME}_cli)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-pthread")

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

find_package(Threads REQUIRED)

set(DeepTextReplace_INC
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Settings.hpp
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/EditFiles.hpp
    ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/Semaphore.hpp
)
source_group(include FILES ${DeepTextReplace_INC})
include_directories(${PROJECT_SOURCE_DIR}/include)

set(DeepTextReplace_SRC
    ${PROJECT_SOURCE_DIR}/src/Settings.cpp
    ${PROJECT_SOURCE_DIR}/src/EditFiles.cpp
)

source_group(src FILES ${DeepTextReplace_SRC})

add_executable(${DeepTextReplace_EXECUTABLE_NAME} ${PROJECT_SOURCE_DIR}/src/main.cpp)
add_library(${PROJECT_NAME} ${DeepTextReplace_SRC} ${DeepTextReplace_INC})

target_include_directories(${PROJECT_NAME}
    PRIVATE "${CMAKE_BINARY_DIR}"
)
target_link_libraries(${DeepTextReplace_EXECUTABLE_NAME} PRIVATE
    ${PROJECT_NAME}
)

# LINTS
set(DeepTextReplace_TIDY OFF)
find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
if (DeepTextReplace_TIDY)
    if(NOT CLANG_TIDY_COMMAND)
        message(WARNING "Could not find clang-tidy!")
        set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE)
    else()
        set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
        message(STATUS "clang-tidy enabled")
    endif()
else()
    message(STATUS "clang-tidy disabled ")
endif()

# valgrind
# ctest -T memcheck
find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
INCLUDE(Dart)

# CPACK
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

# TESTS
add_subdirectory(tests)
