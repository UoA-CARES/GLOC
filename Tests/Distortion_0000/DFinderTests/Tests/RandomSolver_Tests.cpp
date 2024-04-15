//--------------------------------------------------
// Unit Tests for class RandomSolver
//
// @author: Wild Boar
//
// @date: 2024-04-12
//--------------------------------------------------

#include <gtest/gtest.h>

#include <DFinderLib/RandomSolver.h>
using namespace NVL_App;

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
extern void AddGridPoint(Grid * grid, const Point& index, const Point3d& scenePoint, Mat& camera);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Test the solver operation
 */
TEST(RandomSolver_Test, solution_test_00)
{
	// Setup
	auto grid_1 = Grid(Size(12,12)); auto imageSize = Size(1000, 1000);
	Mat camera = (Mat_<double>(3,3) << 1000, 0, imageSize.width * 0.5, 0, 100, imageSize.height * 0.5, 0, 0, 1);
	Mat dparams = (Mat_<double>(4,1) << -0.1, 0.2, 0.01, 0.3);
	Mat noDistortion = Mat_<double>::zeros(4,1);

	// Build the grid
	for (auto row = 0; row < grid_1.GetRows(); row++) 
	{
		for (auto column = 0; column < grid_1.GetColumns(); column++) 
		{
			auto X = (column - 5) * 40.0; auto Y = (row - 5) * 40.0; auto Z = 100;
			AddGridPoint(&grid_1, Point(column, row), Point3d(X, Y, Z), camera);
		}
	}

	// Add some distortion
	auto grid_2 = Distortion(Size(1000,1000)).Undistort(&grid_1, dparams);

	// Confirm
	auto solver = RandomSolver(imageSize, grid_2, noDistortion);
	auto score = solver.Solve(1e6);
	ASSERT_LT(score / (grid_1.GetColumns() * grid_1.GetRows()), 1);
}
