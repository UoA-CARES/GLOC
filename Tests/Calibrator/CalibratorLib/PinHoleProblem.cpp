//--------------------------------------------------
// Implementation of class PinHoleProblem
//
// @author: Wild Boar
//
// @date: 2024-08-04
//--------------------------------------------------

#include "PinHoleProblem.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param grid_1 Initialize variable <grid1>
 * @param grid_2 Initialize variable <grid2>
 */
PinHoleProblem::PinHoleProblem(GridPoints * grid1, GridPoints * grid2) : ProblemBase()
{
	_grid_1 = grid1;
	_grid_2 = grid2;
}

/**
 * @brief Main Terminator
 */
PinHoleProblem::~PinHoleProblem()
{
	// Extra terminational logic
}

//--------------------------------------------------
// DataSize
//--------------------------------------------------

/**
 * @brief Get the size of the data that we are processing
 * @return int Returns a int
 */
int PinHoleProblem::GetDataSize()
{
	return _grid_1->GetPointCount() + _grid_2->GetPointCount();
}

//--------------------------------------------------
// Evaluate
//--------------------------------------------------

/**
 * @brief Evaluate a particular parameter setup in terms of the grids
 * @param parameters The parameters that we are evaluating
 * @param errors The individual erros associated with each point
 * @return double Returns a double
 */
double PinHoleProblem::Evaluate(Mat& parameters, Mat& errors)
{
	// Decode the parameters
	auto camera = GetCamera(parameters);
	auto pose_1 = GetPose(parameters, 0); 
	auto pose_2 = GetPose(parameters, 1);

	// Testing
	cout << "CAMERA: " << camera << endl << endl;
	cout << "POSE_1: " << pose_1 << endl << endl;
	cout << "POSE_2: " << pose_2 << endl << endl;

	// Get the pinhole parameters
	auto parameters_1 = PinholeParams(camera, pose_1);
	auto parameters_2 = PinholeParams(camera, pose_2);

	// Find the errors
	auto errors_1 = vector<double>(); auto score_1 = parameters_1.CalculateError( _grid_1, errors_1 );
	auto errors_2 = vector<double>(); auto score_2 = parameters_2.CalculateError( _grid_2, errors_2 );

	// Update the errors matrix
	for (auto error : errors_1) errors.push_back(error);
	for (auto error : errors_2) errors.push_back(error);

	// Return the error score
	return score_1 + score_2;
}

/**
 * Retrieve the associated camera matrix
 * @param parameters The parameters that we are getting the camera matrix for
 * @return The camera matrix as a matrix
 */
Mat PinHoleProblem::GetCamera(Mat& parameters) 
{
	assert(parameters.rows >= 4);
	auto link = (double *) parameters.data;
	auto fx = link[0], fy = link[1], cx = link[2], cy = link[3];
	return (Mat_<double>(3,3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
}

/**
 * Get the pose that we are dealing with
 * @param parameters The parameters that we are getting the camera matrix for
 * @param index The index that we dealing with
 * @return The pose matrix
 */
Mat PinHoleProblem::GetPose(Mat& parameters, int index) 
{
	auto offset = 4 + index * 6; assert(parameters.rows > offset + 5); 
	auto link = (double *) parameters.data;
	auto rx = link[offset + 0], ry = link[offset + 1], rz = link[offset + 2];
	auto tx = link[offset + 3], ty = link[offset + 4], tz = link[offset + 5];
	auto rvec = Vec3d(rx, ry, rz); auto tvec = Vec3d(tx,ty,tz);
	return NVLib::PoseUtils::Vectors2Pose(rvec, tvec);
}
