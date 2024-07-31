//--------------------------------------------------
// Container for holding calibration details
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

namespace NVL_App
{
	class Calibration
	{
	private:
		Mat _camera;
		Mat _distortion;
		Size _imageSize;
	public:
		Calibration(Mat& camera, Mat& distortion, Size& imageSize) :
			_camera(camera), _distortion(distortion), _imageSize(imageSize) {}

		inline Mat& GetCamera() { return _camera; }
		inline Mat& GetDistortion() { return _distortion; }
		inline Size& GetImageSize() { return _imageSize; }
	};
}