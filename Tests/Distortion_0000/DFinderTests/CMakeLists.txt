#--------------------------------------------------------
# CMake for generating DFinderLib Testing Suite
#
# @author: Wild Boar
#
# Date Created: 2024-04-10
#--------------------------------------------------------

# Add Google Test to the test group
find_package(GTest REQUIRED)

# Setup the includes
include_directories("../")

# Create the executable
add_executable (DFinderTests
	Tests/Example_Tests.cpp
	Tests/Grid_Tests.cpp
	Tests/PointLoader_Tests.cpp
	Tests/Homography_Tests.cpp
	Tests/Distortion_Tests.cpp
)





# Add link libraries
target_link_libraries(DFinderTests DFinderLib NVLib ${OpenCV_LIBS} OpenSSL::SSL uuid GTest::Main)

# Find the associated unit tests
gtest_discover_tests(DFinderTests)

# Copy Resources across
add_custom_target(test_resource_copy ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/DFinderTests/Resources ${CMAKE_BINARY_DIR}/DFinderTests
    DEPENDS ${MY_TARGET}
)