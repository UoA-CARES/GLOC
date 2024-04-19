//--------------------------------------------------
// Implementation of class Settings
//
// @author: Wild Boar
//
// @date: 2024-04-19
//--------------------------------------------------

#include "Settings.h"
using namespace NVL_App;

//--------------------------------------------------
// Constructors and Terminators
//--------------------------------------------------

/**
 * @brief Custom Constructor
 * @param board1 The details of the first board
 * @param board2 The details of the second board 
 */
Settings::Settings(Board * board1, Board * board2) : _board1(board1), _board2(board2)
{
	// Extra logic can go here
}

/**
 * @brief Main Terminator
 */
Settings::~Settings()
{
	delete _board1; delete _board2;
}

//--------------------------------------------------
// Getter
//--------------------------------------------------

/**
 * @brief Retrieve the board by index
 * @param index The index of the board that we want
 * @return Board * Returns a Board *
 */
Board * Settings::GetBoard(int index)
{
	if (index == 1) return _board1;
	else if (index == 2) return _board2;
	else 
	{
		auto message = stringstream(); message << "Unknown Index: " << index;
		throw runtime_error(message.str());
	} 
}