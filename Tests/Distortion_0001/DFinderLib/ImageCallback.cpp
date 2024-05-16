//--------------------------------------------------
// Implementation of class ImageCallback
//
// @author: Wild Boar
//
// @date: 2024-04-15
//--------------------------------------------------

#include "ImageCallback.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param basePoints The base point
 */
ImageCallback::ImageCallback(const Mat& basePoints) : CallbackBase(), _basePoints(basePoints)
{
	// Main Constructor
}

//--------------------------------------------------
// Callback
//--------------------------------------------------

/**
 * @brief The callback method that we are using
 * @param iteration The current iteration identifier
 * @param aveError The average error associated with the system
 * @param parameters The parameters associated with the test case
 * @param data Additional data associated with the system
 */
void ImageCallback::Callback(int iteration, double aveError, const Mat& parameters, const Mat& data)
{
	Mat display = Mat_<Vec3d>::zeros(1000,1000);
	auto pixelCount = _basePoints.rows * _basePoints.cols;

	auto points = vector<Point>();

	auto oLink = (double *) _basePoints.data;
	auto iLink = (double *) data.data;

	for (auto i = 0; i < data.rows; i++) 
	{
		auto x = (int)round(oLink[2 * i + 0]);
		auto y = (int)round(oLink[2 * i + 1]);
		circle(display, Point(x,y), 5, Scalar(0,0,255), FILLED);

		auto u = (int)round(iLink[2 * i + 0]);
		auto v = (int)round(iLink[2 * i + 1]);
		circle(display, Point(u,v), 8, Scalar(0,255,0),3);
	}

	cout << iteration << ". " << parameters.t() << ": " << aveError << endl;
	
	imshow("Point", display); waitKey();
}
