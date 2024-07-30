//--------------------------------------------------
// Implementation of class LoadUtils
//
// @author: Wild Boar
//
// @date: 2024-07-30
//--------------------------------------------------

#include "LoadUtils.h"
using namespace NVL_App;


//--------------------------------------------------
// Board Params
//--------------------------------------------------

/**
 * @brief Load the board parameters from disk
 * @param pathHelper Helper for getting the location of files
 * @return unique_ptr<BoardParams> Returns a unique_ptr<BoardParams>
 */
unique_ptr<BoardParams> LoadUtils::LoadBoardParams(NVLib::PathHelper& pathHelper)
{
	auto path = pathHelper.GetPath("Meta", "board.xml");

	auto document = pugi::xml_document();
	auto success = document.load_file(path.c_str()); if (!success) throw runtime_error("Unable to open file: " + path);

	// Load the board_size
	auto sizeNode = document.child("opencv_storage").child("board_size");
	auto sizeValues = sizeNode.text();
	auto sizeParser = stringstream(sizeValues.as_string()); auto size = Size(); sizeParser >> size.width >> size.height;

	// Load the block_size
	auto blockSize = document.child("opencv_storage").child("block_size").text().as_int();

	// Load the marker size
	auto markerSize = document.child("opencv_storage").child("marker_size").text().as_int();

	// Load the dictionary setting
	auto dictionary = document.child("opencv_storage").child("dictionary").text().as_int();

	// Return the result
	return unique_ptr<BoardParams>(new BoardParams(size, blockSize, markerSize, dictionary));
}

//--------------------------------------------------
// Grid Points
//--------------------------------------------------

/**
 * @brief Load grid points from disk
 * @param pathHelper Helper for getting the location of files
 * @param boardSize The size of the board that we are loading
 * @param folder the folder that we are loading from
 * @param index The index of the grid that we are loading
 * @return unique_ptr<GridPoints> Returns a unique_ptr<GridPoints>
 */
unique_ptr<GridPoints> LoadUtils::LoadGrid(NVLib::PathHelper& pathHelper, const Size& boardSize, const string& folder, int index)
{
	auto fileName = stringstream(); fileName << "points_" << setw(4) << setfill('0') << index << ".txt";
	auto path = pathHelper.GetPath(folder, fileName.str());
	auto reader = ifstream(path); if (!reader.is_open()) throw runtime_error("Unable to open: " + path);

	auto result = new GridPoints(Size(boardSize.width - 1, boardSize.height - 1));

	for (auto row = 0; row < result->GetGridSize().height; row++) 
	{
		for (auto column = 0; column < result->GetGridSize().width; column++) 
		{
			auto line = string(); getline(reader, line);
			if (line == string()) throw runtime_error("Point file does not contain enough entries");
			auto parts = vector<string>(); NVLib::StringUtils::Split(line, ',', parts);
			if (parts.size() != 5) throw runtime_error("Input file does not appear to be in the correct format");
			
			auto values = vector<double>(); for (auto i = 0; i < parts.size(); i++) values.push_back(NVLib::StringUtils::String2Double(parts[i]));
			result->Update(Point2i(column, row), Point2d(values[3], values[4]), Point3d(values[0], values[1], values[2]));
		}
	}

	reader.close();

	return unique_ptr<GridPoints>(result);
}