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
#include "GridList.h"
#include "Homography.h"
#include "CallbackBase.h"

namespace NVL_App
{
	class RandomSolver
	{
	private:
		Size _imageSize;
		Distortion * _distortion;
		GridList * _grids;
		double _bestScore;
		Mat _dparams;
		Vec2d _decenter;
	public:
		RandomSolver(const Size& imageSize, GridList * grids, Mat& dparams);
		~RandomSolver();

		double Solve(int maxIterators, int sensitivity = 100, CallbackBase * callback = nullptr);

		Mat GetCamera();
		Mat GetPoints(int cameraId);
		int GetCameraCount();

		inline Distortion * GetDistortion() { return _distortion; }
		inline double GetBestScore() { return _bestScore; }
		inline Mat& GetDParams() { return _dparams; }
	
	private:
		double GetNumber(int order);
		double CalculateScore(Mat& dparams, Mat& points, const Vec2d& decenter);
	};
}