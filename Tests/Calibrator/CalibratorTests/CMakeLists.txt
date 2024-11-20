#--------------------------------------------------------
# CMake for generating CalibratorLib Testing Suite
#
# @author: Wild Boar
#
# Date Created: 2024-05-28
#--------------------------------------------------------

# Add Google Test to the test group
find_package(GTest REQUIRED)

# Setup the includes
include_directories("../")

# Create the executable
add_executable (CalibratorTests
	Tests/GridPoints_Tests.cpp
	Tests/LoadUtils_Tests.cpp
	Tests/HelperUtils_Tests.cpp
)

# Add link libraries
target_link_libraries(CalibratorTests CalibratorLib JarvisLib NVLib ${OpenCV_LIBS} pugixml OpenSSL::SSL uuid GTest::Main)

# Find the associated unit tests
gtest_discover_tests(CalibratorTests)