//--------------------------------------------------
// The associated parameters for a Charuco Board
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
	class BoardParams
	{
	private:
		Size _boardSize;
		double _blockSize;
		double _markerSize;
		int _dictionary;
	public:
		BoardParams(Size& boardSize, double blockSize, double markerSize, int dictionary) :
			_boardSize(boardSize), _blockSize(blockSize), _markerSize(markerSize), _dictionary(dictionary) {}

		inline Size& GetBoardSize() { return _boardSize; }
		inline double& GetBlockSize() { return _blockSize; }
		inline double& GetMarkerSize() { return _markerSize; }
		inline int& GetDictionary() { return _dictionary; }
	};
}
