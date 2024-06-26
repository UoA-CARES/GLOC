//--------------------------------------------------
// Implementation of class RandomSolver
//
// @author: Wild Boar
//
// @date: 2024-04-12
//--------------------------------------------------

#include "RandomSolver.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param imageSize The size of the image that we are dealing
 * @param grid The grid parameters that we measured
 * @param dparams The list of parameters that we a dealing with
 */
RandomSolver::RandomSolver(const Size& imageSize, Grid * grid, Mat& dparams) : _grid(grid), _dparams(dparams)
{
	NVLib::RandomUtils::TimeSeedRandomNumbers();

	_distortion = new Distortion(imageSize);
	Mat H = Homography::GetHomography(_grid);
	_bestScore = Homography::GetHScore(H, _grid);
}

/**
 * @brief Main Terminator
 */
RandomSolver::~RandomSolver()
{
	delete _distortion;
}

//--------------------------------------------------
// Solver
//--------------------------------------------------

/**
 * @brief Attempt to iterate and find solution
 * @param maxIterators The maximum number of iterations to try
 * @param sensitivity Indicate when the updates can timeout
 * @param callback If one is supplied, it is raised everytime a significant event occurs
 * @return double Returns a double
 */
double RandomSolver::Solve(int maxIterators, int sensitivity, CallbackBase * callback)
{
	Mat dparams = _dparams.clone(); 
	
	auto dlink_1 = (double *) dparams.data;
	auto dlink_2 = (double *) _dparams.data;

	int noUpdate = 0;

	for (auto i = 0; i < maxIterators; i++) 
	{
		for (auto j = 0; j < 4; j++) dlink_1[j] = dlink_2[j];

		auto order = NVLib::RandomUtils::GetInteger(0, 2);
		auto index = NVLib::RandomUtils::GetInteger(0, 4);
		auto delta = GetNumber(order);

		dlink_1[index] += delta;

		auto grid = _distortion->Undistort(_grid, dparams);
		Mat H = Homography::GetHomography(grid);
		auto score = Homography::GetHScore(H, grid);
	
		if (score < _bestScore) 
		{
			_bestScore = score;
			
			if (callback != nullptr) 
			{
				Mat pointMat = grid->GetImagePointMatrix();
				callback->Callback(i, score, dparams, pointMat);
			}

			for (auto j = 0; j < 4; j++) dlink_2[j] = dlink_1[j];

			noUpdate = 0;
		}
		else noUpdate++;

		delete grid;

		if (noUpdate >= sensitivity) break;
	}

	return _bestScore;
}

//--------------------------------------------------
// Solver
//--------------------------------------------------

/**
 * Get the image points that we are dealing with
 * @return A matrix containing the image points
*/
Mat RandomSolver::GetImagePoints() 
{
	auto grid = _distortion->Undistort(_grid, _dparams);
	Mat result = grid->GetImagePointMatrix();
	delete grid;

	return result;
}

//--------------------------------------------------
// Solver
//--------------------------------------------------

/**
 * Get a random generator
 * @param order The order that we are dealing
 * @return The delta 
 */
double RandomSolver::GetNumber(int order) 
{
	auto number = NVLib::RandomUtils::GetInteger(-1000, 1000) / 1000.0;
	auto factor = 1.0; for (auto i = 0; i < order; i++) factor /= 10.0;
	return number * factor;
}