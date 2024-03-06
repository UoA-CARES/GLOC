//--------------------------------------------------
// The list of arguments that serve as input for the application
//
// @author: Wild Boar
//
// @date: 2024-03-06
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

namespace NVL_App
{
	class Arguments
	{
	private:
		double _focal;
		Size _imageSize;
		Mat _distortion;
		Vec3d _rvec;
		Vec3d _tvec;
		Vec2d _blockSize;
		Vec2i _gridSize;
		string _folder;
	public:
		Arguments(double focal, Size& imageSize, Mat& distortion, Vec3d& rvec, Vec3d& tvec, Vec2d& blockSize, Vec2i& gridSize, const string& folder) :
			_focal(focal), _imageSize(imageSize), _distortion(distortion), _rvec(rvec), _tvec(tvec), _blockSize(blockSize), _gridSize(gridSize), _folder(folder) {}

		inline double& GetFocal() { return _focal; }
		inline Size& GetImageSize() { return _imageSize; }
		inline Mat& GetDistortion() { return _distortion; }
		inline Vec3d& GetRvec() { return _rvec; }
		inline Vec3d& GetTvec() { return _tvec; }
		inline Vec2d& GetBlockSize() { return _blockSize; }
		inline Vec2i& GetGridSize() { return _gridSize; }
		inline string& GetFolder() { return _folder; }
	};
}
