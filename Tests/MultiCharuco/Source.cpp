//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2024-05-23
//--------------------------------------------------

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/DisplayUtils.h>
#include <NVLib/Path/PathHelper.h>
#include <NVLib/Parameters/Parameters.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "ArgReader.h"

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void Run(NVLib::Parameters * parameters);
Mat GetImage(NVLib::PathHelper& helper);

//--------------------------------------------------
// Execution Logic
//--------------------------------------------------

/**
 * Main entry point into the application
 * @param parameters The input parameters
 */
void Run(NVLib::Parameters * parameters) 
{
    if (parameters == nullptr) return; auto logger = NVLib::Logger(1);

    logger.StartApplication();

    logger.Log(1, " Create an image loader");
    auto database = NVL_Utils::ArgReader::ReadString(parameters, "database");
    auto dataset = NVL_Utils::ArgReader::ReadString(parameters, "dataset");
    auto pathHelper = NVLib::PathHelper(database, dataset);

    logger.Log(1, "Load a calibration image");
    auto image = (Mat) GetImage(pathHelper);

    NVLib::DisplayUtils::ShowImage("Image", image, 1000); waitKey(); 

    logger.StopApplication();
}

//--------------------------------------------------
// Get Image
//--------------------------------------------------

/**
 * Retrieve the image
 * @param helper The image that we are dealing with
 * @return The image that was found
*/
Mat GetImage(NVLib::PathHelper& helper) 
{
    auto path = helper.GetPath("Images", "left.png");
    auto image = (Mat) imread(path); if (image.empty()) throw runtime_error("Unable to open: " + path);
    return image;
}

//--------------------------------------------------
// Entry Point
//--------------------------------------------------

/**
 * Main Method
 * @param argc The count of the incoming arguments
 * @param argv The number of incoming arguments
 * @return SUCCESS and FAILURE
 */
int main(int argc, char ** argv) 
{
    NVLib::Parameters * parameters = nullptr;

    try
    {
        parameters = NVL_Utils::ArgReader::GetParameters(argc, argv);
        Run(parameters);
    }
    catch (runtime_error exception)
    {
        cerr << "Error: " << exception.what() << endl;
        exit(EXIT_FAILURE);
    }
    catch (string exception)
    {
        cerr << "Error: " << exception << endl;
        exit(EXIT_FAILURE);
    }

    if (parameters != nullptr) delete parameters;

    return EXIT_SUCCESS;
}
