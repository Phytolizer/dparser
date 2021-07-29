cmake_minimum_required(VERSION 3.0)

project(dparser VERSION 1.30.0.0)

include(CPack)
include(GenerateExportHeader)
include(CMakePackageConfigHelpers)

option(DEBUG "DEBUG" FALSE)
option(OPTIMIZE "OPTIMIZE" TRUE)
option(PROFILE "PROFILE" FALSE)
option(USE_GC "USE_GC" FALSE)
option(LEAK_DETECT "LEAK_DETECT" FALSE)
option(USE_FREELISTS "OPTIMIZE" TRUE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=write-strings")
set(CMAKE_CXX_CLANG_TIDY clang-tidy)

add_executable(make_dparser
  make_dparser.cpp
  version.cpp
)
find_package(fmt REQUIRED)
target_compile_features(make_dparser PRIVATE cxx_std_20)
target_link_libraries(make_dparser PRIVATE fmt::fmt)

add_executable(sample_parser
  sample_parser.cpp
  sample.g
  ${CMAKE_CURRENT_BINARY_DIR}/sample.g.d_parser.cpp
)
add_dependencies(sample_parser make_dparser)
target_compile_features(sample_parser PRIVATE cxx_std_20)
target_link_libraries(sample_parser PRIVATE fmt::fmt)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/sample.g.d_parser.cpp
  DEPENDS make_dparser sample.g
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} VERBATIM
  COMMAND $<TARGET_FILE:make_dparser> ${CMAKE_CURRENT_SOURCE_DIR}/sample.g -o ${CMAKE_CURRENT_BINARY_DIR}/sample.g.d_parser.cpp
)

add_executable(test_parser
  test_parser.cpp
  my.g
  ${CMAKE_CURRENT_BINARY_DIR}/my.g.d_parser.cpp
)
add_dependencies(test_parser make_dparser)
target_compile_features(test_parser PRIVATE cxx_std_20)
target_link_libraries(test_parser PRIVATE fmt::fmt)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/my.g.d_parser.cpp
  DEPENDS make_dparser my.g
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} VERBATIM
  COMMAND $<TARGET_FILE:make_dparser> ${CMAKE_CURRENT_SOURCE_DIR}/my.g -o ${CMAKE_CURRENT_BINARY_DIR}/my.g.d_parser.cpp
)

add_library(mkdparse STATIC
  mkdparse.cpp
  write_tables.cpp
  grammar.g.cpp
  gram.cpp
  lex.cpp
  lr.cpp
  version.cpp
)
target_compile_features(mkdparse PUBLIC cxx_std_20)
target_link_libraries(mkdparse PUBLIC fmt::fmt)

add_library(dparse STATIC
  arg.cpp
  parse.cpp
  scan.cpp
  dsymtab.cpp
  util.cpp
  read_binary.cpp
  dparse_tree.cpp
  version.cpp
)
target_compile_features(dparse PUBLIC cxx_std_20)
target_link_libraries(dparse PUBLIC fmt::fmt)

target_link_libraries(make_dparser PRIVATE mkdparse dparse)
target_link_libraries(sample_parser PRIVATE mkdparse dparse)
target_link_libraries(test_parser PRIVATE mkdparse dparse)

macro(d_comple_defs _target)
  target_compile_definitions(${_target} PRIVATE
    -DD_MAJOR_VERSION=${PROJECT_VERSION_MAJOR}
    -DD_MINOR_VERSION=${PROJECT_VERSION_MINOR}
  )
  if(${DEBUG})
    target_compile_definitions(${_target} PRIVATE -DDEBUG -D_DEBUG)
  endif()
  if(${USE_GC})
    target_compile_definitions(${_target} PRIVATE -DUSE_GC)
  endif()
  if(${LEAK_DETECT})
    target_compile_definitions(${_target} PRIVATE -DLEAK_DETECT)
  endif()
  target_include_directories(${_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endmacro()

d_comple_defs(make_dparser)
d_comple_defs(sample_parser)
d_comple_defs(test_parser)
d_comple_defs(mkdparse)
d_comple_defs(dparse)

generate_export_header(dparse)

install(
  TARGETS make_dparser sample_parser test_parser
  EXPORT DParseTargets
  RUNTIME DESTINATION bin
)
install(
  TARGETS mkdparse dparse
  EXPORT DParseTargets
  ARCHIVE DESTINATION lib
)
install(
  FILES d.h dparse.h
  DESTINATION include
)
configure_file(dparser-config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/dparser-config.cmake @ONLY)
configure_file(dparser-generate.cmake ${CMAKE_CURRENT_BINARY_DIR}/dparser-generate.cmake COPYONLY)
install(
  FILES dparser-generate.cmake ${CMAKE_CURRENT_BINARY_DIR}/dparser-config.cmake
  DESTINATION lib/cmake/dparser
)


write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/DParseVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT DParseTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/DParseTargets.cmake"
  NAMESPACE dparser::
)

install(
  EXPORT DParseTargets
  FILE DParseTargets.cmake
  NAMESPACE dparser::
  DESTINATION lib/cmake/dparser
)
