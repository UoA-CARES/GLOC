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
#include <opencv2/aruco.hpp>
#include <opencv2/aruco/charuco.hpp>
using namespace cv;

#include "ArgReader.h"
#include "BoardParams.h"
#include "BoardPoints.h"

//--------------------------------------------------
// Function Prototypes
//--------------------------------------------------
void Run(NVLib::Parameters * parameters);
Mat GetImage(NVLib::PathHelper& helper);
unique_ptr<NVL_App::BoardParams> LoadBoardParams(NVLib::PathHelper& helper);
void LoadDetectorParameters(NVLib::PathHelper& helper, Ptr<aruco::DetectorParameters> &params);
unique_ptr<NVL_App::BoardPoints> FilterPoints(vector<int>& indices, vector<vector<Point2f>>& corners, const Range& indexRange);
void SavePoints(NVLib::PathHelper& helper, int boardNumber, const Ptr<aruco::CharucoBoard>& board, const vector<int>& indices, const vector<Point2f>& corners);

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

    logger.Log(1, "Load up board parameters");
    auto boardParams = LoadBoardParams(pathHelper);
    auto dictionary = aruco::getPredefinedDictionary(boardParams->GetDictionary());
   
    logger.Log(1, "Loading the detector parameters");
    auto detectParameters = aruco::DetectorParameters::create();
    LoadDetectorParameters(pathHelper, detectParameters);

    logger.Log(1, "Detect corners within the system");
    auto corners = vector<vector<Point2f>>(); auto indices = std::vector<int>(); auto rejected = vector<vector<Point2f>>();
    cv::aruco::detectMarkers(image, dictionary, corners, indices, detectParameters);
    if (indices.empty()) throw runtime_error("No corners were detected, verify the image or the parameters");

    logger.Log(1, "Seperating out the board detections");
    auto board_1 = FilterPoints(indices, corners, Range(0, 23));
    auto board_2 = FilterPoints(indices, corners, Range(24, 50));

    logger.Log(1, "Create Charuco board containers");
    auto charucoBoard_1  = aruco::CharucoBoard::create(boardParams->GetBoardSize().width, boardParams->GetBoardSize().height, boardParams->GetBlockSize(), boardParams->GetMarkerSize(), dictionary);
    auto charucoBoard_2  = aruco::CharucoBoard::create(boardParams->GetBoardSize().width, boardParams->GetBoardSize().height, boardParams->GetBlockSize(), boardParams->GetMarkerSize(), dictionary);
    auto indices_1 = vector<int>(); for (auto i = 0; i < 24; i++) indices_1.push_back(i); auto indices_2 = vector<int>(); for (auto i = 24; i < 48; i++) indices_2.push_back(i);
        
    charucoBoard_1->setIds(indices_1);  
    charucoBoard_2->setIds(indices_2);

    logger.Log(1, "Extract Charuco corners");
    vector<Point2f> cc_1; vector<int> ci_1; cv::aruco::interpolateCornersCharuco(board_1->GetCorners(), board_1->GetIndices(), image, charucoBoard_1, cc_1, ci_1);
    vector<Point2f> cc_2; vector<int> ci_2; cv::aruco::interpolateCornersCharuco(board_2->GetCorners(), board_2->GetIndices(), image, charucoBoard_2, cc_2, ci_2);
    auto grayImage = (Mat) Mat(); cvtColor(image, grayImage, COLOR_BGR2GRAY);
    cornerSubPix(grayImage, cc_1, Size(13, 13), Size(-1, -1), TermCriteria(TermCriteria::COUNT & TermCriteria::EPS, 1000, 1e-3));
    cornerSubPix(grayImage, cc_2, Size(13, 13), Size(-1, -1), TermCriteria(TermCriteria::COUNT & TermCriteria::EPS, 1000, 1e-3));

    logger.Log(1, "Save image of detected markers");
    auto displayImage = (Mat) image.clone(); 
    cv::aruco::drawDetectedCornersCharuco(displayImage, cc_1, ci_1, Scalar(0, 0, 255)); cv::aruco::drawDetectedCornersCharuco(displayImage, cc_2, ci_2, Scalar(0,0,255));
    auto imagePath = pathHelper.GetPath("Points", "marker.png"); imwrite(imagePath, displayImage);

    logger.Log(1, "Save points to disk");
    SavePoints(pathHelper, 0, charucoBoard_1, ci_1, cc_1);
    SavePoints(pathHelper, 1, charucoBoard_2, ci_2, cc_2);
    
    logger.StopApplication();
}

//--------------------------------------------------
// Board Seperator
//--------------------------------------------------

/**
 * Add the logic to seperate corners
 * @param indices The indices of the corners
 * @param corners The corners that we are getting
 * @param indexRange The range of indices that we are working with
*/
unique_ptr<NVL_App::BoardPoints> FilterPoints(vector<int>& indices, vector<vector<Point2f>>& corners, const Range& indexRange) 
{
    auto result = new NVL_App::BoardPoints();

    for (auto i = 0; i < indices.size(); i++) 
    {
        auto index = indices[i];
        auto contains = index >= indexRange.start && index <= indexRange.end;
        if (contains) result->Add(indices[i], corners[i]);
    }

    return unique_ptr<NVL_App::BoardPoints>(result);
}

//--------------------------------------------------
// Load Helpers
//--------------------------------------------------

