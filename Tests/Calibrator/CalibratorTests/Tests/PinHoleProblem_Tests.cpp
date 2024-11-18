//--------------------------------------------------
// Unit Tests for class IntrinsicProblem
//
// @author: Wild Boar
//
// @date: 2024-08-04
//--------------------------------------------------

#include <gtest/gtest.h>

#include <CalibratorLib/PinHoleProblem.h>
using namespace NVL_App;

#include "../Helpers/TestUtils.h"

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Verify the operation of the Intrinsic Problem
 */
TEST(PinHoleProblem_Test, verify_opertion)
{
	// Create the camera parameters
	auto camera = (Mat)(Mat_<double>(3,3) << 900, 0, 450, 0, 900, 450, 0, 0, 1);
	auto pose_1 = NVLib::PoseUtils::Vectors2Pose(Vec3d(0.1, -0.03, 0.2), Vec3d(10,20,70));
	auto pose_2 = NVLib::PoseUtils::Vectors2Pose(Vec3d(0, 0, 0), Vec3d(100,72,71));
	auto parameters_1 = PinholeParams(camera, pose_1);
	auto parameters_2 = PinholeParams(camera, pose_2);

	// Generate the associated grid
	auto grid_1 = TestUtils::BuildGrid(Size(9,7), 25, parameters_1);
	auto grid_2 = TestUtils::BuildGrid(Size(9,7), 25, parameters_2);

	// Generate the parameters
	Mat parameters = TestUtils::BuildParameters(camera, pose_1, pose_2);

	// Create a pinhole problem
	auto problem = PinHoleProblem(grid_1.get(), grid_2.get());

	//Calculate score
	auto errors = vector<double>(); auto score = problem.Evaluate()

	// Verify
	//ASSERT_NEAR(score, 0, 1e-4);
}