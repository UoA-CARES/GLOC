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

		 enum class TriggerMode 
		 {
        	TRIGGER_MODE_ASYNC,
        	TRIGGER_MODE_EXPOSURE,
        	TRIGGER_MODE_PIN
		};

		private:
			Handle * _handle;
			string _name;
			TriggerMode _triggerMode;
			bool _isMaster;
		public:
			Camera(const string& name, TriggerMode triggerMode, bool isMaster);
			~Camera();

			Mat Capture(int timeout);

			void Trigger();

			int GetWidth();
			int GetHeight();

			inline string& GetName() { return _name; }
			inline TriggerMode& GetTriggerMode() { return _triggerMode; }
			inline bool GetIsMaster() { return _isMaster; }
		private:
			Handle * GetHandle(const string& name);
	};
}
