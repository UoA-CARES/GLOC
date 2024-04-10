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

#include "NVLib/Path/PathHelper.h"
#include "Grid.h"

namespace NVL_App
{
	class PointLoader
	{
	public:
		static Grid * GetPoints(NVLib::PathHelper * pathHelper, const string& folder);
	private:
		static void ReadLine(istream& reader, vector<double>& values);
		static void UpdateVector(vector<double>& indexVector, double value);
		static double GetFactor(const vector<double>& indexVector);
	};
}
