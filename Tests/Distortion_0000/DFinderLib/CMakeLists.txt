#--------------------------------------------------------
# CMake for generating the DFinderLib
#
# @author: Wild Boar
#
# Date Created: 2024-04-10
#--------------------------------------------------------

# Setup include directories
include_directories("../" "${LIBRARY_BASE}/NVLib")

# Create Library
add_library (DFinderLib STATIC
	ArgUtils.cpp
	Grid.cpp
	PointLoader.cpp
	Homography.cpp
	Distortion.cpp
)




