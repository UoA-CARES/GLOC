//--------------------------------------------------
// The set of parameters containing key parameters about the calibration board
//
// @author: Wild Boar
//
// @date: 2024-07-30
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
		int _blockSize;
		int _markerSize;
		int _dictionary;
	public:
		BoardParams(const Size& boardSize, int blockSize, int markerSize, int dictionary) :
			_boardSize(boardSize), _blockSize(blockSize), _markerSize(markerSize), _dictionary(dictionary) {}

		inline Size& GetBoardSize() { return _boardSize; }
		inline int& GetBlockSize() { return _blockSize; }
		inline int& GetMarkerSize() { return _markerSize; }
		inline int& GetDictionary() { return _dictionary; }
	};
}
