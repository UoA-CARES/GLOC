//--------------------------------------------------
// Implementation of class PinholeParams
//
// @author: Wild Boar
//
// @date: 2024-06-17
//--------------------------------------------------

#include "PinholeParams.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param camera The camera matrix that we are using
 * @param pose The pose matrix that we are storing
 */
PinholeParams::PinholeParams(Mat camera, Mat pose)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Error
//--------------------------------------------------

/**
 * @brief Calculate the current error
 * @param points The grid points that we are processing
 * @param errors The set of errors that we are adding
 * @return double Returns a double
 */
double PinholeParams::CalculateError(GridPoints * points, vector<double>& errors)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// State
//--------------------------------------------------

/**
 * @brief Set the state as a vector
 * @param variables The variables with we are adding
 */
void PinholeParams::SetState(vector<double>& variables)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Pose
//--------------------------------------------------

/**
 * @brief Retrieve the pose as a matrix
 * @return Mat Returns a Mat
 */
Mat PinholeParams::GetPoseMatrix( )
{
	throw runtime_error("Not implemented");
}
