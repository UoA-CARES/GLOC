//--------------------------------------------------
// Unit Tests for class IntrinsicProblem
//
// @author: Wild Boar
//
// @date: 2024-08-04
//--------------------------------------------------

#include <gtest/gtest.h>

#include <CalibratorLib/IntrinsicProblem.h>
using namespace NVL_App;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
extern unique_ptr<GridPoints> BuildGrid(const Size& gridSize, double blockSize, PinholeParams& parameters);
Mat BuildParameters(Mat& camera, Mat& pose_1, Mat& pose_2);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify the operation of the Intrinsic Problem
 */
TEST(IntrinsicProblem_Test, verify_opertion)
{
// Create the camera parameters
	auto camera = (Mat)(Mat_<double>(3,3) << 900, 0, 450, 0, 900, 450, 0, 0, 1);
	auto pose_1 = NVLib::PoseUtils::Vectors2Pose(Vec3d(0.1, -0.03, 0.2), Vec3d(10,20,70));
	auto pose_2 = NVLib::PoseUtils::Vectors2Pose(Vec3d(0, 0, 0), Vec3d(100,72,71));
	auto parameters_1 = PinholeParams(camera, pose_1);
	auto parameters_2 = PinholeParams(camera, pose_2);

	// Generate the associated grid
	auto grid_1 = BuildGrid(Size(9,7), 25, parameters_1);
	auto grid_2 = BuildGrid(Size(9,7), 25, parameters_2);

	FAIL() << "Not fully implemented";

	// Calculate score
	//auto errors = vector<double>(); auto score = parameters.CalculateError(grid.get(), errors);

	// Verify
	//ASSERT_NEAR(score, 0, 1e-4);
}

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------

/**
 * Convert the matrices into a vector of parameters
 * @param camera The provided camera matrix
 * @param pose_1 The pose of the first grid
 * @param pose_2 The pose of the second grid
 */
Mat BuildParameters(Mat& camera, Mat& pose_1, Mat& pose_2) 
{
	throw runtime_error("Not implemented");
}
