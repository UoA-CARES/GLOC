//--------------------------------------------------
// Implementation code for the Engine
//
// @author: Wild Boar
//
// @date: 2024-05-28
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
    _logger->Log(1, "Loading board parameters");
    auto board = NVL_App::LoadUtils::LoadBoardParams(*_pathHelper);
    _logger->Log(1, "Board Size: [%i,%i]", board->GetBoardSize().width, board->GetBoardSize().height);

    _logger->Log(1, "Loading the first grid");
    auto grid_1 = NVL_App::LoadUtils::LoadGrid(*_pathHelper, board->GetBoardSize(), "Points", 0);
    _logger->Log(1, "Load completed: %i points", grid_1->GetPointCount());

    _logger->Log(1, "Loading the second grid");
    auto grid_2 = NVL_App::LoadUtils::LoadGrid(*_pathHelper, board->GetBoardSize(), "Points", 1);
    _logger->Log(1, "Load completed: %i points", grid_2->GetPointCount());

    _logger->Log(1, "Loading the distortion model from disk");
    auto dmodel = NVL_App::LoadUtils::LoadCalibration(*_pathHelper, "Distortion");
    _logger->Log(1, "Distortion: %s", (NVLib::Formatter() << dmodel->GetDistortion().t()).str().c_str());
}
