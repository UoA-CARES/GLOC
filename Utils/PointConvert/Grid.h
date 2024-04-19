//--------------------------------------------------
// Defines a grid within the system
//
// @author: Wild Boar
//
// @date: 2024-04-20
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
		vector<Point3d> _scenePoints;
		vector<Point2d> _imagePoints;
	public:
		Grid(vector<Point3d>& scenePoints, vector<Point2d>& imagePoints) :
			_scenePoints(scenePoints), _imagePoints(imagePoints) {}

		inline vector<Point3d>& GetScenePoints() { return _scenePoints; }
		inline vector<Point2d>& GetImagePoints() { return _imagePoints; }
	};
}
