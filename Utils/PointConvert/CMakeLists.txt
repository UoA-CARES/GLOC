#--------------------------------------------------------
# Top-Level: PointConvert
#
# @author: Wild Boar
#
# @Date Created: 2024-04-19
#--------------------------------------------------------

cmake_minimum_required(VERSION 3.0.0)
project(PointConvert VERSION 0.1.0)

# Set the base path of the libraries
set(LIBRARY_BASE "$ENV{HOME}/Libraries")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add OpenCV to the solution
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Include OpenSSL
find_package(OpenSSL REQUIRED)

# Add the NVLib library to the folder
add_library(NVLib STATIC IMPORTED)
set_target_properties(NVLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/NVLib/build/NVLib/libNVLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/NVLib"
)

# Create the executable
add_executable(PointConvert
    Source.cpp
    Settings.cpp
    LoadUtils.cpp
)

# Add link libraries                               
target_link_libraries(PointConvert NVLib ${OpenCV_LIBS} OpenSSL::SSL uuid)