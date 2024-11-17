//--------------------------------------------------
// Implementation of class PinHoleProblem
//
// @author: Wild Boar
//
// @date: 2024-08-04
//--------------------------------------------------

#include "PinHoleProblem.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Initializer Constructor
 * @param grid1 Initialize variable <grid1>
 * @param grid2 Initialize variable <grid2>
 */
PinHoleProblem::PinHoleProblem(GridPoints * grid1, GridPoints * grid2) : ProblemBase()
{
	_grid1 = grid1;
	_grid2 = grid2;
}

/**
 * @brief Main Terminator
 */
PinHoleProblem::~PinHoleProblem()
{
	// Extra terminational logic
}

//--------------------------------------------------
// DataSize
//--------------------------------------------------

/**
 * @brief Get the size of the data that we are processing
 * @return int Returns a int
 */
int PinHoleProblem::GetDataSize()
{
	throw runtime_error("Not implemented");
}

//--------------------------------------------------
// Evaluate
//--------------------------------------------------

/**
 * @brief Evaluate a particular parameter setup in terms of the grids
 * @param parameters The parameters that we are evaluating
 * @param errors The individual erros associated with each point
 * @return double Returns a double
 */
double PinHoleProblem::Evaluate(Mat& parameters, Mat& errors)
{
	throw runtime_error("Not implemented");
}