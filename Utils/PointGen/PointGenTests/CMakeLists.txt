#--------------------------------------------------------
# CMake for generating PointGenLib Testing Suite
#
# @author: Wild Boar
#
# Date Created: 2024-03-05
#--------------------------------------------------------

# Add Google Test to the test group
find_package(GTest REQUIRED)

# Setup the includes
include_directories("../")

# Create the executable
add_executable(PointGenTests
    Tests/Example_Tests.cpp
)

# Add link libraries
target_link_libraries(PointGenTests PointGenLib NVLib ${OpenCV_LIBS} OpenSSL::SSL uuid GTest::Main)

# Find the associated unit tests
gtest_discover_tests(PointGenTests)
