//--------------------------------------------------
// Implementation of class HelperUtils
//
// @author: Wild Boar
//
// @date: 2024-07-31
//--------------------------------------------------

#include "HelperUtils.h"
using namespace NVL_App;


//--------------------------------------------------
// Undistort
//--------------------------------------------------

/**
 * @brief Remove the distortion from given points
 * @param calibration The calibration that we are dealing with
 * @param points The points that we are undistorting
 * @return unique_ptr<GridPoints> Returns a unique_ptr<GridPoints>
 */
unique_ptr<GridPoints> HelperUtils::Undistort(Calibration * calibration, GridPoints * points)
{
	throw runtime_error("Not implemented");
}
