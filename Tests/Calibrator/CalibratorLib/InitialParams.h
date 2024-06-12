//--------------------------------------------------
// The initial params used for the distortion estimation
//
// @author: Wild Boar
//
// @date: 2024-06-12
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

namespace NVL_App
{
	class InitialParams
	{
	private:
		Mat _camera;
		Mat _distortion;
		Size _imageSize;

	public:
		InitialParams(Mat& camera, Mat& distortion, Size& imageSize);
		InitialParams(const string& path);

		inline Mat& GetCamera() { return _camera; }
		inline Mat& GetDistortion() { return _distortion; }
		inline Size& GetImageSize() { return _imageSize; }
	};
}
