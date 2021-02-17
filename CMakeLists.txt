cmake_minimum_required(VERSION 3.13)
if(DEFINED ENV{VCPKG_INSTALLATION_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "")
endif()

project(BioebString VERSION 1.0.0.0)

add_subdirectory(extern/yaml-cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/icu4c")
endif()
message(STATUS "STATUS CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "STATUS ENV VCPKG_INSTALLATION_ROOT = $ENV{VCPKG_INSTALLATION_ROOT}")
find_package(ICU REQUIRED COMPONENTS uc io)

set(YAML_CPP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/extern/yaml-cpp/include/yaml-cpp")

add_library(BioebString SHARED)
add_library(Bioeb::String ALIAS BioebString)
target_sources(BioebString
  PRIVATE
  BioebString.cpp
  )

option(BUILD_SHARED_LIBS "Build shaded library" ON)
include(GenerateExportHeader)
generate_export_header(BioebString
  EXPORT_MACRO_NAME BioebString_API
  EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/bioebstring/common.h
  )

target_include_directories(BioebString
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
  )

set_target_properties(BioebString PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  )

include(GNUInstallDirs)
install(TARGETS BioebString
  EXPORT BioebString-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${LIBLEGACY_INCLUDE_DIRS}
  )
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/bioebstring
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
install(EXPORT BioebString-targets
  FILE BioebString-targets.cmake
  NAMESPACE Bieoeb::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BioebString
  )

include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/BioebString-config.cmake.in
  ${CMAKE_BINARY_DIR}/cmake/BioebString-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BioebString
  )
write_basic_package_version_file(
  ${CMAKE_BINARY_DIR}/cmake/BioebString-config-version.cmake
  VERSION ${BioebString_VERSION}
  COMPATIBILITY AnyNewerVersion
  )
install(
  FILES
  ${CMAKE_BINARY_DIR}/cmake/BioebString-config.cmake
  ${CMAKE_BINARY_DIR}/cmake/BioebString-config-version.cmake
  DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/cmake/BioebString
  )
export(EXPORT BioebString-targets
  FILE ${CMAKE_BINARY_DIR}/cmake/BioebString-targets.cmake
  NAMESPACE Bioeb::
  )

#find_package(yaml-cpp REQUIRED)
# if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
#   set(YAML_CPP_INCLUDE_DIR "/usr/include/yaml-cpp")
# endif()

# include(FetchContent)
# set(YAML_BUILD_SHARED_LIBS ON CACHE INTERNAL "")
# FetchContent_Declare(
#   yaml-cpp
#   GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
#   GIT_SHALLOW ON
#   GIT_TAG a6bbe0e50ac4074f0b9b44188c28cf00caf1a723
#   )
# FetchContent_GetProperties(yaml-cpp)
# if(NOT yaml-cpp_POPULATED)
#   message(STATUS "Populating yaml-cpp...")
#   FetchContent_Populate(yaml-cpp)
#   set(YAML_CPP_BUILD_TESTS OFF)
#   add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
#   message(STATUS "Done.")
# endif()
# include_directories(BEFORE SYSTEM ${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR}/include)
# add_executable(stringTest
#   stringTest.cpp
# #   BioebString.cpp
# #   BioebString.h
# )
# target_include_directories(stringTest PRIVATE "${PROJECT_BINARY_DIR}")
# target_include_directories(stringTest PRIVATE "${ICU_INCLUDE_DIR}")
# target_include_directories(stringTest PRIVATE "${YAML_CPP_INCLUDE_DIR}")
# message(STATUS "YAML include: ${YAML_CPP_INCLUDE_DIR}")
# message(STATUS "YAML libraries: ${YAML_CPP_LIBRARIES}")

# target_link_libraries(stringTest PRIVATE Bioeb::String)
# target_link_libraries(stringTest PRIVATE ${ICU_LIBRARIES})
# target_link_libraries(stringTest PUBLIC yaml-cpp::yaml-cpp)

# enable_testing()
set(OUTPUT_FILE_NAME "stringTest")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(OUTPUT_FILE_NAME "${OUTPUT_FILE_NAME}MacOS")
else()
  set(OUTPUT_FILE_NAME "${OUTPUT_FILE_NAME}${CMAKE_SYSTEM_NAME}")
endif()

set_target_properties(stringTest PROPERTIES OUTPUT_NAME ${OUTPUT_FILE_NAME})
target_include_directories(stringTest PRIVATE "${PROJECT_BINARY_DIR}")
target_include_directories(stringTest PRIVATE "submodules")
target_include_directories(stringTest PRIVATE "${ICU_INCLUDE_DIR}")
target_include_directories(stringTest PRIVATE "${YAML_CPP_INCLUDE_DIR}")

target_link_libraries(stringTest ${ICU_LIBRARIES})
target_link_libraries(stringTest yaml-cpp)

# add_test(NAME TokenTest1
#   COMMAND stringTest ${CMAKE_SOURCE_DIR}/testdata/tokenizer_tests.yml)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
