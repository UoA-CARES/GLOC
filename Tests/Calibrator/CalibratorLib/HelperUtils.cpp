//--------------------------------------------------
// Implementation of class HelperUtils
//
// @author: Wild Boar
//
// @date: 2024-07-31
//--------------------------------------------------

#include "HelperUtils.h"
using namespace NVL_App;

//--------------------------------------------------
// Undistort
//--------------------------------------------------

/**
 * @brief Remove the distortion from given points
 * @param calibration The calibration that we are dealing with
 * @param points The points that we are undistorting
 * @return unique_ptr<GridPoints> Returns a unique_ptr<GridPoints>
 */
unique_ptr<GridPoints> HelperUtils::Undistort(Calibration * calibration, GridPoints * points)
{
	// Get the image points
	auto& imagePoints = points->GetImagePoints();
	auto& scenePoints = points->GetGoalPoints();

	// Find the set of images
	auto uimagePoints = vector<Point2d>(); undistortPoints(imagePoints, uimagePoints, calibration->GetCamera(), calibration->GetDistortion(), noArray(), calibration->GetCamera());

	// Create the result
	auto gridSize = points->GetGridSize();
	auto result = new GridPoints(gridSize);
	for (auto row = 0; row < gridSize.height; row++) 
	{
		for (auto column = 0; column < gridSize.width; column++) 
		{
			auto index = column + row * gridSize.width;
			result->Update(Point2i(column, row), uimagePoints[index], scenePoints[index]);
		}
	}

	// Return the result
	return unique_ptr<GridPoints>(result);
}
