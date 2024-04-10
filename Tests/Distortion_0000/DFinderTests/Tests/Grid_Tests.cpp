//--------------------------------------------------
// Unit Tests for class Grid
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#include <gtest/gtest.h>

#include <DFinderLib/Grid.h>
using namespace NVL_App;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Retrieve points from the grid structure
 */
TEST(Grid_Test, retrieve_points)
{
	// Setup
	auto grid = Grid(Size(5,5));
	grid.SetImagePoint(Point(0,0), Point2d(1,2)); grid.SetScenePoint(Point(0,0), Point3d(1,2,3));

	// Execute
	auto ipoint_1 = grid.GetImagePoint(Point(0,0)); auto spoint_1 = grid.GetScenePoint(Point(0,0));
	auto ipoint_2 = grid.GetImagePoint(Point(1,1)); auto spoint_2 = grid.GetScenePoint(Point(1,1));

	// Confirm
	ASSERT_EQ(grid.GetColumns(), 5); ASSERT_EQ(grid.GetRows(), 5);

	ASSERT_EQ(ipoint_1.x, 1); ASSERT_EQ(ipoint_1.y, 2);
	ASSERT_EQ(spoint_1.x, 1); ASSERT_EQ(spoint_1.y, 2); ASSERT_EQ(spoint_1.z, 3);

	ASSERT_EQ(ipoint_2.x, 0); ASSERT_EQ(ipoint_2.y, 0);
	ASSERT_EQ(spoint_2.x, 0); ASSERT_EQ(spoint_2.y, 0); ASSERT_EQ(spoint_2.z, 0);
}
