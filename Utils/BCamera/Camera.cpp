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
 * @param handle Initialize variable <handle>
 * @param id Initialize variable <id>
 * @param name Initialize variable <name>
 * @param triggerMode Initialize variable <triggerMode>
 * @param isMaster Initialize variable <isMaster>
 */
Camera::Camera(Handle * handle, const string& id, const string& name, TriggerMode& triggerMode, bool isMaster)
{
	_handle = handle;
	_id = id;
	_name = name;
	_triggerMode = triggerMode;
	_isMaster = isMaster;
}

/**
 * @brief Main Terminator
 */
Camera::~Camera()
{
	// TODO: Add Teardown logic here
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
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Trigger
//--------------------------------------------------

/**
 * @brief Add the logic to trigger the camera
 */
void Camera::Trigger()
{
	throw runtime_error("Not implemented");
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
	throw runtime_error("Not implemented");
}

/**
 * @brief Retrieve the height of the image associated with the camera
 * @return int Returns a int
 */
int Camera::GetHeight()
{
	throw runtime_error("Not implemented");
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

	// Return the result
	return result;
}
