//--------------------------------------------------
// The settings for extracting points
//
// @author: Wild Boar
//
// @date: 2024-04-19
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include "Board.h"

namespace NVL_App
{
	class Settings
	{
	private:
		Board * _board1;
		Board * _board2;
	public:
		Settings(Board * board1, Board * board2);
		~Settings();

		Board * GetBoard(int index);

		inline Board * GetBoard1() { return _board1; }
		inline Board * GetBoard2() { return _board2; }
	};
}