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
PinholeParams::PinholeParams(Mat camera, Mat pose) : _camera(camera)
{
	NVLib::PoseUtils::Pose2Vectors(pose, _rvec, _tvec);
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
	auto result = 0.0; errors.clear();

	auto grid = points->GetGridSize();

	for (auto row = 0; row < grid.height; row++) 
	{
		for (auto column = 0; column < grid.width; column++) 
		{
			auto position = Point2i(column, row);
			auto isSet = points->IsPointSet(position); if (!isSet) continue;
			auto scenePoint = points->GetGoalPoint3D(position);
			auto imagePoint = points->GetImagePoint(position);

			auto pose = GetPoseMatrix();
			auto tscenePoint = NVLib::Math3D::TransformPoint(pose, scenePoint);

			auto actual = NVLib::Math3D::Project(_camera, tscenePoint);
			auto error = NVLib::Math2D::GetDistance(imagePoint, actual);
			result += error; errors.push_back(error);
			
		}
	}

	return result;
}

//--------------------------------------------------
// Pose
//--------------------------------------------------

/**
 * @brief Retrieve the pose as a matrix
 * @return Mat Returns a Mat
 */
Mat PinholeParams::GetPoseMatrix()
{
	return NVLib::PoseUtils::Vectors2Pose(_rvec, _tvec);
}
