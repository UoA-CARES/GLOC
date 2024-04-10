//--------------------------------------------------
// Unit Tests for class Homography
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#include <gtest/gtest.h>

#include <DFinderLib/Homography.h>
using namespace NVL_App;

//--------------------------------------------------
// Helper Methods
//--------------------------------------------------
double GetPointMagnitude(const Point2d& point);

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief The logic of fitting a homography to data
 */
TEST(Homography_Test, h_fitting)
{
	// Setup
	auto grid = Grid(Size(2,2));

	grid.SetScenePoint(Point(0,0), Point3d(0,0,0));
	grid.SetImagePoint(Point(0,0), Point2d(0,0));

	grid.SetScenePoint(Point(1,0), Point3d(1,0,0));
	grid.SetImagePoint(Point(1,0), Point2d(2,0));

	grid.SetScenePoint(Point(1,1), Point3d(1,1,0));
	grid.SetImagePoint(Point(1,1), Point2d(2,2));

	grid.SetScenePoint(Point(0,1), Point3d(0,1,0));
	grid.SetImagePoint(Point(0,1), Point2d(0,2));

	// Execute
	Mat H = Homography::GetHomography(&grid);

	// Confirm
	auto score = Homography::GetHScore(H, &grid);
	ASSERT_LT(score, 1e-3);
}

/**
 * @brief The logic of scoring a homography against actual points
 */
TEST(Homography_Test, h_score)
{
// Setup
	auto grid = Grid(Size(3,3));

	grid.SetScenePoint(Point(0,0), Point3d(0,0,0));
	grid.SetImagePoint(Point(0,0), Point2d(0,0));

	grid.SetScenePoint(Point(2,0), Point3d(2,0,0));
	grid.SetImagePoint(Point(2,0), Point2d(2,0));

	grid.SetScenePoint(Point(2,2), Point3d(1,1,0));
	grid.SetImagePoint(Point(2,2), Point2d(2,2));

	grid.SetScenePoint(Point(0,2), Point3d(0,1,0));
	grid.SetImagePoint(Point(0,2), Point2d(0,2));

	grid.SetScenePoint(Point(1,0), Point3d(1,0,0));
	grid.SetScenePoint(Point(0,1), Point3d(0,1,0));
	grid.SetScenePoint(Point(1,1), Point3d(1,1,0));
	grid.SetScenePoint(Point(2,1), Point3d(2,1,0));
	grid.SetScenePoint(Point(1,2), Point3d(1,2,0));

	// Execute
	Mat H = Homography::GetHomography(&grid);

	// Determine a theoretical error
	auto p_1 = Homography::Transform(H, Point3d(1,0,0)); auto s_1 = GetPointMagnitude(p_1);
	auto p_2 = Homography::Transform(H, Point3d(0,1,0)); auto s_2 = GetPointMagnitude(p_2);
	auto p_3 = Homography::Transform(H, Point3d(1,1,0)); auto s_3 = GetPointMagnitude(p_3);
	auto p_4 = Homography::Transform(H, Point3d(2,1,0)); auto s_4 = GetPointMagnitude(p_4);
	auto p_5 = Homography::Transform(H, Point3d(1,2,0)); auto s_5 = GetPointMagnitude(p_5);

	// Confirm
	auto expectedError = s_1 + s_2 + s_3 + s_4 + s_5;
	auto score = Homography::GetHScore(H, &grid);
	ASSERT_LT(abs(score - expectedError), 1e-3);
}

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * Calculate the point magnitude
 * @param point The point that we are getting the magnitude for
 * @return The point magnitude that we have calculated
*/
double GetPointMagnitude(const Point2d& point) 
{
	return sqrt(point.x * point.x + point.y + point.y);
}