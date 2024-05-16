//--------------------------------------------------
// A helper class for Homography type operations
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

#include "Grid.h"

namespace NVL_App
{
	class Homography
	{
	public:
		static Mat GetHomography(Grid * grid);
		static unique_ptr<Grid> GetGrid(Grid * grid, Mat& H);
		static double GetHScore(Mat& H, Grid * grid);
		static Point2d Transform(Mat& H, const Point2d& point);
	private:
		static Point2f Convert(const Point2d& point);
		static Point2f Convert(const Point3d& point);
	};
}