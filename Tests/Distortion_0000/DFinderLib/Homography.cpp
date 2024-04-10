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
	throw runtime_error("Not implemented");
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
	throw runtime_error("Not implemented");
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
Point2d Homography::Transform(Mat& H, const Point3d& point)
{
	throw runtime_error("Not implemented");
}
