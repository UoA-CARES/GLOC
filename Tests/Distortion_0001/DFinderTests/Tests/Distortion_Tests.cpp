//--------------------------------------------------
// Unit Tests for class Distortion
//
// @author: Wild Boar
//
// @date: 2024-04-12
//--------------------------------------------------

#include <gtest/gtest.h>
#include <NVLib/Math2D.h>
#include <DFinderLib/Distortion.h>
using namespace NVL_App;

//--------------------------------------------------
// Add Point
//--------------------------------------------------

void AddGridPoint(Grid * grid, const Point& index, const Point3d& scenePoint, Mat& camera);
Point2d GetPoint(Mat& hpoint);
double GetDifference(const Point& index, Grid * grid_1, Grid * grid_2);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Convert the numbers
 */
TEST(Distortion_Test, distortion_test)
{
	// Setup
	auto grid_1 = Grid(Size(3,3));
	Mat camera = (Mat_<double>(3,3) << 1000, 0, 320, 0, 100, 240, 0, 0, 1);
	Mat dparams = (Mat_<double>(4,1) << 0.1, 0, 0, 0);

	// Build the grid
	for (auto row = 0; row < grid_1.GetRows(); row++) 
	{
		for (auto column = 0; column < grid_1.GetColumns(); column++) 
		{
			auto X = (column - 1) * 40.0; auto Y = (row - 1) * 40.0; auto Z = 100;
			AddGridPoint(&grid_1, Point(column, row), Point3d(X, Y, Z), camera);
		}
	}

	// Execute
	auto grid_2 = Distortion(Size(640, 480)).Undistort(&grid_1, dparams);

	auto delta_1 = GetDifference(Point(1,1), &grid_1, grid_2);
	auto delta_2 = GetDifference(Point(2,2), &grid_1, grid_2);

	// Confirm
	ASSERT_LT(delta_1, 1e-3);
	ASSERT_GT(delta_2, 1.0);

	// Teardown
	delete grid_2;
}

//--------------------------------------------------
// Helper Functionality
//--------------------------------------------------

/**
 * Add a grid point to the application
 * @param grid The grid that we are adding to the system
 * @param index The index that we are adding the point to
 * @param screenPoint The scene point that is being added
 * @param camera The camera matrix that we are using
*/
void AddGridPoint(Grid * grid, const Point& index, const Point3d& scenePoint, Mat& camera) 
{
	Mat hpoint = camera * Mat(scenePoint);
	auto imagePoint = GetPoint(hpoint);
	grid->SetScenePoint(index, scenePoint);
	grid->SetImagePoint(index, imagePoint);
}

/**
 * Retrieve a point from a homogenous matrix
 * @param hpoint The encoded homogenous point
 * @return The point that has been retrieved
*/
Point2d GetPoint(Mat& hpoint) 
{
	auto dlink = (double *) hpoint.data;
	auto x = dlink[0]; auto y = dlink[1]; auto z = dlink[2];
	auto u = x / z; auto v = y / z;
	return Point2d(u,v);
}

/**
 * Find the difference between points at a particular index
 * @param index The index of the point that we are calculating
 * @param grid_1 The value for the first grid
 * @param grid_2 The valeu for the second grid
 * @return The difference between the two values
*/
double GetDifference(const Point& index, Grid * grid_1, Grid * grid_2) 
{
	auto p_1 = grid_1->GetImagePoint(index);
	auto p_2 = grid_2->GetImagePoint(index);
	return NVLib::Math2D::GetDistance(p_1, p_2);
}