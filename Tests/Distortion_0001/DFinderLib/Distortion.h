//--------------------------------------------------
// A wrapper for the distortion logic
//
// @author: Wild Boar
//
// @date: 2024-04-12
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/Math3D.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "Grid.h"

namespace NVL_App
{
	class Distortion
	{
	private:
		Mat _camera;
	public:
		Distortion(const Size& imagesize);
		unique_ptr<Grid> Undistort(Grid * grid, Mat& dparams);
		unique_ptr<Grid> Distort(Grid * grid, Mat& dparams);

		inline Mat& GetCamera() { return _camera; }
	private:
		void BuildProjectInput(Mat& invCamera, const Point2d& point, vector<Point3d>& output);
	};
}