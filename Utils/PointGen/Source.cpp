//--------------------------------------------------
// Startup code module
//
// @author: Wild Boar
//
// @date: 2024-03-05
//--------------------------------------------------

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/Path/PathHelper.h>
#include <NVLib/Parameters/Parameters.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include "ArgReader.h"
#include "Arguments.h"

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void Run(NVLib::Parameters * parameters);
unique_ptr<NVL_App::Arguments> GetArguments(NVLib::PathHelper& pathHelper);

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

    // Create a helper for path tracking
    auto database = NVL_Utils::ArgReader::ReadString(parameters, "database");
    auto dataset = NVL_Utils::ArgReader::ReadString(parameters, "dataset");
    auto pathHelper = NVLib::PathHelper(database, dataset);

    logger.StopApplication();
}

//--------------------------------------------------
// Helper Methods
//--------------------------------------------------

/**
 * Retrieve the arguments associated with the application
 * @param pathHelper The helper for getting the path information
 * @return The arguments that we are getting for the application
*/
unique_ptr<NVL_App::Arguments> GetArguments(NVLib::PathHelper& pathHelper) 
{
    auto path = pathHelper.GetPath("Meta", "PointGen.xml");

    auto reader = FileStorage(path, FileStorage::FORMAT_XML | FileStorage::READ);
    if (!reader.isOpened()) throw runtime_error("Unable to open: " + path);


    double focal; reader["focal"] >> focal;
    Size imageSize; reader["image_size"] >> imageSize;
    Mat distortion; reader["distortion"] >> distortion;
    Vec3d rotation; reader["rotation"] >> rotation;
    Vec3d translation; reader["translation"] >> translation;
    Vec2i blockSize; reader["block_size"] >> blockSize;
    Vec2i gridSize; reader["grid_size"] >> gridSize;


    reader.release();


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
