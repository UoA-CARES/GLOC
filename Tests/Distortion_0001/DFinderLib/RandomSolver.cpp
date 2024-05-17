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
 * @param grids The list of grids that we are saving for
 * @param dparams The list of parameters that we a dealing with
 */
RandomSolver::RandomSolver(const Size& imageSize, GridList * grids, Mat& dparams) : _grids(grids), _dparams(dparams), _imageSize(imageSize), _decenter(Vec2d())
{
	NVLib::RandomUtils::TimeSeedRandomNumbers(); assert(grids->GetCount() > 0);
	_distortion = new Distortion(imageSize);
	Mat pointMat; _bestScore = CalculateScore(dparams, pointMat, _decenter);
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
		for (auto j = 0; j < _dparams.rows; j++) dlink_1[j] = dlink_2[j];

		auto order = NVLib::RandomUtils::GetInteger(0, 2);
		auto index = NVLib::RandomUtils::GetInteger(0, _dparams.rows);
		auto delta = GetNumber(order);

		dlink_1[index] += delta;

		auto decenterMode = NVLib::RandomUtils::GetInteger(0,4);
		auto deltaX = GetNumber(1);
		auto deltaY = GetNumber(1);

		auto decenter = Vec2d(_decenter[0], _decenter[1]);

		if (decenterMode == 0) decenter[0] += deltaX;
		else if (decenterMode == 1) decenter[1] += deltaY;

		Mat pointMat; auto score = CalculateScore(dparams, pointMat, decenter);
	
		if (score < _bestScore) 
		{
			_bestScore = score;
			
			if (callback != nullptr) 
			{
				callback->Callback(i, score, dparams, pointMat);
			}

			for (auto j = 0; j < _dparams.rows; j++) dlink_2[j] = dlink_1[j];
			_decenter = decenter;

			noUpdate = 0;
		}
		else noUpdate++;

		if (noUpdate >= sensitivity) break;
	}

	return _bestScore;
}


//--------------------------------------------------
// Get Camera Matrix
//--------------------------------------------------

/**
 * Get the camera matrix
 * @return The result that we are saving
*/
Mat RandomSolver::GetCamera() 
{
	Mat camera = _distortion->GetCamera().clone();
	auto c_link = (double *) camera.data;
	c_link[2] += _decenter[0]; c_link[5] += _decenter[1];
	return camera;
}

//--------------------------------------------------
// Get the points
//--------------------------------------------------

/**
 * The points that we are dealing with
 * @param cameraId The camera identifier that we are dealing with
 * @return The points that we are dealing with
*/
Mat RandomSolver::GetPoints(int cameraId) 
{
	if (cameraId < 0 || cameraId > _grids->GetCount()) throw runtime_error("CameraId is out of range");
	
	auto grid = _grids->GetData()[cameraId];
	auto ugrid = _distortion->Undistort(grid, _dparams, _decenter);
	Mat H = Homography::GetHomography(ugrid.get());
	auto hgrid = Homography::GetGrid(grid, H);

	auto pointCount = hgrid->GetData().rows * hgrid->GetData().cols;
	auto d_link = (double *) hgrid->GetData().data;

	Mat result = Mat_<double>::zeros(pointCount, 5);
	auto m_link = (double *) result.data;

	for (auto row = 0; row < pointCount; row++) 
	{
		auto u = d_link[row * 5 + 0];
		auto v = d_link[row * 5 + 1];
		auto X = d_link[row * 5 + 2];
		auto Y = d_link[row * 5 + 3];
		auto Z = d_link[row * 5 + 4];

		m_link[row * 5 + 0] = X;
		m_link[row * 5 + 1] = Y;
		m_link[row * 5 + 2] = Z;
		m_link[row * 5 + 3] = u;
		m_link[row * 5 + 4] = v;
	}

	return result;
}

/**
 * Retrieve the number of cameras that we are dealing with
 * @return The number of cameras
*/
int RandomSolver::GetCameraCount() 
{
	return _grids->GetCount();
}

//--------------------------------------------------
// Helper: Calculate scores
//--------------------------------------------------

/**
 * Global logic for calculating the score
 * @param dparams The distortion parameters
 * @param points The current point matrix
 * @param decenter The decentering parameters
 * @return The overall error
*/
double RandomSolver::CalculateScore(Mat & dparams, Mat& points, const Vec2d& decenter) 
{
	auto totalScore = 0.0;

	Mat pointMat;

	for (auto grid : _grids->GetData())
	{
		auto ugrid = _distortion->Undistort(grid, dparams, decenter);
		Mat H = Homography::GetHomography(ugrid.get());
		auto hgrid = Homography::GetGrid(grid, H);
		auto dgrid = _distortion->Distort(hgrid.get(), dparams, decenter);
		auto score = grid->GetDifference(dgrid.get());
		totalScore += score;
		
		if (pointMat.empty()) pointMat = dgrid->GetImagePointMatrix();
		else 
		{
			Mat update = dgrid->GetImagePointMatrix();
			vconcat(pointMat, update, pointMat);
		}
	}

	points = pointMat;

	return totalScore;
}

//--------------------------------------------------
// Helper: Get Random Number
//--------------------------------------------------

/**
 * Get a random generator
 * @param order The order that we are dealing
 * @return The delta 
 */
double RandomSolver::GetNumber(int order) 
{
	auto number = NVLib::RandomUtils::GetInteger(-1000, 1000) / 1000.0;
	auto factor = 10; for (auto i = 0; i < order; i++) factor /= 10.0;
	return number * factor;
}