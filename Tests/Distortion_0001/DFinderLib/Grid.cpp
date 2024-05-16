//--------------------------------------------------
// Implementation of class Grid
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#include "Grid.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param data Initialize variable <data>
 */
Grid::Grid(Mat& data) : _data(data)
{
	// Extra initialization can go here
}

/**
 * @brief The dize of the data constructor
*/
Grid::Grid(const Size& gridSize) 
{
	_data = Mat_<Vec<double, 5>>::zeros(gridSize);
}

//--------------------------------------------------
// Getter
//--------------------------------------------------

/**
 * @brief Retrieve the number of rows in the grid
 * @return int Returns a int
 */
int Grid::GetRows()
{
	return _data.rows;
}

/**
 * @brief Retrieve the number of columns in the grid
 * @return int Returns a int
 */
int Grid::GetColumns()
{
	return _data.cols;
}

/**
 * Retrieve the size of the grid
*/
Size Grid::GetSize() 
{
	return _data.size();
}

/**
 * @brief Retrieve the image point
 * @param location The location of the image point that we want
 * @return Point2d Returns a Point2d
 */
Point2d Grid::GetImagePoint(const Point& location)
{
	if (location.x < 0 || location.x >= _data.cols || location.y < 0 || location.y >= _data.rows) throw runtime_error("location is out of range");

	auto dlink = (double *) _data.data;
	auto index = location.x + location.y * _data.cols;

	auto u = dlink[index * 5 + 0];
	auto v = dlink[index * 5 + 1];

	return Point2d(u, v);
}

/**
 * @brief Retrieve the scene point
 * @param location The location of the scene point that we want
 * @return Point3d Returns a Point3d
 */
Point3d Grid::GetScenePoint(const Point& location)
{
	if (location.x < 0 || location.x >= _data.cols || location.y < 0 || location.y >= _data.rows) throw runtime_error("location is out of range");

	auto dlink = (double *) _data.data;
	auto index = location.x + location.y * _data.cols;

	auto X = dlink[index * 5 + 2];
	auto Y = dlink[index * 5 + 3];
	auto Z = dlink[index * 5 + 4];

	return Point3d(X, Y, Z);
}

//--------------------------------------------------
// Getter
//--------------------------------------------------

/**
 * Set the associated image point location
 * @param location The location of the given point
 * @param point The point that we are setting
*/
void Grid::SetImagePoint(const Point& location, const Point2d& point) 
{
	if (location.x < 0 || location.x >= _data.cols || location.y < 0 || location.y >= _data.rows) throw runtime_error("location is out of range");

	auto dlink = (double *) _data.data;
	auto index = location.x + location.y * _data.cols;

	dlink[index * 5 + 0] = point.x;
	dlink[index * 5 + 1] = point.y;
}

/**
 * Set the associated scene point location
 * @param location The location that we are setting
 * @param point The point that is being set
*/
void Grid::SetScenePoint(const Point& location, const Point3d& point) 
{
	if (location.x < 0 || location.x >= _data.cols || location.y < 0 || location.y >= _data.rows) throw runtime_error("location is out of range");

	auto dlink = (double *) _data.data;
	auto index = location.x + location.y * _data.cols;

	dlink[index * 5 + 2] = point.x;
	dlink[index * 5 + 3] = point.y;
	dlink[index * 5 + 4] = point.z;
}

/**
 * Determine a point matrix
 */
Mat Grid::GetImagePointMatrix() 
{
	// Determine the number of points
	auto pointCount = _data.rows * _data.cols;

	Mat result = Mat_<double>::zeros(pointCount, 2);

	auto inputLink = (double *) _data.data;
	auto outputLink = (double *) result.data;

	for (auto row = 0; row < _data.rows; row++) 
	{
		for (auto column = 0; column < _data.cols; column++) 
		{
			auto index = column + row * _data.cols;
			
			outputLink[index * 2 + 0] = inputLink[index * 5 + 0];
			outputLink[index * 2 + 1] = inputLink[index * 5 + 1];
		}
	}

	return result;
}