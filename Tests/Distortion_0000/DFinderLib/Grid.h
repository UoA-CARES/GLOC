//--------------------------------------------------
// A grid formation for holding the points
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

namespace NVL_App
{
	class Grid
	{
	private:
		Mat _data;
	public:
		Grid(Mat& data);
		~Grid();

		int GetRows();
		int GetColumns();
		Point2d GetImagePoint(const Point& location);
		Point3d GetScenePoint(const Point& location);

		inline Mat& GetData() { return _data; }
	};
}