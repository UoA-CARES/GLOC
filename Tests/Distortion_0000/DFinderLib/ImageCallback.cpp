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
ImageCallback::ImageCallback(Mat& basePoints)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Callback
//--------------------------------------------------

/**
 * @brief The callback method that we are using
 * @param aveError The average error associated with the system
 * @param parameters The parameters associated with the test case
 * @param data Additional data associated with the system
 */
void ImageCallback::Callback(double aveError, Mat& parameters, Mat& data)
{
	throw runtime_error("Not implemented");
}
