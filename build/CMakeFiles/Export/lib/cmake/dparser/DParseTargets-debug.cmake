#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dparser::make_dparser" for configuration "Debug"
set_property(TARGET dparser::make_dparser APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(dparser::make_dparser PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/make_dparser"
  )

list(APPEND _IMPORT_CHECK_TARGETS dparser::make_dparser )
list(APPEND _IMPORT_CHECK_FILES_FOR_dparser::make_dparser "${_IMPORT_PREFIX}/bin/make_dparser" )

# Import target "dparser::sample_parser" for configuration "Debug"
set_property(TARGET dparser::sample_parser APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(dparser::sample_parser PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/sample_parser"
  )

list(APPEND _IMPORT_CHECK_TARGETS dparser::sample_parser )
list(APPEND _IMPORT_CHECK_FILES_FOR_dparser::sample_parser "${_IMPORT_PREFIX}/bin/sample_parser" )

# Import target "dparser::test_parser" for configuration "Debug"
set_property(TARGET dparser::test_parser APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(dparser::test_parser PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/test_parser"
  )

list(APPEND _IMPORT_CHECK_TARGETS dparser::test_parser )
list(APPEND _IMPORT_CHECK_FILES_FOR_dparser::test_parser "${_IMPORT_PREFIX}/bin/test_parser" )

# Import target "dparser::mkdparse" for configuration "Debug"
set_property(TARGET dparser::mkdparse APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(dparser::mkdparse PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libmkdparse.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS dparser::mkdparse )
list(APPEND _IMPORT_CHECK_FILES_FOR_dparser::mkdparse "${_IMPORT_PREFIX}/lib/libmkdparse.a" )

# Import target "dparser::dparse" for configuration "Debug"
set_property(TARGET dparser::dparse APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(dparser::dparse PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libdparse.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS dparser::dparse )
list(APPEND _IMPORT_CHECK_FILES_FOR_dparser::dparse "${_IMPORT_PREFIX}/lib/libdparse.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
