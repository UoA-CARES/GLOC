//--------------------------------------------------
// A set of utilities for loading values from the file
//
// @author: Wild Boar
//
// @date: 2024-04-19
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/Path/PathHelper.h>
#include "Settings.h"

namespace NVL_App
{
	class LoadUtils
	{
	public:
		static unique_ptr<Settings> LoadBoardSettings(NVLib::PathHelper * pathHelper);
	private:
		static NVL_App::Board * GetBoard(const string& line);
	};
}
