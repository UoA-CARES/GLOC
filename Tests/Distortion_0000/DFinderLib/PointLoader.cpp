//--------------------------------------------------
// Implementation of class PointLoader
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#include "PointLoader.h"
using namespace NVL_App;


//--------------------------------------------------
// Load
//--------------------------------------------------

/**
 * @brief Add the functionality to load points from disk
 * @param pathHelper A helper for setting up the path for finding the points file
 * @param folder The folder in which we are searching for results
 * @return Grid * Returns a Grid *
 */
Grid * PointLoader::GetPoints(NVLib::PathHelper * pathHelper, const string& folder)
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Helper
//--------------------------------------------------

/**
 * @brief Read a line
 * @param reader The reader that we are using
 * @param values The line that we have read
 */
void PointLoader::ReadLine(istream& reader, vector<double>& values)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Update the index vector
 * @param indexVector The index vector that we are updating
 * @param value The new value that we are adding to the vector
 */
void PointLoader::UpdateVector(vector<double>& indexVector, double value)
{
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the conversion factor
 * @param indexVector The index helper that we are determining the update factor from
 * @return double Returns a double
 */
double PointLoader::GetFactor(const vector<double>& indexVector)
{
	throw runtime_error("Not implemented");
}
