# - Try to find ThreadPool
# Once done this will define
#  ThreadPool_FOUND - System has ThreadPool
#  ThreadPool_INCLUDE_DIRS - The ThreadPool include directories
#  ThreadPool_LIBRARIES - The libraries needed to use ThreadPool

find_path(ThreadPool_INCLUDE_DIR
	NAMES ThreadPool.hpp
	HINTS ${ThreadPool_ROOT}/include
	DOC "The ThreadPool include directory"
)

find_library(ThreadPool_LIBRARY
	NAMES ThreadPool
	HINTS ${ThreadPool_ROOT}/lib
	DOC "The ThreadPool library"
)

if(ThreadPool_INCLUDE_DIR AND ThreadPool_LIBRARY)
	set(ThreadPool_FOUND 1)
endif()

# Handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE if all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ThreadPool DEFAULT_MSG ThreadPool_INCLUDE_DIR ThreadPool_LIBRARY)

if(ThreadPool_FOUND)
	set(ThreadPool_LIBRARIES ${ThreadPool_LIBRARY} )
	set(ThreadPool_INCLUDE_DIRS ${ThreadPool_INCLUDE_DIR} )
endif()

# Tell cmake ThreadPools to ignore the "local" variables
mark_as_advanced(ThreadPool_INCLUDE_DIR ThreadPool_LIBRARY)
