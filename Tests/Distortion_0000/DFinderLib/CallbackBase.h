//--------------------------------------------------
// 
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

namespace NVL_App
{
	class CallbackBase
	{
	public:
		CallbackBase() {}
		virtual void Callback(double aveError, Mat& parameters, Mat& data) = 0;
	};
}
