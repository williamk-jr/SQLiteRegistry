# - Try to find Sqlite3
# Once done this will define
#
#  SQLITE3_FOUND - system has Sqlite3
#  SQLITE3_INCLUDE_DIRS - the Sqlite3 include directory
#  SQLITE3_LIBRARIES - Link these to use Sqlite3
#  SQLITE3_DEFINITIONS - Compiler switches required for using Sqlite3
#  SQLITE3_VERSION - Sqlite3 version

if (SQLITE3_LIBRARIES AND SQLITE3_INCLUDE_DIRS) # Check if lib has already been found.
  set(SQLITE3_FOUND TRUE)
else()
  if (NOT WIN32) # If not windows, try using pkg_config.
    find_package(PkgConfig)
    if(PKG_CONFIG_FOUND)
      pkg_check_modules(PC_SQLITE3 sqlite3)
    endif()
  endif()

  if (PC_SQLITE3_FOUND)
    set(SQLITE3_INCLUDE_DIRS ${PC_SQLITE3_INCLUDE_DIRS})
    set(SQLITE3_LIBRARIES ${PC_SQLITE3_LIBRARIES})
    set(SQLITE3_FOUND TRUE)
  else() # If pkg_config fails, manually search standard locations.
    find_path(SQLITE3_INCLUDE_DIR
      NAMES
        sqlite3.h
      PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include
    )

    find_library(SQLITE3_LIBRARY
      NAMES
        sqlite3
      PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        /sw/lib
    )

    find_path(SQLITE3_LIBRARY_DIR
      NAMES
        sqlite3
      PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        /sw/lib
    )

    set(SQLITE3_INCLUDE_DIRS ${SQLITE3_INCLUDE_DIR})
    set(SQLITE3_LIBRARIES ${SQLITE3_LIBRARY})
    set(SQLITE3_LIBRARY_DIRS ${SQLITE3_LIBRARY_DIR})

    if (SQLITE3_INCLUDE_DIRS AND SQLITE3_LIBRARIES)
       set(SQLITE3_FOUND TRUE)
    endif()

    if (SQLITE3_FOUND) # Logging
      if (NOT Sqlite3_FIND_QUIETLY)
        message(STATUS "Found Sqlite3: ${SQLITE3_LIBRARIES}")
      endif()
    else()
      if (Sqlite3_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find Sqlite3")
      endif()
    endif()
  endif()

  # show the PORTAUDIO_INCLUDE_DIRS and PORTAUDIO_LIBRARIES variables only in the advanced view
  mark_as_advanced(SQLITE3_INCLUDE_DIRS SQLITE3_LIBRARIES)
endif()