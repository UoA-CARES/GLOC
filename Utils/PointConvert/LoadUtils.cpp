//--------------------------------------------------
// Implementation of class LoadUtils
//
// @author: Wild Boar
//
// @date: 2024-04-19
//--------------------------------------------------

#include "LoadUtils.h"
using namespace NVL_App;

//--------------------------------------------------
// Board
//--------------------------------------------------

/**
 * @brief Load board settings
 * @param pathHelper A handle for finding the path
 * @return Settings * Returns a Settings *
 */
unique_ptr<Settings> LoadUtils::LoadBoardSettings(NVLib::PathHelper * pathHelper)
{
	// Build image path
	auto path = pathHelper->GetPath("Tool_Output", "calibration..txt");

	// Create a reader
	auto reader = ifstream(path); if (!reader.is_open()) throw runtime_error("Unable to open: " + path);

	// Read the calibration count
	auto line_1 = string(); getline(reader, line_1);

	// Read the first calibration file
	auto line_2 = string(); getline(reader, line_2);

	// Read the first board
	auto line_3 = string(); getline(reader, line_3);
	auto board_1 = GetBoard(line_3);

	// Read the second calibration file
	auto line_4 = string(); getline(reader, line_4);

	// Reader the second board
	auto line_5 = string(); getline(reader, line_5);
	auto board_2 = GetBoard(line_5);

	// Close the reader
	reader.close();

	// Return the board
	return unique_ptr<Settings>(new Settings(board_1, board_2));
}

/**
 * Get board details embedded in the line
 * @param line The line that embeds board parameters
 * @return The extracted board parameters
*/
NVL_App::Board * LoadUtils::GetBoard(const string& line) 
{
	auto i = 0, gridRows = 0, gridCols = 0; auto blockRows = 0.0, blockCols = 0.0;
	auto stream = stringstream(line); stream >> i >> gridRows >> gridCols >> blockRows >> blockCols;
	return new NVL_App::Board(Size(gridCols, gridRows), Size(blockCols, blockRows));
}

//--------------------------------------------------
// Load Grid
//--------------------------------------------------

/**
 * Load the points for the grid
 * @param pHelper The associated path helper
 * @param settings The settings describing the grid elements
 * @param cameraId The camera that we want the points for
 * @param gridId The grid that we are dealing with
 * @return The points that have been loaded
*/
unique_ptr<Grid> LoadUtils::LoadGrid(NVLib::PathHelper * pHelper, Settings * settings, int cameraId, int gridId) 
{
	// Define the name of the points file
	auto fileName = stringstream(); fileName << "Camera_" << cameraId << "Points_" << gridId << ".txt";

	// Defines the path to the points files
	auto path = pHelper->GetPath("Tool_Output", fileName.str());

	// Create variables to hold points
	auto imagePoints = vector<Point2d>(); auto scenePoints = vector<Point3d>();

	// Open the points file
	auto reader = ifstream(path); if (!reader.is_open()) throw runtime_error("Unable to open file: " + path);

	// Get the relevant board parameters
	auto board = settings->GetBoard(cameraId + 1);

	// Conduct the actual loading stuff
	for (auto row = 0; row < board->GetGridSize().height; row++) 
	{
		for (auto column = 0; column < board->GetGridSize().width; column++) 
		{
			auto u = 0.0, v = 0.0; reader >> u >> v;
			auto X = column * board->GetBoardSize().width;
			auto Y = row * board->GetBoardSize().height;
			auto Z = 0.0;

			imagePoints.push_back(Point2d(u,v)); scenePoints.push_back(Point3d(X, Y, Z));
		}
	}

	// close the file
	reader.close();

	// Return the result
	return unique_ptr<Grid>(new Grid(scenePoints, imagePoints));
}