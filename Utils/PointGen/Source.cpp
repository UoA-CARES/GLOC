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
void FillImagePoints(NVL_App::Arguments * arguments, const vector<Point3d>& scenePoints, vector<Point2d>& points);
Mat BuildCameraMat(NVL_App::Arguments * arguments);
Mat MakeImage(NVL_App::Arguments * arguments, const vector<Point2d>& points);
void SavePoints(NVLib::PathHelper& pathHelper, const string& folder, const vector<Point3d>& scenePoints, const vector<Point2d>& imagePoints);

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
    
    logger.Log(1, "Generate the image 2D points");
    auto imagePoints = vector<Point2d>(); FillImagePoints(arguments.get(), scenePoints, imagePoints);

    logger.Log(1, "Save the resultant image");
    Mat image = MakeImage(arguments.get(), imagePoints);
    auto imagePath = pathHelper.GetPath(arguments->GetFolder(), "image.png");
    imwrite(imagePath, image);

    logger.Log(1, "Save the associated points");
    SavePoints(pathHelper, arguments->GetFolder(), scenePoints, imagePoints);

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

/**
 * Add the logic to fill associated image points
 * @param arguments The arguments that we are populating
 * @param scenePoints The given scene points for the application
 * @param points The resultant image points associated with the application
 */
void FillImagePoints(NVL_App::Arguments * arguments, const vector<Point3d> & scenePoints, vector<Point2d> & points) 
{
    Mat camera = BuildCameraMat(arguments);
    Mat & distortion = arguments->GetDistortion();
    auto& rvec = arguments->GetRvec();
    auto& tvec = arguments->GetTvec();

    projectPoints(scenePoints, rvec, tvec, camera, distortion, points);
}

/**
 * Assemble the camera matrix
 * @param arguments The arguments that we are dealing with
*/
Mat BuildCameraMat(NVL_App::Arguments * arguments) 
{
    auto fx = arguments->GetFocal(); 
    auto fy = arguments->GetFocal();
    auto cx = arguments->GetImageSize().width * 0.5;
    auto cy = arguments->GetImageSize().height * 0.5;

    return (Mat_<double>(3,3) << fx, 0, cx, 0, fy, cy, 0, 0, 1);
}

/**
 * Generate an image that we are dealing with
 * @param arguments The arguments that we are dealing with
 * @param points The points that we are generating the images from
 * @return The image that it was made
*/
Mat MakeImage(NVL_App::Arguments * arguments, const vector<Point2d>& points) 
{
    Mat image = Mat_<Vec3b>::zeros(arguments->GetImageSize());

    for (auto& point : points) 
    {
        circle(image, point, 3, Scalar(0, 0, 255), FILLED);
    }

    return image;
}

/**
 * Save the point files to disk
 * @param pathHelper A helper for generating the path that we are saving to
 * @param folder The folder that we are saving to
 * @param scenePoints The scene points that are being saved
 * @param imagePoints The image points that are being saved
 */
void SavePoints(NVLib::PathHelper& pathHelper, const string& folder, const vector<Point3d>& scenePoints, const vector<Point2d>& imagePoints) 
{
    auto path = pathHelper.GetPath(folder, "points.txt");
    auto writer = ofstream(path); if (!writer.is_open()) throw runtime_error("Unable to create file: " + path);
    if (scenePoints.size() != imagePoints.size()) throw runtime_error("There is a size mismatch between the scene points and image points");

    for (auto i = 0; i < scenePoints.size(); i++) 
    {
        writer << scenePoints[i].x << "," << scenePoints[i].y << "," << scenePoints[i].z << "," << imagePoints[i].x << "," << imagePoints[i].y << endl;
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
