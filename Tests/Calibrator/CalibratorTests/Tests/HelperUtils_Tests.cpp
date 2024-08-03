//--------------------------------------------------
// Unit Tests for class HelperUtils
//
// @author: Wild Boar
//
// @date: 2024-07-31
//--------------------------------------------------

#include <gtest/gtest.h>

#include <CalibratorLib/HelperUtils.h>
#include <CalibratorLib/LoadUtils.h>
#include <CalibratorLib/PinholeParams.h>
using namespace NVL_App;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
unique_ptr<GridPoints> BuildGrid(const Size& gridSize, double blockSize, PinholeParams& parameters);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Determine that the distortion removal works as expected
 */
TEST(HelperUtils_Test, distortion_conversion)
{
	// Setup
	auto helper = NVLib::PathHelper("/home/trevor/Research/GLOC/Data", "UnitTest");
	auto board = LoadUtils::LoadBoardParams(helper);
	auto calibration = LoadUtils::LoadCalibration(helper, "Distortion");

	// Load grids
	auto grid = LoadUtils::LoadGrid(helper, board->GetBoardSize(), "Points", 0);
	auto expected_grid = LoadUtils::LoadGrid(helper, board->GetBoardSize(), "Distortion", 0);

	// Perform the undistortion operation
	auto actual_grid = HelperUtils::Undistort(calibration.get(), grid.get());

	// Confirm that the values are as expected
	ASSERT_EQ(expected_grid->GetGridSize().width, actual_grid->GetGridSize().width);
	ASSERT_EQ(expected_grid->GetGridSize().height, actual_grid->GetGridSize().height);

	for (auto row = 0; row < expected_grid->GetGridSize().height; row++) 
	{
		for (auto column = 0; column < expected_grid->GetGridSize().width; column++) 
		{
			ASSERT_NEAR(expected_grid->GetImagePoint(Point2i(column, row)).x, actual_grid->GetImagePoint(Point2i(column, row)).x, 2);
			ASSERT_NEAR(expected_grid->GetImagePoint(Point2i(column, row)).y, actual_grid->GetImagePoint(Point2i(column, row)).y, 2);
		}
	}
}

/**
 * Calculate the given reprojection error
 */
TEST(HelperUtils_Test, reprojection_error) 
{
	// Create the camera parameters
	auto camera = (Mat)(Mat_<double>(3,3) << 900, 0, 450, 0, 900, 450, 0, 0, 1);
	auto pose = NVLib::PoseUtils::Vectors2Pose(Vec3d(0.1, -0.03, 0.2), Vec3d(10,20,70));
	auto parameters = PinholeParams(camera, pose);

	// Generate the associated grid
	auto grid = BuildGrid(Size(9,7), 25, parameters);

	// Calculate score
	auto errors = vector<double>(); auto score = parameters.CalculateError(grid.get(), errors);

	// Verify
	ASSERT_NEAR(score, 0, 1e-4);

}

//--------------------------------------------------
// Build Grid
//--------------------------------------------------

/**
 * Add the functionality to build the associated grid
 * @param gridSize The size of the grid that we are making
 * @param blockSize The size of the blocks making up the grid
 * @param parameters The parameters we are using to construct the 3d Points
 */
unique_ptr<GridPoints> BuildGrid(const Size& gridSize, double blockSize, PinholeParams& parameters) 
{
	auto result = new GridPoints(gridSize);

	auto invPose = parameters.GetPoseMatrix().inv();

	for (auto row = 0; row < gridSize.height; row++) 
	{
		for (auto column = 0; column < gridSize.width; column++) 
		{
			auto scenePoint = Point3d(column * blockSize, row * blockSize, 800);
			auto tscenePoint = NVLib::Math3D::TransformPoint(invPose, scenePoint);
			auto imagePoint = NVLib::Math3D::Project(parameters.GetCamera(), scenePoint);
			result->Update(Point2i(column, row), imagePoint, tscenePoint);
		}
	}

	return unique_ptr<GridPoints>(result);
}