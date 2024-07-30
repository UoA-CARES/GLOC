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
	FAIL() << "Not implemented";

	// Setup

	// Execute

	// Confirm

	// Teardown
}
