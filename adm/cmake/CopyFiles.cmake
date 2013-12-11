# Script designed to be executed with 'cmake -P' that will copy a list of files
# to an output location. Accepts two -D arguments:
# - files_to_copy A list of files to copy
# - destination_directory The directory to copy the files into.

if( NOT files_to_copy )
  message( FATAL_ERROR "This script requires the variable 'files_to_copy' to be set" )
endif()

if( NOT destination_directory )
  message( FATAL_ERROR "This script requires the variable 'destination_directory' to be set" )
endif()

# Make sure the destination directory exists before we try the copy operation.
if( EXISTS ${destination_directory} )
  if( NOT IS_DIRECTORY ${destination_directory} )
    message( FATAL_ERROR
      "${destination_directory} exists but is not a directory." )
  endif()
else()
  file( MAKE_DIRECTORY ${destination_directory} )
endif()

list( LENGTH files_to_copy number_of_files )

message( STATUS "Copying ${number_of_files} files to ${destination_directory}" )

foreach( file ${files_to_copy} )
  execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy ${file} ${destination_directory}
  )
endforeach()
