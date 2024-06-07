//--------------------------------------------------
// The points that make up a general grid structure
//
// @author: Wild Boar
//
// @date: 2024-06-07
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include "opencv2/opencv.hpp"
using namespace cv;

namespace NVL_App
{
	class GridPoints
	{
	private:
		vector<Point2d> _imagePoints;
		vector<Point2d> _goalPoints;
		Size _gridSize;
		vector<bool> _setPoints;
		vector<double> _depth;
	public:
		GridPoints(Size& gridSize);

		void Update(const Point2i& position, const Point2d& imagePoint, const Point2d& goalPoint);
		void Update(const Point2i& position, const Point2d& imagePoint, const Point3d& goalPoint);

		Point2d GetImagePoint(const Point2i& position);
		Point2d GetGoalPoint2D(const Point2i& position);
		Point3d GetGoalPoint3D(const Point2i& position);
		bool IsPointSet(const Point2i& position);
		int GetPointCount();
		int GetSetPointCount();

		inline vector<Point2d>& GetImagePoints() { return _imagePoints; }
		inline vector<Point2d>& GetGoalPoints() { return _goalPoints; }
		inline Size& GetGridSize() { return _gridSize; }
		inline vector<bool>& GetSetPoints() { return _setPoints; }
		inline vector<double>& GetDepth() { return _depth; }
};
}
