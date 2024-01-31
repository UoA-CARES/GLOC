//--------------------------------------------------
// a camera wrapper for the Basler
//
// @author: Wild Boar
//
// @date: 2024-01-26
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include <pylon/PylonIncludes.h>

#include <pylon/usb/BaslerUsbInstantCamera.h>

namespace NVL_App
{
	class Camera
	{
		public:
			typedef Pylon::CBaslerUsbInstantCamera Handle;
		private:
			Handle * _handle;
			string _name;
		public:
			Camera(const string& name);
			~Camera();

			Mat Capture(int timeout);

			int GetWidth();
			int GetHeight();

			inline string& GetName() { return _name; }

		private:
			Handle * GetHandle(const string& name);
	};
}
