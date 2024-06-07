//--------------------------------------------------
// Implementation of class GridPoints
//
// @author: Wild Boar
//
// @date: 2024-06-07
//--------------------------------------------------

#include "GridPoints.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param gridSize the size of the grid of points
 */
GridPoints::GridPoints(Size& gridSize)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Update
//--------------------------------------------------

/**
 * @brief Update a point within the system
 * @param position The position of the update
 * @param imagePoint The location of the image point
 * @param goalPoint The position of the goal point
 */
void GridPoints::Update(const Point2i& position, const Point2d& imagePoint, const Point2d& goalPoint)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Update a point within the system
 * @param position The position of the update
 * @param imagePoint The location of the image point
 * @param goalPoint The position of the goal point
 */
void GridPoints::Update(const Point2i& position, const Point2d& imagePoint, const Point3d& goalPoint)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Getter
//--------------------------------------------------

/**
 * @brief Retrieve a given image point
 * @param position the position of the associated image point
 * @return Point2d Returns a Point2d
 */
Point2d GridPoints::GetImagePoint(const Point2i& position)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve a given image point (in 2D)
 * @param position the position of the associated image point
 * @return Point2d Returns a Point2d
 */
Point2d GridPoints::GetGoalPoint2D(const Point2i& position)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve a given goal point (in 3D)
 * @param position the position of the associated image point
 * @return Point3d Returns a Point3d
 */
Point3d GridPoints::GetGoalPoint3D(const Point2i& position)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Determines whether a given point is set
 * @param position the position of the associated image point
 * @return bool Returns a bool
 */
bool GridPoints::IsPointSet(const Point2i& position)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the number of points within the grid
 * @return int Returns a int
 */
int GridPoints::GetPointCount()
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the number of points that have been set
 * @return int Returns a int
 */
int GridPoints::GetSetPointCount()
{
	throw runtime_error("Not implemented");
}
