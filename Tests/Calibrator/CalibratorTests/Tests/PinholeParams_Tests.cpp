//--------------------------------------------------
// Unit Tests for class PinholeParams
//
// @author: Wild Boar
//
// @date: 2024-06-17
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/PoseUtils.h>

#include <CalibratorLib/PinholeParams.h>
using namespace NVL_App;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm the error calculation logic
 */
TEST(PinholeParams_Test, error_calculation)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

/**
 * @brief Confirm that we are able to correctly set the state
 */
TEST(PinholeParams_Test, state_setting)
{
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}

/**
 * @brief Determine the pose 
 */
TEST(PinholeParams_Test, pose_test)
{
	// Setup elements
	auto camera = (Mat) (Mat_<double>(3,3) << 1000.0, 0.0, 640, 0, 1000, 480, 0, 0, 1);
	auto pose = NVLib::PoseUtils::Vectors2Pose(Vec3d(0.1,-0.2,0.3), Vec3d(10, -14, 211));

	// Setup: Create a params object
	auto params = PinholeParams(camera, pose);

	// Execute
	auto actualPose = params.GetPoseMatrix();

	// Confirm
	auto alink = (double *) actualPose.data; auto plink = (double *) pose.data;
	auto pixelCount = pose.rows * pose.cols;
	for (auto i = 0; i < pixelCount; i++) ASSERT_EQ(alink[i], plink[i]);
}