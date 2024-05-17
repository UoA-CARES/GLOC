//--------------------------------------------------
// Save the utils that we are dealing with
//
// @author: Wild Boar
//
// @date: 2024-05-17
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/FileUtils.h>
#include <NVLib/Path/PathHelper.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "RandomSolver.h"

namespace NVL_App
{
	class SaveUtils
	{
	public:
		static void SaveParams(NVLib::PathHelper * helper, RandomSolver * solver);
		static void SavePoints(NVLib::PathHelper * helper, RandomSolver * solver);
	};
}