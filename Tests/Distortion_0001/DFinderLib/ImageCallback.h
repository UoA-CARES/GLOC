//--------------------------------------------------
// Defines a callback for images
//
// @author: Wild Boar
//
// @date: 2024-04-15
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "CallbackBase.h"

namespace NVL_App
{
	class ImageCallback : public CallbackBase
	{
	private:
		Mat _basePoints;
	public:
		ImageCallback(const Mat& basePoints);
		virtual void Callback(int iteration, double aveError, const Mat& parameters, const Mat& data) override;
	};
}