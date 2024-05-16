//--------------------------------------------------
// Implementation of class Homography
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#include "Homography.h"
using namespace NVL_App;

//--------------------------------------------------
// Generate
//--------------------------------------------------

/**
 * @brief Determine the existing homography
 * @param grid The grid that we are processing
 * @return Mat Returns a Mat
 */
Mat Homography::GetHomography(Grid * grid)
{
	auto scenePoints = vector<Point2f>(); auto imagePoints = vector<Point2f>();

	auto xmax = grid->GetColumns() - 1; auto ymax = grid->GetRows() - 1; 

	scenePoints.push_back(Convert(grid->GetScenePoint(Point(0,0))));
	imagePoints.push_back(Convert(grid->GetImagePoint(Point(0,0))));

	scenePoints.push_back(Convert(grid->GetScenePoint(Point(xmax,0))));
	imagePoints.push_back(Convert(grid->GetImagePoint(Point(xmax,0))));

	scenePoints.push_back(Convert(grid->GetScenePoint(Point(xmax,ymax))));
	imagePoints.push_back(Convert(grid->GetImagePoint(Point(xmax,ymax))));

	scenePoints.push_back(Convert(grid->GetScenePoint(Point(0,ymax))));
	imagePoints.push_back(Convert(grid->GetImagePoint(Point(0,ymax))));

	return cv::findHomography(scenePoints, imagePoints);
}

//--------------------------------------------------
// Scoring
//--------------------------------------------------

/**
 * Get the grid from the given homography
 * @param grid The base grid
 * @param H The homograph that we are using
 * @return The resultant grid
*/
unique_ptr<Grid> Homography::GetGrid(Grid * grid, Mat& H) 
{
	auto result = new Grid(grid->GetSize());

	for (auto row = 0; row < grid->GetRows(); row++) 
	{
		for (auto column = 0; column < grid->GetColumns(); column++) 
		{
			auto scenePoint = grid->GetScenePoint(Point(column, row));
			auto imagePoint = grid->GetImagePoint(Point(column, row)); //Transform(H, Convert(scenePoint));

			auto ipoint_1 = grid->GetImagePoint(Point(column, row));
			auto ipoint_2 = Transform(H, Convert(scenePoint));

			result->SetScenePoint(Point(column, row), scenePoint);
			result->SetImagePoint(Point(column, row), ipoint_2);			
		}
	}

	return unique_ptr<Grid>(result);
}

//--------------------------------------------------
// Scoring
//--------------------------------------------------

/**
 * @brief Determine the score of the homography fit
 * @param H The homography that we are testing against
 * @param grid The grid that we are processing
 * @return double Returns a double
 */
double Homography::GetHScore(Mat& H, Grid * grid)
{
	auto total = 0.0;

	for (auto row = 0; row < grid->GetRows(); row++) 
	{
		for (auto column = 0; column < grid->GetColumns(); column++) 
		{
			auto scenePoint = grid->GetScenePoint(Point(column, row));
			auto expected = Transform(H, Point2d(scenePoint.x, scenePoint.y));
			auto actual = grid->GetImagePoint(Point(column, row));

			auto xDiff = expected.x - actual.x;
			auto yDiff = expected.y - actual.y;
			auto score = sqrt(xDiff * xDiff + yDiff * yDiff);

			total += score;
		}
	}

	return total;
}

//--------------------------------------------------
// Generation
//--------------------------------------------------

/**
 * @brief Transform a world coordinate into an image coordinate
 * @param H The homography that we are working with
 * @param point The point that we are converting
 * @return Point2d Returns a Point2d
 */
Point2d Homography::Transform(Mat& H, const Point2d& point)
{
	auto hLink = (double *) H.data;

	auto X = hLink[0] * point.x + hLink[1] * point.y + hLink[2];
	auto Y = hLink[3] * point.x + hLink[4] * point.y + hLink[5];
	auto Z = hLink[6] * point.x + hLink[7] * point.y + hLink[8];

	return Point2d( X / Z, Y / Z);
}

//--------------------------------------------------
// Generation
//--------------------------------------------------

/**
 * Convert a "double" image point into a float point
 * @param point The point that we dealing with
 * @return The resultant point
*/
Point2f Homography::Convert(const Point2d& point) 
{
	return Point2f((float) point.x, (float) point.y);
}

/**
 * Convert a "double" 3D point that we are dealing with
 * @param point the scene point
 * @return The resultant point
*/
Point2f Homography::Convert(const Point3d& point) 
{
	return Point2f((float) point.x, (float) point.y);
}