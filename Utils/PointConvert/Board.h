//--------------------------------------------------
// The details associated with a board
//
// @author: Wild Boar
//
// @date: 2024-04-19
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

namespace NVL_App
{
	class Board
	{
	private:
		Size _gridSize;
		Size _boardSize;

	public:
		Board(const Size& gridSize, const Size& boardSize) : _gridSize(gridSize), _boardSize(boardSize) {}

		inline Size& GetGridSize() { return _gridSize; }
		inline Size& GetBoardSize() { return _boardSize; }
	};
}
