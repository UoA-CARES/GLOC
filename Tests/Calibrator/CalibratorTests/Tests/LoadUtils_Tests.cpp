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
	ASSERT_EQ(board->GetBoardSize().width, 6);
	ASSERT_EQ(board->GetBoardSize().height, 8);
	ASSERT_EQ(board->GetBlockSize(), 48);
	ASSERT_EQ(board->GetMarkerSize(), 36);
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
	ASSERT_EQ(grid->GetPointCount(), 35);
	ASSERT_EQ(grid->GetImagePoint(Point2i(0,0)).x, 639.405);
	ASSERT_EQ(grid->GetImagePoint(Point2i(0,1)).x, 640.826);
	ASSERT_EQ(grid->GetImagePoint(Point2i(4,6)).y, 596.465);
	ASSERT_EQ(grid->GetGoalPoint3D(Point2i(0,1)).z, 0);
	ASSERT_EQ(grid->GetGoalPoint3D(Point2i(1,1)).x, 48);
	ASSERT_EQ(grid->GetGoalPoint3D(Point2i(0,6)).y, 288);
}