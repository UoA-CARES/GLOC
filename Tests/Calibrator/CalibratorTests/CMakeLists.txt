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
	Tests/Example_Tests.cpp
	Tests/GridPoints_Tests.cpp
	Tests/InitialParams_Tests.cpp
	Tests/PinholeParams_Tests.cpp
	Tests/LoadUtils_Tests.cpp
)


# Add link libraries
target_link_libraries(CalibratorTests CalibratorLib NVLib ${OpenCV_LIBS} OpenSSL::SSL uuid GTest::Main)

# Find the associated unit tests
gtest_discover_tests(CalibratorTests)