cmake_minimum_required(VERSION 3.10)

project(BioebString VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/icu4c")
endif()
message(STATUS "STATUS CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "STATUS ENV VCPKG_INSTALLATION_ROOT = $ENV{VCPKG_INSTALLATION_ROOT}")

if(MSVC)
  set(pdb_output_dir "${CMAKE_CURRENT_BINARY_DIR}/pdb-files")

  set(CMAKE_PDB_OUTPUT_DIRECTORY "${pdb_output_dir}")
  set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY "${pdb_output_dir}")

  get_cmake_property(is_multi GENERATOR_IS_MULTI_CONFIG)
  if(is_multi)
    set(config_suffix "$<CONFIG>")
  else()
    set(config_suffix "")
  endif()

  # Introduce variables:
  # * CMAKE_INSTALL_LIBDIR
  # * CMAKE_INSTALL_BINDIR
  include(GNUInstallDirs)

  if(BUILD_SHARED_LIBS)
    set(pdb_dst ${CMAKE_INSTALL_BINDIR})
  else()
    set(pdb_dst ${CMAKE_INSTALL_LIBDIR})
  endif()

  install(
      DIRECTORY "${pdb_output_dir}/${config_suffix}/"
      DESTINATION ${pdb_dst}
  )
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  list(APPEND CMAKE_PREFIX_PATH "/usr/local/opt/icu4c")
  message(STATUS "CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}")
endif()


find_package(ICU REQUIRED COMPONENTS uc io data i18n)

set(YAML_CPP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/extern/yaml-cpp/include/yaml-cpp")

add_library(${PROJECT_NAME} SHARED)
add_library(Bioeb::String ALIAS ${PROJECT_NAME})
target_sources(${PROJECT_NAME}
  PRIVATE
  src/BioebString.cpp
  )
target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")

target_link_libraries(${PROJECT_NAME} PRIVATE ${ICU_LIBRARIES})

set(generated_headers "${CMAKE_CURRENT_BINARY_DIR}/generated_headers")
set(generated_export "${generated_headers}/${PROJECT_NAME}/${PROJECT_NAME}_EXPORT.h")

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME ${generated_export}
  )

message(STATUS "${generated_headers}")

target_include_directories(${PROJECT_NAME}
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
    "$<BUILD_INTERFACE:${generated_headers}>"
  PRIVATE
    "${ICU_INCLUDE_DIR}"
  )

include(GNUInstallDirs)
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${version_config}" COMPATIBILITY SameMajorVersion
  )

configure_package_config_file(
  "cmake/config.cmake.in"
  "${project_config}"
  INSTALL_DESTINATION "${config_install_dir}"
  )

install(
  TARGETS ${PROJECT_NAME}
  EXPORT "${TARGETS_EXPORT_NAME}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  )

install(
  DIRECTORY "src"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING PATTERN "*.h"
  )

install(
  FILES "${generated_export}"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
  )

install(
  FILES "${project_config}" "${version_config}"
  DESTINATION "${config_install_dir}"
  )

install(
  EXPORT "${TARGETS_EXPORT_NAME}"
  NAMESPACE "${namespace}"
  DESTINATION "${config_install_dir}"
  )

# find_package(yaml-cpp CONFIG REQUIRED)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(YAML_CPP_INCLUDE_DIR "/usr/include/yaml-cpp")
  message(STATUS "YAML include: ${YAML_CPP_INCLUDE_DIR}")
endif()

# add_executable(stringTest
#   stringTest.cpp
#   )

# target_link_libraries(stringTest PRIVATE BioebString)
# target_link_libraries(stringTest PRIVATE ${ICU_LIBRARIES})
# target_link_libraries(stringTest PUBLIC yaml-cpp)

enable_testing()
set(OUTPUT_FILE_NAME "stringTest")
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
  set(OUTPUT_FILE_NAME "${OUTPUT_FILE_NAME}MacOS")
else()
  set(OUTPUT_FILE_NAME "${OUTPUT_FILE_NAME}${CMAKE_SYSTEM_NAME}")
endif()

# target_include_directories(stringTest PRIVATE "${PROJECT_BINARY_DIR}")
# target_include_directories(stringTest PRIVATE "${ICU_INCLUDE_DIR}")
# target_include_directories(stringTest PRIVATE "${YAML_CPP_INCLUDE_DIR}")

# add_test(NAME TokenTest1
#   COMMAND stringTest ${CMAKE_SOURCE_DIR}/testdata/tokenizer_tests.yml)
