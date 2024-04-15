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

    _logger->Log(1, "Load points");
    auto pointFolder = ArgUtils::GetString(parameters, "pointset");
    auto grid = PointLoader::GetPoints(_pathHelper, pointFolder);

    _logger->Log(1, "Get image size");
    auto testImagePath = _pathHelper->GetPath(pointFolder, "image.png");
    Mat testImage = imread(testImagePath); if (testImage.empty()) throw runtime_error("Unable to find test image: " + testImagePath);
    auto imageSize = testImage.size();

    _logger->Log(1, "Setup a callback object");
    auto callback = ImageCallback(grid->GetImagePointMatrix());
   
    _logger->Log(1, "Refine the points that we dealing with");
    Mat initial = Mat_<double>::zeros(4,1);
    auto refiner = RandomSolver(imageSize, grid, initial);
    refiner.Solve(500000, &callback);

    delete grid;
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
    // TODO: Execution Logic
}
