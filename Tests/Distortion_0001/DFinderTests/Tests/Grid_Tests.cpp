//--------------------------------------------------
// Unit Tests for class Grid
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#include <gtest/gtest.h>

#include <DFinderLib/Distortion.h>
#include <DFinderLib/Grid.h>
using namespace NVL_App;

//--------------------------------------------------
// Prototypes
//--------------------------------------------------
unique_ptr<Grid> MakeGrid(const Size& size);

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

/**
 * @brief Grid distort and undistort
 */
TEST(Grid_Test, distortion_test)
{
	// Setup
	auto grid = MakeGrid(Size(5,5));
	auto distortion = Distortion(Size(500,500));
	Mat dparams = (Mat_<double>(4,1) << 0.1 -0.2, 0.01, -0.003);

	// Distort the grid
	auto dgrid = distortion.Distort(grid.get(), dparams);

	// Undistort the grid
	auto ugrid = distortion.Undistort(dgrid.get(), dparams);

	// Calculate the differences
	auto d_score = grid->GetDifference(dgrid.get());
	auto u_score = grid->GetDifference(ugrid.get());

	// Validate
	ASSERT_GT(d_score, 25);
	ASSERT_NEAR(u_score, 0, 1e-3);
}

//--------------------------------------------------
// Helper: MakeGrid
//--------------------------------------------------

/**
 * Add the functionality to make a grid
 * @param size The size fo the grid
 * @return The resultant grid that has been generated
*/
unique_ptr<Grid> MakeGrid(const Size& size) 
{
	auto result = new Grid(size);

	for (auto row = 0; row < size.height; row++) 
	{
		for (auto column = 0; column < size.width; column++) 
		{
			auto scenePoint = Point3d(column, row, 0);
			auto imagePoint = Point2d((column - 2.5) * 2 + 250, (row - 2.5) * 2 + 250);
			result->SetImagePoint(Point(column, row), imagePoint);
			result->SetScenePoint(Point(column, row), scenePoint);
		}
	}

	return unique_ptr<Grid>(result);
}