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
unique_ptr<NVL_App::Arguments> LoadArguments(NVLib::PathHelper& pathHelper);
void FillScenePoints(NVL_App::Arguments * arguments, vector<Point3d>& points);

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

    logger.Log(1, "Load the associated arguments from disk");
    auto arguments = LoadArguments(pathHelper);

    logger.Log(1, "Generate the associated 3D points");
    auto scenePoints = vector<Point3d>(); FillScenePoints(arguments.get(), scenePoints);
    

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
unique_ptr<NVL_App::Arguments> LoadArguments(NVLib::PathHelper& pathHelper) 
{
    auto path = pathHelper.GetPath("Meta", "PointGen.xml");

    auto reader = FileStorage(path, FileStorage::FORMAT_XML | FileStorage::READ);
    if (!reader.isOpened()) throw runtime_error("Unable to open: " + path);

    double focal; reader["focal"] >> focal;
    Size imageSize; reader["image_size"] >> imageSize;
    Mat distortion; reader["distortion"] >> distortion;
    Vec3d rvec; reader["rotation"] >> rvec;
    Vec3d tvec; reader["translation"] >> tvec;
    Vec2d blockSize; reader["block_size"] >> blockSize;
    Vec2i gridSize; reader["grid_size"] >> gridSize;
    string folder; reader["folder"] >> folder;

    reader.release();

    return unique_ptr<NVL_App::Arguments>(new NVL_App::Arguments(focal, imageSize, distortion, rvec, tvec, blockSize, gridSize, folder));
}

/**
 * Add logic to generate scene points and put them into a points vector
 * @param arguments The arguments provided for the application
 * @param points The points that we are adding to the system
 */
void FillScenePoints(NVL_App::Arguments * arguments, vector<Point3d>& points) 
{
    for (auto row = 0; row < arguments->GetGridSize()[1]; row++) 
    {
        for (auto column = 0; column < arguments->GetGridSize()[0]; column++) 
        {
            auto X = column * arguments->GetBlockSize()[0];
            auto Y = row * arguments->GetBlockSize()[1];
            auto Z = 0;
            points.push_back(Point3d(X, Y, Z));
        }
    }
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
