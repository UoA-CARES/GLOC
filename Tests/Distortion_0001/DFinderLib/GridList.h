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

namespace NVL_App
{
	class GridList
	{
	private:
		vector<Grid *> _data;
	public:
		GridList() { /* extra implementation can go here */}
		~GridList() { for (auto grid : _data) delete grid; }
		inline void Add(Grid * grid) { _data.push_back(grid); }
		inline vector<Grid *>& GetData() { return _data; }
	};
}