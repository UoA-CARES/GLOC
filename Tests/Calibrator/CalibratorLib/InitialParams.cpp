//--------------------------------------------------
// Implementation of class InitialParams
//
// @author: Wild Boar
//
// @date: 2024-06-12
//--------------------------------------------------

#include "InitialParams.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param camera Initialize variable <camera>
 * @param distortion Initialize variable <distortion>
 * @param imageSize Initialize variable <imageSize>
 */
InitialParams::InitialParams(Mat& camera, Mat& distortion, Size& imageSize)
{
	_camera = camera;
	_distortion = distortion;
	_imageSize = imageSize;
}

/**
 * @brief Custom Constructor
 * @param path Load the data from file
 */
InitialParams::InitialParams(const string& path)
{
	throw runtime_error("Not implemented");
}
