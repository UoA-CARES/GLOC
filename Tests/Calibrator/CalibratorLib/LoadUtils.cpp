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
 * @param folder the folder that we are loading from
 * @param index The index of the grid that we are loading
 * @return unique_ptr<GridPoints> Returns a unique_ptr<GridPoints>
 */
unique_ptr<GridPoints> LoadUtils::LoadGrid(NVLib::PathHelper& pathHelper, const string& folder, int index)
{
	throw runtime_error("Not implemented");
}
