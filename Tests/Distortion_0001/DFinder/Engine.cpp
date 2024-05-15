//--------------------------------------------------
// Implementation code for the Engine
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#include "Engine.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructor and Terminator
//--------------------------------------------------

/**
 * Main Constructor
 * @param logger The logger that we are using for the system
 * @param parameters The input parameters
 */
Engine::Engine(NVLib::Logger* logger, NVLib::Parameters* parameters) 
{
    _logger = logger; _parameters = parameters;

    _logger->Log(1, "Creating a path helper");
    auto database = ArgUtils::GetString(parameters, "database");
    auto dataset = ArgUtils::GetString(parameters, "dataset");
    _pathHelper = new NVLib::PathHelper(database, dataset);
    _pointFolder = ArgUtils::GetString(parameters, "pointset");
}

/**
 * Main Terminator 
 */
Engine::~Engine() 
{
    delete _parameters; delete _pathHelper;
}

//--------------------------------------------------
// Execution Entry Point
//--------------------------------------------------

/**
 * Entry point function
 */
void Engine::Run()
{
    _logger->Log(1, "Load points");
    auto grids = PointLoader::GetGrid(_pathHelper, _pointFolder);

    // _logger->Log(1, "Get image size");
    // auto testImagePath = _pathHelper->GetPath(_pointFolder, "image.png");
    // Mat testImage = imread(testImagePath); if (testImage.empty()) throw runtime_error("Unable to find test image: " + testImagePath);
    // auto imageSize = testImage.size();

    // _logger->Log(1, "Setup a callback object");
    // auto callback = ImageCallback(grid->GetImagePointMatrix());
   
    // _logger->Log(1, "Refine the points that we dealing with");
    // Mat initial = Mat_<double>::zeros(4,1);
    // auto refiner = RandomSolver(imageSize, grid, initial);
    // refiner.Solve(500000, 40000, &callback);

    // _logger->Log(1, "Saving the final points to disk");
    // Mat savePoints = refiner.GetImagePoints();
    // SaveUPoints(_pointFolder, savePoints);

    // _logger->Log(1, "Free Memory");
    // delete grid;
}

//--------------------------------------------------
// Execution Entry Point
//--------------------------------------------------

/**
 * The points that that we found
 * @param folder The folder that we are dealing with
 * @param points The points that we are saving
*/
void Engine::SaveUPoints(const string& folder, Mat& points) 
{
    auto resultFolder = _pathHelper->GetPath(folder, "upoints.txt");
    auto writer = ofstream(resultFolder); if (!writer.is_open()) throw runtime_error("Unable to open file: " + resultFolder);

    auto pLink = (double *) points.data;

    auto pCount = points.rows * points.cols;

    for (auto i = 0; i < pCount; i++) 
    {
        auto u = pLink[i * 2 + 0];
        auto v = pLink[i * 2 + 1];
        writer << u << "," << v << endl;
    }

    writer.close();
}