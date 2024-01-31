//--------------------------------------------------
// Implementation of class Camera
//
// @author: Wild Boar
//
// @date: 2024-01-26
//--------------------------------------------------

#include "Camera.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param name Initialize variable <name>
 */
Camera::Camera(const string& name) : _name(name)
{
	_handle = GetHandle(name);
}

/**
 * @brief Main Terminator
 */
Camera::~Camera()
{
	// Extra termination logic can go here!
}

//--------------------------------------------------
// Capture
//--------------------------------------------------

/**
 * @brief Capture an image from the camera
 * @param timeout The timeout setting associated with the camera
 * @return Mat Returns a Mat
 */
Mat Camera::Capture(int timeout)
{
	// Declare working variables
	auto grabResult = Pylon::CGrabResultPtr();
	auto pylonImage = Pylon::CPylonImage();
	auto formatConverter = Pylon::CImageFormatConverter(); formatConverter.OutputPixelFormat = Pylon::PixelType_BGR8packed;

	// Grab an associated image
	_handle->RetrieveResult(timeout, grabResult);

	// handles checking and confirmation of the grab
	if (grabResult->GrabSucceeded()) 
	{
		formatConverter.Convert(pylonImage, grabResult);
		Mat image = Mat_<Vec3b>(grabResult->GetHeight(), grabResult->GetWidth(), (Vec3b *)pylonImage.GetBuffer());
		return image.clone();
	}
	else throw runtime_error("Unable to successfully capture an image");
}

//--------------------------------------------------
// Getter
//--------------------------------------------------

/**
 * @brief Retrieve the width of the image associated with the camera
 * @return int Returns a int
 */
int Camera::GetWidth()
{
	return _handle->Width.GetMax();
}

/**
 * @brief Retrieve the height of the image associated with the camera
 * @return int Returns a int
 */
int Camera::GetHeight()
{
	return _handle->Height.GetMax();
}

//--------------------------------------------------
// Helper Functionality
//--------------------------------------------------

/**
 * Add the logic to get a 'handle' to the camera in question
 * @param name The name of the camera
*/
Camera::Handle * Camera::GetHandle(const string& name) 
{
	// Create a factory
	auto& factory = Pylon::CTlFactory::GetInstance();

	// Get the list of attached devices
	auto devices = Pylon::DeviceInfoList_t(); factory.EnumerateDevices(devices);

	// Create a value to hold the result
	auto found = (Pylon::CDeviceInfo *) nullptr;

	// Find the device that has the name that we are looking for
	for (auto& device : devices) 
	{
		if (device.GetUserDefinedName().c_str() == name) 
		{
			found = &device; break;
		}
	}

	// Check to see if a camera was found
	if (found == nullptr) throw runtime_error("Unable to find a camera with the given name");

	// Create the camera handle
	auto result = new Camera::Handle();
	result->Attach(factory.CreateDevice(*found));
	result->MaxNumBuffer = 1;
	result->Open();

	result->TriggerMode.SetValue(Basler_UsbCameraParams::TriggerMode_Off);
	result->BalanceWhiteAuto.SetValue(Basler_UsbCameraParams::BalanceWhiteAutoEnums::BalanceWhiteAuto_Continuous);
	result->GainAuto.SetValue(Basler_UsbCameraParams::GainAutoEnums::GainAuto_Continuous);
	result->ExposureAuto.SetValue(Basler_UsbCameraParams::ExposureAuto_Continuous);
	result->StartGrabbing();

	// Return the result
	return result;
}