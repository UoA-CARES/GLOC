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
    _logger->Log(1, "Determining how many point sets there are...");
    auto gridCount = PointLoader::GetGridCount(_pathHelper);
    _logger->Log(1, "Number of grids found: %i", gridCount);
    if (gridCount == 0) throw runtime_error("At least 1 grid is required to perform the optimization");

    _logger->Log(1, "Loading Grids from disk");
    auto grids = PointLoader::GetGridList(_pathHelper, gridCount);

    _logger->Log(1, "Determining the image size");
    auto imageSize = PointLoader::GetImageSize(_pathHelper, "Images", "image.png");
    _logger->Log(1, "Image Size: %i x %i", imageSize.width, imageSize.height);
   
    _logger->Log(1, "Setup a callback object");
    Mat noDistortion = Mat_<double>::zeros(DISTORTION_COEFFICIENTS,1);
    auto callback = ImageCallback(grids->GetImagePoints(imageSize, noDistortion), imageSize);
   
    _logger->Log(1, "Refine the points that we dealing with");
    Mat initial = Mat_<double>::zeros(DISTORTION_COEFFICIENTS,1);
    auto refiner = RandomSolver(imageSize, grids.get(), initial);
    refiner.Solve(500000, 40000, &callback);

    _logger->Log(1, "Saving parameter results to disk");
    SaveUtils::SaveParams(_pathHelper, &refiner);

    _logger->Log(1, "Saving associated points to disk");
    SaveUtils::SavePoints(_pathHelper, &refiner);
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