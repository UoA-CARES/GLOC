//--------------------------------------------------
// The functionality to load points from disk
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <NVLib/Path/PathHelper.h>
#include <NVLib/Formatter.h>
#include <NVLib/FileUtils.h>

#include "GridList.h"

namespace NVL_App
{
	class PointLoader
	{
	public:
		static int GetGridCount(NVLib::PathHelper * pathHelper);
		static Size GetImageSize(NVLib::PathHelper * pathHelper, const string& folder, const string& imageName);
		static unique_ptr<GridList> GetGridList(NVLib::PathHelper * pathHelper, int gridCount);
		static Grid * GetGrid(NVLib::PathHelper * pathHelper, const string& folder, int gridCount);
	private:
		static bool ReadLine(istream& reader, vector<double>& values);
		static void UpdateVector(vector<double>& indexVector, double value);
		static double GetFactor(const vector<double>& indexVector);
	};
}
