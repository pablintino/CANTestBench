
if(WIN32)

    find_path(CANLIB_INCLUDE_DIR NAMES canlib.h PATHS "C:\\Program Files (x86)\\Kvaser\\Canlib\\INC")
    find_library(CANLIB_LIBRARY NAMES canlib32 PATHS "C:\\Program Files (x86)\\Kvaser\\Canlib" PATH_SUFFIXES Lib/x64)
else()
    find_path(CANLIB_INCLUDE_DIR canlib.h)
    find_library(CANLIB_LIBRARY canlib)
endif()

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBXML2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Canlib  DEFAULT_MSG
        CANLIB_LIBRARY CANLIB_INCLUDE_DIR)

mark_as_advanced(CANLIB_INCLUDE_DIR CANLIB_LIBRARY)

set(CANLIB_LIBRARIES ${CANLIB_LIBRARY} )
set(CANLIB_INCLUDE_DIRS ${CANLIB_INCLUDE_DIR} )
