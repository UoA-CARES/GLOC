//--------------------------------------------------
// Defines a solver that uses a type of random search to find distortion parameters
//
// @author: Wild Boar
//
// @date: 2024-04-12
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/RandomUtils.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "Distortion.h"
#include "Grid.h"
#include "Homography.h"
#include "CallbackBase.h"

namespace NVL_App
{
	class RandomSolver
	{
	private:
		Distortion * _distortion;
		Grid * _grid;
		double _bestScore;
		Mat _dparams;
	public:
		RandomSolver(const Size& imageSize, Grid * grid, Mat& dparams);
		~RandomSolver();

		double Solve(int maxIterators, CallbackBase * callback = nullptr);

		inline Distortion * GetDistortion() { return _distortion; }
		inline Grid * GetGrid() { return _grid; }
		inline double GetBestScore() { return _bestScore; }
		inline Mat& GetDParams() { return _dparams; }
	
	private:
		double GetNumber(int order);
	};
}