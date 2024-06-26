//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2024-04-19
//--------------------------------------------------

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/Path/PathHelper.h>
#include <NVLib/Parameters/Parameters.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "ArgReader.h"
#include "LoadUtils.h"

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void Run(NVLib::Parameters * parameters);
Size GetImageSize(NVLib::PathHelper * pathHelper);
void SaveGrid(NVLib::PathHelper * helper, NVL_App::Grid * grid, int index);

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

    logger.Log(1, "Create a path helper");
    auto database = NVL_Utils::ArgReader::ReadString(parameters, "database");
    auto dataset = NVL_Utils::ArgReader::ReadString(parameters, "dataset");
    auto pathHelper = NVLib::PathHelper(database, dataset);

    logger.Log(1, "Load the camera Id");
    auto cameraId = NVL_Utils::ArgReader::ReadInteger(parameters, "cameraId");
    logger.Log(1, "The cameraId: %i", cameraId);

    logger.Log(1, "Load the given board settings");
    auto boardSettings = NVL_App::LoadUtils::LoadBoardSettings(&pathHelper);

    logger.Log(1, "Load image size");
    auto imageSize = GetImageSize(&pathHelper);
    logger.Log(1, "Image Size: %i x %i", imageSize.width, imageSize.height);

    logger.Log(1, "Load the grid variables");
    auto grid_1 = NVL_App::LoadUtils::LoadGrid(&pathHelper, boardSettings.get(), cameraId, 0);
    auto grid_2 = NVL_App::LoadUtils::LoadGrid(&pathHelper, boardSettings.get(), cameraId, 1);

    logger.Log(1, "Writing output files");
    SaveGrid(&pathHelper, grid_1.get(), 0); SaveGrid(&pathHelper, grid_2.get(), 1);

    logger.StopApplication();
}

//--------------------------------------------------
// Helper Size
//--------------------------------------------------

/**
 * Get the image size that we are dealing with
 * @param pathHelper That we are finding
 * @return The size of the image that we are getting
*/
Size GetImageSize(NVLib::PathHelper * pathHelper) 
{
    // Get the image path
    auto path = pathHelper->GetPath("Tool_Output", "Camera_0_Image_0.jpg");

    // Load the image
    Mat image = imread(path); if (image.empty()) throw runtime_error("Unable to find: " + path);

    // Return 
    return image.size();
}

//--------------------------------------------------
// Save Functionality
//--------------------------------------------------

/**
 * Defines save functionality for the grid
 * @param helper The helper element that we are using to perform the save
*/
void SaveGrid(NVLib::PathHelper * helper, NVL_App::Grid * grid, int index) 
{
    auto fileName = stringstream(); fileName << "points_" << setw(4) << setfill('0') << index << ".txt";
    auto path = helper->GetPath("Points", fileName.str());

    auto writer = ofstream(path);

    for (auto i = 0; i < grid->GetPointCount(); i++) 
    {
        auto iPoint = grid->GetImagePoints()[i];
        auto sPoint = grid->GetScenePoints()[i];

        writer << sPoint.x << "," << sPoint.y << "," << sPoint.z << "," << iPoint.x << "," << iPoint.y << endl;
    }

    writer.close();
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