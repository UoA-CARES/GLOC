//--------------------------------------------------
// Implementation of class Distortion
//
// @author: Wild Boar
//
// @date: 2024-04-12
//--------------------------------------------------

#include "Distortion.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param imageSize The size of the image that we are working with
 */
Distortion::Distortion(const Size& imageSize)
{
	auto f = max(imageSize.width, imageSize.height) * 2;
	auto cx = imageSize.width * 0.5; auto cy = imageSize.height * 0.5;
	_camera = (Mat_<double>(3,3) << f, 0, cx, 0, f, cy, 0, 0, 1);
}

//--------------------------------------------------
// UnDistort
//--------------------------------------------------

/**
 * @brief Create an undistorted grid
 * @param grid The grid that we are dealing with
 * @param dparams The distortion parameters
 * @return Grid * Returns a Grid *
 */
Grid * Distortion::Undistort(Grid * grid, Mat& dparams)
{
	auto result = new Grid(grid->GetSize());

	for (auto row = 0; row < grid->GetRows(); row++) 
	{
		for (auto column = 0; column < grid->GetColumns(); column++) 
		{
			auto index = Point(column, row);
			auto scenePoint = grid->GetScenePoint(index);
			auto imagePoint = grid->GetImagePoint(index);

			auto input = vector<Point2d> { imagePoint }; auto output = vector<Point2d>();

			undistortPoints(input, output, _camera, dparams, noArray(), _camera);

			result->SetScenePoint(index, scenePoint);
			result->SetImagePoint(index, output[0]);
		}
	}

	return result;
}