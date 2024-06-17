//--------------------------------------------------
// An implementation of a refiner for the pinhole parameters
//
// @author: Wild Boar
//
// @date: 2024-06-17
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "GridPoints.h"

namespace NVL_App
{
	class PinholeParams
	{
	private:
		Mat _camera;
		Vec3d _rvec;
		Vec3d _tvec;
	public:
		PinholeParams(Mat camera, Mat pose);

		virtual double CalculateError(GridPoints * points, vector<double>& errors);

		virtual void SetState(vector<double>& variables);

		Mat GetPoseMatrix( );

		inline Mat& GetCamera() { return _camera; }
		inline Vec3d& GetRvec() { return _rvec; }
		inline Vec3d& GetTvec() { return _tvec; }
	};
}
