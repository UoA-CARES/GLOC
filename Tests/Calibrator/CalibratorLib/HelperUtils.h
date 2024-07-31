//--------------------------------------------------
// A library of helper functions for this application
//
// @author: Wild Boar
//
// @date: 2024-07-31
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "Calibration.h"
#include "GridPoints.h"

namespace NVL_App
{
	class HelperUtils
	{
	public:
		static unique_ptr<GridPoints> Undistort(Calibration * calibration, GridPoints * points);
	};
}
