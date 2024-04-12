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
	_distortion = new Distortion(imageSize);
	Mat H = Homography::GetHomography(_grid);
	_bestScore = Homography::GetHScore(H, _grid);
}

/**
 * @brief Main Terminator
 */
RandomSolver::~RandomSolver()
{
	delete _grid; delete _distortion;
}

//--------------------------------------------------
// Solver
//--------------------------------------------------

/**
 * @brief Attempt to iterate and find solution
 * @param maxIterators The maximum number of iterations to try
 * @param verbose Indicates whether we want to see some console outputs
 * @return double Returns a double
 */
double RandomSolver::Solve(int maxIterators, bool verbose)
{
	throw runtime_error("Not implemented");
}
