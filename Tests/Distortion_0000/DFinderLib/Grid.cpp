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
Grid::Grid(Mat& data)
{
	_data = data;
}

/**
 * @brief Main Terminator
 */
Grid::~Grid()
{
	// TODO: Add teardown logic here
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
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the number of columns in the grid
 * @return int Returns a int
 */
int Grid::GetColumns()
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the image point
 * @param location The location of the image point that we want
 * @return Point2d Returns a Point2d
 */
Point2d Grid::GetImagePoint(const Point& location)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the scene point
 * @param location The location of the scene point that we want
 * @return Point3d Returns a Point3d
 */
Point3d Grid::GetScenePoint(const Point& location)
{
	throw runtime_error("Not implemented");
}