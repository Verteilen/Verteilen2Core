cmake_minimum_required(VERSION 3.31)
project(Vertelien2Core LANGUAGES CXX)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/ )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY obj/ )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY archive/ )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif ()

file(GLOB_RECURSE INCLUDE
        include/*.h
        include/*.hpp
)

file(GLOB_RECURSE SRC
        src/*.c
        src/*.cpp
)

add_library(Vertelien2Core ${INCLUDE} ${SRC})
set_target_properties(Vertelien2Core PROPERTIES LINKER_LANGUAGE CXX)

add_executable(Vertelien2Core_UUIDTest test/uuid.cpp)
target_include_directories(Vertelien2Core_UUIDTest PUBLIC "include")
set_target_properties(Vertelien2Core_UUIDTest PROPERTIES LINKER_LANGUAGE CXX)