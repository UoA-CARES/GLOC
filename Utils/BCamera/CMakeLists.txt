#--------------------------------------------------------
# Top-Level: BCamera
#
# @author: Wild Boar
#
# @Date Created: 2024-01-23
#--------------------------------------------------------

cmake_minimum_required(VERSION 3.0.0)
project(BCamera VERSION 0.1.0)

# Set the base path of the libraries
set(LIBRARY_BASE "$ENV{HOME}/Libraries")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add OpenCV to the solution
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Include OpenSSL
find_package(OpenSSL REQUIRED)

# Add Pylon to the project
include_directories(/opt/pylon/include)
link_directories(/opt/pylon/lib)

# Add the NVLib library to the folder
add_library(NVLib STATIC IMPORTED)
set_target_properties(NVLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/NVLib/build/NVLib/libNVLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/NVLib"
)

# Create the executable
add_executable(BCamera
    Source.cpp
    Camera.cpp
)

# Add link libraries                               
target_link_libraries(BCamera NVLib ${OpenCV_LIBS} pylonutility pylonbase GenApi_gcc_v3_1_Basler_pylon GCBase_gcc_v3_1_Basler_pylon OpenSSL::SSL uuid)
