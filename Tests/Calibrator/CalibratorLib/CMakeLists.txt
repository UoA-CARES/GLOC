#--------------------------------------------------------
# CMake for generating the CalibratorLib
#
# @author: Wild Boar
#
# Date Created: 2024-05-28
#--------------------------------------------------------

# Setup include directories
include_directories("../" "${LIBRARY_BASE}/NVLib")

# Create Library
add_library (CalibratorLib STATIC
	ArgUtils.cpp
	GridPoints.cpp
)