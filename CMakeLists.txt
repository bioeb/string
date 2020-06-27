cmake_minimum_required(VERSION 3.10)

project(StringTest VERSION 1.0)

add_subdirectory(extern/yaml-cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/icu4c")
endif()

find_package(ICU REQUIRED COMPONENTS uc io)

set(YAML_CPP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/extern/yaml-cpp/include/yaml-cpp")

add_executable(stringTest
  stringTest.cpp
  BioebString.cpp
  BioebString.h
  )

target_include_directories(stringTest PRIVATE "${PROJECT_BINARY_DIR}")
target_include_directories(stringTest PRIVATE "submodules")
target_include_directories(stringTest PRIVATE "${ICU_INCLUDE_DIR}")
target_include_directories(stringTest PRIVATE "${YAML_CPP_INCLUDE_DIR}")

target_link_libraries(stringTest ${ICU_LIBRARIES})
target_link_libraries(stringTest yaml-cpp)

enable_testing()

add_test(NAME TokenTest1
  COMMAND stringTest ${CMAKE_SOURCE_DIR}/testdata/tokenizer_tests.yml)