/**
 * Retrieve the image
 * @param helper A helper module that allows for the loading of valid paths
 * @return The image that was found
*/
Mat GetImage(NVLib::PathHelper& helper) 
{
    auto path = helper.GetPath("Images", "left.png");
    auto image = (Mat) imread(path); if (image.empty()) throw runtime_error("Unable to open: " + path);
    return image;
}

/**
 * Add associated board parameters from disk
 * @param helper  A helper module that allows for the loading of valid paths
 * @return The board parameters
*/
unique_ptr<NVL_App::BoardParams> LoadBoardParams(NVLib::PathHelper& helper) 
{
    auto path = helper.GetPath("Config", "board.xml");
    auto reader = FileStorage(path, FileStorage::FORMAT_XML | FileStorage::READ);
    if (!reader.isOpened()) throw runtime_error("Unable to find board configuration: " + path);
   
    auto size = Size(); reader["board_size"] >> size;
    auto blockSize = 0.0; reader["block_size"] >> blockSize;
    auto markerSize = 0.0; reader["marker_size"] >> markerSize;
    auto dictionary = 0; reader["dictionary"] >> dictionary;
   
    reader.release();

    return unique_ptr<NVL_App::BoardParams>(new NVL_App::BoardParams(size, blockSize, markerSize, dictionary));
}

/**
 * Load up detector parameters
 * @param helper The path helper that we have
 * @param params The parameters that we are loading
 */
void LoadDetectorParameters(NVLib::PathHelper& helper, Ptr<aruco::DetectorParameters> &params) 
{
    auto path = helper.GetPath("Config", "detector_params.yml");
    FileStorage reader(path, FileStorage::READ); if (!reader.isOpened()) throw runtime_error("Unable to open: " + path);
    
    reader["adaptiveThreshWinSizeMin"] >> params->adaptiveThreshWinSizeMin;
    reader["adaptiveThreshWinSizeMax"] >> params->adaptiveThreshWinSizeMax;
    reader["adaptiveThreshWinSizeStep"] >> params->adaptiveThreshWinSizeStep;
    reader["adaptiveThreshConstant"] >> params->adaptiveThreshConstant;
    reader["minMarkerPerimeterRate"] >> params->minMarkerPerimeterRate;
    reader["maxMarkerPerimeterRate"] >> params->maxMarkerPerimeterRate;
    reader["polygonalApproxAccuracyRate"] >> params->polygonalApproxAccuracyRate;
    reader["minCornerDistanceRate"] >> params->minCornerDistanceRate;
    reader["minDistanceToBorder"] >> params->minDistanceToBorder;
    reader["minMarkerDistanceRate"] >> params->minMarkerDistanceRate;
    reader["cornerRefinementMethod"] >> params->cornerRefinementMethod;
    reader["cornerRefinementWinSize"] >> params->cornerRefinementWinSize;
    reader["cornerRefinementMaxIterations"] >> params->cornerRefinementMaxIterations;
    reader["cornerRefinementMinAccuracy"] >> params->cornerRefinementMinAccuracy;
    reader["markerBorderBits"] >> params->markerBorderBits;
    reader["perspectiveRemovePixelPerCell"] >> params->perspectiveRemovePixelPerCell;
    reader["perspectiveRemoveIgnoredMarginPerCell"] >> params->perspectiveRemoveIgnoredMarginPerCell;
    reader["maxErroneousBitsInBorderRate"] >> params->maxErroneousBitsInBorderRate;
    reader["minOtsuStdDev"] >> params->minOtsuStdDev;
    reader["errorCorrectionRate"] >> params->errorCorrectionRate;

    reader.release();
}

//--------------------------------------------------
// Save Points
//--------------------------------------------------

/**
 * Save points to disk
 * @param helper The helper tool that we are using to save points to disk
 * @param boardNumber The number of the board that we are saving
 * @param board The actual board details
 * @param indices The indices of the points
 * @param corners The actual corners that we are saving
*/
void SavePoints(NVLib::PathHelper& helper, int boardNumber, const Ptr<aruco::CharucoBoard>& board, const vector<int>& indices, const vector<Point2f>& corners) 
{
    // Create a path
    auto fileName = stringstream(); fileName << "cpoints_" << setw(4) << setfill('0') << boardNumber << ".txt";
    auto savePath = helper.GetPath("Points", fileName.str());

    ////////////////
    // NOTE that there is some implication to suggest that the indices = the corner id - see https://github.com/opencv/opencv_contrib/blob/4.x/modules/aruco/src/aruco_calib.cpp
    // This needs to be tested ofcourse!
    ////////////////

    // Build 3D points
    auto scenePoints = vector<Point3f>();
    for (auto i = 0; i < indices.size(); i++) 
    {
        auto& index = indices[i];
        auto& point = board->chessboardCorners[index];
        scenePoints.push_back(point);
    }
    
    // Open a write
    auto writer = ofstream(savePath); if (!writer.is_open()) throw runtime_error("Unable to create output file: " + savePath);

    for (auto i = 0; i < indices.size(); i++) 
    {
        auto index = indices[i];
        auto imagePoint = corners[i];
        auto scenePoint = scenePoints[i];
     
        writer << scenePoint.x << "," << scenePoint.y << "," << scenePoint.z << "," << imagePoint.x << "," << imagePoint.y << endl;
    }

    // Close writer
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
