//--------------------------------------------------
// A list of grids
//
// @author: Wild Boar
//
// @date: 2024-05-15
//--------------------------------------------------

#pragma once

#include <vector>
#include <iostream>
using namespace std;

#include "Grid.h"
#include "Distortion.h"

namespace NVL_App
{
	class GridList
	{
	private:
		vector<Grid *> _data;
	public:
		GridList() { /* extra implementation can go here */}
		~GridList() { for (auto grid : _data) delete grid; }
		inline int GetCount() { return _data.size(); }
		inline void Add(Grid * grid) { _data.push_back(grid); }

		inline Mat GetImagePoints(const Size& imageSize, Mat& dparams) 
		{
			// If no data, then return nothing
			if (_data.size() <= 0) return Mat();

			// Create a distortion element
			auto distortion = Distortion(imageSize);

			// Setup the first came
			Mat result = GetImagePoints(_data[0], distortion, dparams);

			// Add the remaining grids
			for (auto i = 1; i < _data.size(); i++) 
			{
				Mat update = GetImagePoints(_data[i], distortion, dparams);
				vconcat(result, update, result);
			}

			// Remove image points
			return result;
		}
		
		inline vector<Grid *>& GetData() { return _data; }

	private:
		inline Mat GetImagePoints(Grid * grid, Distortion& distortion, Mat& dparams) 
		{
			Grid * ugrid = distortion.Undistort(grid, dparams);
			Mat result = ugrid->GetImagePointMatrix();
			delete ugrid;

			return result;
		}
	};
}