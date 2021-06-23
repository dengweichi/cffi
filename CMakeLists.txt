cmake_minimum_required(VERSION 3.16)
project(lib-cffi)

SET(ENABLE_TESTS_MODE OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

# 只支持linux系统
if(NOT(CMAKE_SYSTEM_NAME STREQUAL "Linux"))
    message(SEND_ERROR "only support linux system")
endif()

# 只支持64位系统
if(NOT(CMAKE_SIZEOF_VOID_P EQUAL 8))
    message(SEND_ERROR "only support 64 bits")
endif()

# 只支持x86-64位处理器
if(NOT(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64"))
    message(SEND_ERROR "only support x86-64")
endif()

enable_language(ASM)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -ldl")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ldl")

if(ENABLE_TESTS_MODE)
    set(googleTestDir ./googletest)
    add_subdirectory(${googleTestDir})
    include_directories(${googleTestDir}/googletest/include)
    include_directories(${googleTestDir}/googlemock/include)

    add_executable(${PROJECT_NAME} ./test/main.cpp ./src/cffi.c ./src/cffi.s ./test/test_call.cpp)

    target_link_libraries(${PROJECT_NAME} gtest gtest_main)
    target_link_libraries(${PROJECT_NAME} gmock gmock_main)
    # 必须手动链接
    target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
    file(COPY ./test/bar.so DESTINATION ${CMAKE_BINARY_DIR})
else()
    add_library(${PROJECT_NAME} STATIC ./src/cffi.c ./src/cffi.s)
endif()

