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
	// Create a reader for reading in the data
	auto path = pathHelper->GetPath(folder, "points.txt");
	auto reader = ifstream(path); if (!reader.is_open()) throw runtime_error("Unable to open: " + path);

	// Create a row and column indices
	auto rowIndices = vector<double>(); auto columnIndices = vector<double>();

	// Data
	Mat pointData;

	// Create the file
	while(true) 
	{
		auto entry = vector<double>();
		auto valid = ReadLine(reader, entry); if (!valid) break;

		auto imagePoint = Point2d(entry[3], entry[4]); auto scenePoint = Point3d(entry[0], entry[1], entry[2]);

		if (scenePoint.z != 0) throw runtime_error("It is expected the all Z values are 0");

		UpdateVector(columnIndices, scenePoint.x); UpdateVector(rowIndices, scenePoint.y);

		auto row = Mat_<double>(1, 5, entry.data()); pointData.push_back(row);
	}

	// Close the reader
	reader.close();

	// Create the grid
	auto result = new Grid(Size(columnIndices.size(), rowIndices.size()));

	// Get the conversion factors
	auto xFactor = GetFactor(columnIndices); auto yFactor = GetFactor(rowIndices);

	// Create a link to the point data
	auto pLink = (double *) pointData.data;

	// Populate the grid with data
	for (auto row = 0; row < pointData.rows; row++) 
	{
		auto imagePoint = Point2d(pLink[row * 5 + 3], pLink[row * 5 + 4]);
		auto scenePoint = Point3d(pLink[row * 5 + 0], pLink[row * 5 + 1], pLink[row * 5 + 2]);

		auto gridX = (int) round(scenePoint.x / xFactor); auto gridY = (int) round(scenePoint.y / yFactor);

		result->SetImagePoint(Point(gridX, gridY), imagePoint); 
		result->SetScenePoint(Point(gridX, gridY), scenePoint);
	}

	// return the result
	return result;
}

//--------------------------------------------------
// Helper
//--------------------------------------------------

/**
 * @brief Read a line
 * @param reader The reader that we are using
 * @param values The line that we have read
 */
bool PointLoader::ReadLine(istream& reader, vector<double>& values)
{
	auto line = string(); getline(reader, line); if (line == string()) return false;

	auto parts = vector<string>(); NVLib::StringUtils::Split(line, ',', parts);
	if (parts.size() != 5) throw runtime_error("Invalid line in input: " + line);

	values.clear();

	for (auto i = 0; i < parts.size(); i++) 
	{
		auto value = NVLib::StringUtils::String2Double(parts[i]);
		values.push_back(value);
	}

	return true;
}

/**
 * @brief Update the index vector
 * @param indexVector The index vector that we are updating
 * @param value The new value that we are adding to the vector
 */
void PointLoader::UpdateVector(vector<double>& indexVector, double value)
{
	for (auto i = indexVector.begin(); i != indexVector.end(); i++) 
	{
		auto current = *i;
		if (current == value) return;

		if (current > value) 
		{
			indexVector.insert(i, value); return;
		}
	}

	indexVector.push_back(value);
}

/**
 * @brief Retrieve the conversion factor
 * @param indexVector The index helper that we are determining the update factor from
 * @return double Returns a double
 */
double PointLoader::GetFactor(const vector<double>& indexVector)
{
	if (indexVector[0] != 0) throw runtime_error("Get factor failed, it is expected that the first index is 0");

	// TODO: We could add consistency checking here!

	return indexVector[1];
}