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
			Vec2d _rvec;
			Vec2d _tvec;
			Vec2d _BlockSize;
			Vec2d _GridSize;
			string _folder;
		public:
			Arguments(double focal, Size& imageSize, Mat& distortion, Vec2d& rvec, Vec2d& tvec, Vec2d& BlockSize, Vec2d& GridSize, const string& folder) :
				_focal(focal), _imageSize(imageSize), _distortion(distortion), _rvec(rvec), _tvec(tvec), _BlockSize(BlockSize), _GridSize(GridSize), _folder(folder) {}

			inline double& GetFocal() { return _focal; }
			inline Size& GetImageSize() { return _imageSize; }
			inline Mat& GetDistortion() { return _distortion; }
			inline Vec2d& GetRvec() { return _rvec; }
			inline Vec2d& GetTvec() { return _tvec; }
			inline Vec2d& GetBlockSize() { return _BlockSize; }
			inline Vec2d& GetGridSize() { return _GridSize; }
			inline string& GetFolder() { return _folder; }
	};
}
