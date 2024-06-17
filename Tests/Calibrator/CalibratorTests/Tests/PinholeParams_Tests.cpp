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
	// Setup elements
	auto camera = (Mat) (Mat_<double>(3,3) << 1000.0, 0.0, 640, 0, 1000, 480, 0, 0, 1);
	auto pose = NVLib::PoseUtils::Vectors2Pose(Vec3d(), Vec3d());

	// Setup: Create a params object
	auto params = PinholeParams(camera, pose);

	// Setup the points
	auto points = GridPoints(Size(2,1));
	points.Update(Point2i(0, 0), Point2d(640, 481), Point3d(0, 0, 100));
	points.Update(Point2i(1, 0), Point2d(841, 181), Point3d(20, -30, 100));

	// Calcualte errors
	auto errors = vector<double>(); auto totalError = params.CalculateError(&points, errors);

	// Validate
	ASSERT_EQ(errors.size(), 2);
	ASSERT_EQ(errors[0], 1);
	ASSERT_EQ(errors[1], sqrt(2));
	ASSERT_EQ(totalError, 1 + sqrt(2));
}

/**
 * @brief Confirm that we are able to correctly set the state
 */
TEST(PinholeParams_Test, state_setting)
{
	// Setup elements
	auto camera = (Mat) (Mat_<double>(3,3) << 1000.0, 0.0, 640, 0, 1000, 480, 0, 0, 1);
	auto pose = NVLib::PoseUtils::Vectors2Pose(Vec3d(0.1,-0.2,0.3), Vec3d(10, -14, 211));

	// Setup: Create a params object
	auto params = PinholeParams(camera, pose);

	// Update the parameters
	auto a = vector<double> { 1200,1199, 1, 2, 3, 100, 100, 300 };
	params.SetState(a); 
	auto expectedPose = NVLib::PoseUtils::Vectors2Pose(Vec3d(a[2], a[3], a[4]), Vec3d(a[5], a[6], a[7]));

	// Execute
	auto actualPose = params.GetPoseMatrix();

	// Confirm
	auto alink = (double *) actualPose.data; auto plink = (double *) expectedPose.data;
	auto pixelCount = pose.rows * pose.cols;
	for (auto i = 0; i < pixelCount; i++) ASSERT_EQ(alink[i], plink[i]);

	auto clink = (double *) camera.data;
	ASSERT_EQ(clink[0], a[0]); ASSERT_EQ(clink[4], a[1]);
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
	for (auto i = 0; i < pixelCount; i++) ASSERT_NEAR(alink[i], plink[i], 1e-4);
}