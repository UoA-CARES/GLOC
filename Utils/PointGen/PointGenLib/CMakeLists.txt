#--------------------------------------------------------
# CMake for generating the PointGenLib
#
# @author: Wild Boar
#
# Date Created: 2024-03-05
#--------------------------------------------------------

# Setup include directories
include_directories("../" "${LIBRARY_BASE}/NVLib")

# Create Library
add_library(PointGenLib STATIC
    ArgUtils.cpp
)
