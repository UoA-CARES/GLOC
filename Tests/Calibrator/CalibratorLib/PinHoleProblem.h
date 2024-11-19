//--------------------------------------------------
// The problem that we want to refine
//
// @author: Wild Boar
//
// @date: 2024-08-04
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <JarvisLib/Solver/ProblemBase.h>

#include <NVLib/PoseUtils.h>

#include "GridPoints.h"
#include "PinholeParams.h"

namespace NVL_App
{
	class PinHoleProblem : public NVL_AI::ProblemBase
	{
	private:
		GridPoints * _grid_1;
		GridPoints * _grid_2;
	public:
		PinHoleProblem(GridPoints * grid_1, GridPoints * grid_2);
		~PinHoleProblem();

		virtual int GetDataSize();
		virtual double Evaluate(Mat& parameters, Mat& errors);

		inline GridPoints * GetGrid1() { return _grid_1; }
		inline GridPoints * GetGrid2() { return _grid_2; }
	private:
		Mat GetCamera(Mat& parameters);
		Mat GetPose(Mat& parameters, int index);
	};
}