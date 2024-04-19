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