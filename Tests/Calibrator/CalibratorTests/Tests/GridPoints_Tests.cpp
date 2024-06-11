//--------------------------------------------------
// Unit Tests for class GridPoints
//
// @author: Wild Boar
//
// @date: 2024-06-07
//--------------------------------------------------

#include <gtest/gtest.h>

#include <CalibratorLib/GridPoints.h>
using namespace NVL_App;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Determine that the counts associated with the grid are correct
 */
TEST(GridPoints_Test, counts_test)
{
	// Base Count Test
	auto grid = GridPoints(Size(5,4));
	ASSERT_EQ(grid.GetPointCount(), 20);
	ASSERT_EQ(grid.GetSetPointCount(), 0);
	ASSERT_EQ(grid.GetImagePoints().size(), 20);

	// Add a 2D point
	grid.Update(Point(1,1), Point2d(10,10), Point2d(11, 12));
	ASSERT_EQ(grid.GetSetPointCount(), 1);
	auto p_1 = grid.GetGoalPoint3D(Point(1,1));
	ASSERT_EQ(p_1.x, 11); ASSERT_EQ(p_1.y, 12); ASSERT_EQ(p_1.z, 0);

	// Add a 3D point
	grid.Update(Point(1,2), Point2d(10,20), Point3d(15, 16, 100));
	ASSERT_EQ(grid.GetSetPointCount(), 2);
	auto p_2 = grid.GetGoalPoint3D(Point(1,2));
	ASSERT_EQ(p_2.x, 15); ASSERT_EQ(p_2.y, 16); ASSERT_EQ(p_2.z, 100);
	auto p_3 = grid.GetImagePoint(Point(1,2));
	ASSERT_EQ(p_3.x, 10); ASSERT_EQ(p_3.y, 20);

	// Set Point Test
	ASSERT_TRUE(grid.IsPointSet(Point(1,1)));
	ASSERT_TRUE(grid.IsPointSet(Point(1,2)));
	ASSERT_FALSE(grid.IsPointSet(Point(1,3)));
}