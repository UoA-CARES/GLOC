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

#include <NVLib/PoseUtils.h>
#include <NVLib/Math2D.h>
#include <NVLib/Math3D.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "GridPoints.h"
#include "RefineResult.h"

namespace NVL_App
{
	class PinholeParams : public RefineResult
	{
	private:
		Mat _camera;
		Vec3d _rvec;
		Vec3d _tvec;
	public:
		PinholeParams(Mat camera, Mat pose);

		virtual double CalculateError(GridPoints * points, vector<double>& errors) override;
		virtual void SetState(vector<double>& variables) override;

		Mat GetPoseMatrix();

		inline Mat& GetCamera() { return _camera; }
		inline Vec3d& GetRvec() { return _rvec; }
		inline Vec3d& GetTvec() { return _tvec; }
	};
}
