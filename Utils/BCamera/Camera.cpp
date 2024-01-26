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
