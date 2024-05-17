//--------------------------------------------------
// Implementation of class SaveUtils
//
// @author: Wild Boar
//
// @date: 2024-05-17
//--------------------------------------------------

#include "SaveUtils.h"
using namespace NVL_App;

//--------------------------------------------------
// Parameters
//--------------------------------------------------

/**
 * @brief The parameters that we are saving
 * @param helper The path that we are saving to
 * @param solver The parameter data that was refined
 */
void SaveUtils::SaveParams(NVLib::PathHelper * helper, RandomSolver * solver)
{
	// Create a path
	auto path = helper->GetPath("Distortion", "params.xml");

	// Open the writer
	auto writer = FileStorage(path, FileStorage::FORMAT_XML | FileStorage::WRITE);

	// Add value
	writer << "camera" << solver->GetCamera();
	writer << "distortion" << solver->GetDParams();

	// Close the writer
	writer.release();
}

//--------------------------------------------------
// Points
//--------------------------------------------------

/**
 * @brief Save the points that we are dealing with
 * @param helper The path that we are saving to
 * @param solver The parameter data was refined
 */
void SaveUtils::SavePoints(NVLib::PathHelper * helper, RandomSolver * solver)
{	
	for (auto i = 0; i < solver->GetCameraCount(); i++) 
	{
		auto fileName = stringstream(); fileName << "upoints_" << setw(4) << setfill('0') << i << ".txt";
		auto path = helper->GetPath("Distortion", fileName.str());

		Mat points = solver->GetPoints(i); auto link = (double *) points.data;

		auto writer = ofstream(path);

		for (auto row = 0; row < points.rows; row++) 
		{
			auto X = link[row * 5 + 0];
			auto Y = link[row * 5 + 1];
			auto Z = link[row * 5 + 2];
			auto u = link[row * 5 + 3];
			auto v = link[row * 5 + 4];
			writer << X << "," << Y << "," << Z << "," << u << "," << v << endl;
		}

		writer.close();
	}
}