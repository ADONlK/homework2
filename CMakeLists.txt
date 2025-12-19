cmake_minimum_required(VERSION 3.20)
project(homework2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(sparsevector
        SparseVector.cpp
)

target_include_directories(sparsevector PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)


add_executable(homework2
        main.cpp
)

target_link_libraries(homework2
        sparsevector
)


include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable(tests
        test.cpp
)

target_link_libraries(tests
        sparsevector
        gtest_main
)

add_test(NAME SparseVectorTests COMMAND tests)





