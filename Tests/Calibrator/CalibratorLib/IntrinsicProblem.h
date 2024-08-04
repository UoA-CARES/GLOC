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

#include "GridPoints.h"
#include "PinholeParams.h"

namespace NVL_App
{
	class IntrinsicProblem : public NVL_AI::ProblemBase
	{
	private:
		GridPoints * _grid1;
		GridPoints * _grid2;
	public:
		IntrinsicProblem(GridPoints * grid1, GridPoints * grid2);
		~IntrinsicProblem();

		virtual int GetDataSize();
		virtual double Evaluate(Mat& parameters, Mat& errors);

		inline GridPoints * GetGrid1() { return _grid1; }
		inline GridPoints * GetGrid2() { return _grid2; }
	};
}