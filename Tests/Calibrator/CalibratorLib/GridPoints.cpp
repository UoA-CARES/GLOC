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
GridPoints::GridPoints(const Size& gridSize) : _gridSize(gridSize)
{
	assert(gridSize.width > 0 && gridSize.height > 0);
	auto pointCount = gridSize.width * gridSize.height;
	for (auto i = 0; i < pointCount; i++) 
	{
		_imagePoints.push_back(Point2d());
		_goalPoints.push_back(Point2d());
		_setPoints.push_back(false);
		_depth.push_back(0);
	}
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
	assert(position.x >= 0 && position.x < _gridSize.width && position.y >= 0 && position.y < _gridSize.height);
	auto index = position.x + position.y * _gridSize.width;

	_imagePoints[index] = imagePoint;
	_goalPoints[index] = goalPoint;
	_depth[index] = 0;
	_setPoints[index] = true;
}

/**
 * @brief Update a point within the system
 * @param position The position of the update
 * @param imagePoint The location of the image point
 * @param goalPoint The position of the goal point
 */
void GridPoints::Update(const Point2i& position, const Point2d& imagePoint, const Point3d& goalPoint)
{
	assert(position.x >= 0 && position.x < _gridSize.width && position.y >= 0 && position.y < _gridSize.height);
	auto index = position.x + position.y * _gridSize.width;

	_imagePoints[index] = imagePoint;
	_goalPoints[index] = Point2d(goalPoint.x, goalPoint.y);
	_depth[index] = goalPoint.z;
	_setPoints[index] = true;
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
	assert(position.x >= 0 && position.x < _gridSize.width && position.y >= 0 && position.y < _gridSize.height);
	auto index = position.x + position.y * _gridSize.width;
	return _imagePoints[index];
}

/**
 * @brief Retrieve a given image point (in 2D)
 * @param position the position of the associated image point
 * @return Point2d Returns a Point2d
 */
Point2d GridPoints::GetGoalPoint2D(const Point2i& position)
{
	assert(position.x >= 0 && position.x < _gridSize.width && position.y >= 0 && position.y < _gridSize.height);
	auto index = position.x + position.y * _gridSize.width;
	return _goalPoints[index];
}

/**
 * @brief Retrieve a given goal point (in 3D)
 * @param position the position of the associated image point
 * @return Point3d Returns a Point3d
 */
Point3d GridPoints::GetGoalPoint3D(const Point2i& position)
{
	assert(position.x >= 0 && position.x < _gridSize.width && position.y >= 0 && position.y < _gridSize.height);
	auto index = position.x + position.y * _gridSize.width;
	auto xy =  _goalPoints[index]; auto z = _depth[index];
	return Point3d(xy.x, xy.y, z); 
}

/**
 * @brief Determines whether a given point is set
 * @param position the position of the associated image point
 * @return bool Returns a bool
 */
bool GridPoints::IsPointSet(const Point2i& position)
{
	assert(position.x >= 0 && position.x < _gridSize.width && position.y >= 0 && position.y < _gridSize.height);
	auto index = position.x + position.y * _gridSize.width;
	return _setPoints[index];
}

/**
 * @brief Retrieve the number of points within the grid
 * @return int Returns a int
 */
int GridPoints::GetPointCount()
{
	return _gridSize.width * _gridSize.height;
}

/**
 * @brief Retrieve the number of points that have been set
 * @return int Returns a int
 */
int GridPoints::GetSetPointCount()
{
	auto total = 0; auto pixelCount = _gridSize.width * _gridSize.height;
	for (auto i = 0; i < pixelCount; i++) if (_setPoints[i]) total++;
	return total;
}
