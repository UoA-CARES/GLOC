//--------------------------------------------------
// Unit Tests for class LoadUtils
//
// @author: Wild Boar
//
// @date: 2024-07-30
//--------------------------------------------------

#include <gtest/gtest.h>

#include <CalibratorLib/LoadUtils.h>
using namespace NVL_App;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Determine that the loading of board parameters is occuring succesfully
 */
TEST(LoadUtils_Test, load_board_params)
{
	// Setup
	auto helper = NVLib::PathHelper("/home/trevor/Research/GLOC/Data", "UnitTest");

	// Execute
	auto board = LoadUtils::LoadBoardParams(helper);

	// Confirm
	ASSERT_EQ(board->GetBoardSize().width, 10);
	ASSERT_EQ(board->GetBoardSize().height, 7);
	ASSERT_EQ(board->GetBlockSize(), 25);
	ASSERT_EQ(board->GetMarkerSize(), 0);
	ASSERT_EQ(board->GetDictionary(), 3);
}

/**
 * @brief Determine that we are able to load a grid correctly
 */
TEST(LoadUtils_Test, load_grid)
{
	// Setup
	auto helper = NVLib::PathHelper("/home/trevor/Research/GLOC/Data", "UnitTest");
	auto board = LoadUtils::LoadBoardParams(helper);

	// Execute
	auto grid = LoadUtils::LoadGrid(helper, board->GetBoardSize(), "Points", 0);

	// Confirm
	ASSERT_EQ(grid->GetPointCount(), 54);
	ASSERT_EQ(grid->GetImagePoint(Point2i(0,0)).x, 1143.88);
	ASSERT_EQ(grid->GetImagePoint(Point2i(0,1)).x, 1071.59);
	ASSERT_EQ(grid->GetImagePoint(Point2i(4,5)).y, 582.715);
	ASSERT_EQ(grid->GetGoalPoint3D(Point2i(0,1)).z, 0);
	ASSERT_EQ(grid->GetGoalPoint3D(Point2i(1,1)).x, 25);
	ASSERT_EQ(grid->GetGoalPoint3D(Point2i(0,5)).y, 125);
}

/**
 * Add the functionality to load up calibration details
 */
TEST(LoadUtils_Test, load_calibration) 
{
	// Setup
	auto helper = NVLib::PathHelper("/home/trevor/Research/GLOC/Data", "UnitTest");

	// Execute
	auto calibration = LoadUtils::LoadCalibration(helper, "Distortion");

	// Test Camera
	auto clink = (double *) calibration->GetCamera().data;
	ASSERT_EQ(calibration->GetCamera().rows, 3);
	ASSERT_EQ(calibration->GetCamera().cols, 3);
	auto cvalues = vector<double> { 6624, 0, 1104.003, 0, 6624, 620.999, 0, 0, 1 };
	for (auto i = 0; i < cvalues.size(); i++) ASSERT_NEAR(clink[i], cvalues[i], 1e-4);

	// Test Distortion
	auto dlink = (double *) calibration->GetDistortion().data;
	ASSERT_EQ(calibration->GetDistortion().rows, 5);
	ASSERT_EQ(calibration->GetDistortion().cols, 1);
	auto dvalues = vector<double> { -4.05099, 183.005, -0.032, -0.004, -3698.3929 };
	for (auto i = 0; i < dvalues.size(); i++) ASSERT_NEAR(dlink[i], dvalues[i], 1e-4);

	// Test Size
	ASSERT_EQ(calibration->GetImageSize().width, 2208);
	ASSERT_EQ(calibration->GetImageSize().height, 1242);
}