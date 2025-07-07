cmake_minimum_required(VERSION 3.31)
project(Vertelien2Core LANGUAGES CXX)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/ )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY obj/ )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY archive/ )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(MYLIB "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif ()

file(GLOB_RECURSE INCLUDE
        include/**.h
        include/**.hpp
)

file(GLOB_RECURSE SRC
        src/**.c
        src/**.cpp
)

add_library(Vertelien2Core ${SRC})
target_include_directories(Vertelien2Core PUBLIC "include")
set_target_properties(Vertelien2Core PROPERTIES LINKER_LANGUAGE CXX)

enable_testing()

add_executable(Vertelien2Core_UUIDTest test/uuid.cpp)
target_include_directories(Vertelien2Core_UUIDTest PUBLIC "include")
target_link_directories(Vertelien2Core_UUIDTest PUBLIC "${MYLIB}")
target_link_libraries(Vertelien2Core_UUIDTest "libVertelien2Core.a")
add_test(NAME Vertelien2Core_UUIDTest COMMAND Vertelien2Core_UUIDTest)

add_executable(Vertelien2Core_Serialization_JobTest test/serialization/job.cpp)
target_include_directories(Vertelien2Core_Serialization_JobTest PUBLIC "include")
target_link_directories(Vertelien2Core_Serialization_JobTest PUBLIC "${MYLIB}")
target_link_libraries(Vertelien2Core_Serialization_JobTest "libVertelien2Core.a")
add_test(NAME Vertelien2Core_Serialization_JobTest COMMAND Vertelien2Core_Serialization_JobTest)

add_executable(Vertelien2Core_Serialization_TaskTest test/serialization/task.cpp)
target_include_directories(Vertelien2Core_Serialization_TaskTest PUBLIC "include")
target_link_directories(Vertelien2Core_Serialization_TaskTest PUBLIC "${MYLIB}")
target_link_libraries(Vertelien2Core_Serialization_TaskTest "libVertelien2Core.a")
add_test(NAME Vertelien2Core_Serialization_TaskTest COMMAND Vertelien2Core_Serialization_TaskTest)

add_executable(Vertelien2Core_Serialization_ProjectTest test/serialization/project.cpp)
target_include_directories(Vertelien2Core_Serialization_ProjectTest PUBLIC "include")
target_link_directories(Vertelien2Core_Serialization_ProjectTest PUBLIC "${MYLIB}")
target_link_libraries(Vertelien2Core_Serialization_ProjectTest "libVertelien2Core.a")
add_test(NAME Vertelien2Core_Serialization_ProjectTest COMMAND Vertelien2Core_Serialization_ProjectTest)