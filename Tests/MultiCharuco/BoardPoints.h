//--------------------------------------------------
// The detected points associated with a board
//
// @author: Wild Boar
//
// @date: 2024-02-14
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

namespace NVL_App
{
	class BoardPoints
	{
	private:
		vector<int> _indices;
		vector<vector<Point2f>> _corners;
	public:
		BoardPoints() {} 
		
		void Add(int index, vector<Point2f>& corner) { _indices.push_back(index); _corners.push_back(corner); }

		inline vector<int>& GetIndices() { return _indices; }
		inline vector<vector<Point2f>>& GetCorners() { return _corners; }
	};
}
