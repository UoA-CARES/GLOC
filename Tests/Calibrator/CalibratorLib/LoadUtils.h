//--------------------------------------------------
// A utility for loading resources from disk
//
// @author: Wild Boar
//
// @date: 2024-07-30
//--------------------------------------------------

#pragma once

#include <sstream>
#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <pugixml.hpp>

#include <NVLib/Path/PathHelper.h>
#include "BoardParams.h"
#include "GridPoints.h"

namespace NVL_App
{
	class LoadUtils
	{
	public:
		static unique_ptr<BoardParams> LoadBoardParams(NVLib::PathHelper& pathHelper);
		static unique_ptr<GridPoints> LoadGrid(NVLib::PathHelper& pathHelper, const Size& boardSize, const string& folder, int index);
	};
}