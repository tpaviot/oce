# This example shows how to use find_package(OCE) by specifying
# a list of toolkits.
# If a toolkit is missing or if OCE is not found, a fatal error
# is thrown, we do not try to find an Opencascade installation.

cmake_minimum_required(VERSION 2.6)

find_package(OCE REQUIRED COMPONENTS TKPrim)

# Include files reside in ${OCE_INCLUDE_DIRS};
include_directories(${OCE_INCLUDE_DIRS})

# We do not need library path, they will be automatically imported.
add_executable(computeSurface computeSurface.cpp)
target_link_libraries(computeSurface TKPrim)

