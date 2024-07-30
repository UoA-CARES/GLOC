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
	throw runtime_error("Not implemented");
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
