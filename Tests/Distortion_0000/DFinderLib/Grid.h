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
		Grid(const Size& gridSize);

		int GetRows();
		int GetColumns();
		Size GetSize();
		
		Point2d GetImagePoint(const Point& location);
		Point3d GetScenePoint(const Point& location);

		void SetImagePoint(const Point& location, const Point2d& point);
		void SetScenePoint(const Point& location, const Point3d& point);

		inline Mat& GetData() { return _data; }
	};
}