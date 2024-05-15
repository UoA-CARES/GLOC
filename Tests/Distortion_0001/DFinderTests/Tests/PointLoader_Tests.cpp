//--------------------------------------------------
// Unit Tests for class PointLoader
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#include <gtest/gtest.h>

#include <DFinderLib/PointLoader.h>
using namespace NVL_App;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Determines that loading occurred in a successful way
 */
TEST(PointLoader_Test, confirm_load)
{
	// Setup
	auto pathHelper = NVLib::PathHelper(string(), string());

	// Execute
	auto grid = PointLoader::GetGrid(&pathHelper, string(), 0);

	// Confirm
	ASSERT_EQ(grid->GetColumns(), 6);
	ASSERT_EQ(grid->GetRows(), 4);

	ASSERT_EQ(grid->GetImagePoint(Point(0,0)).x, 277.47);
	ASSERT_EQ(grid->GetImagePoint(Point(0,0)).y, 351.646);
	ASSERT_EQ(grid->GetScenePoint(Point(0,0)).x, 0.0);
	ASSERT_EQ(grid->GetScenePoint(Point(0,0)).y, 0.0);
	ASSERT_EQ(grid->GetScenePoint(Point(0,0)).z, 0.0);

	ASSERT_EQ(grid->GetImagePoint(Point(2,2)).x, 420.413);
	ASSERT_EQ(grid->GetImagePoint(Point(2,2)).y, 500.0);
	ASSERT_EQ(grid->GetScenePoint(Point(2,2)).x, 80.0);
	ASSERT_EQ(grid->GetScenePoint(Point(2,2)).y, 80.0);
	ASSERT_EQ(grid->GetScenePoint(Point(2,2)).z, 0.0);

	// Teardown
	delete grid;
}
