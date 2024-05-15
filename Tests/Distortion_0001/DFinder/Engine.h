//--------------------------------------------------
// Defines a basic engine for a vanilla C++ project.
//
// @author: Wild Boar
//
// @date: 2024-04-10
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/Logger.h>
#include <NVLib/Path/PathHelper.h>

#include <DFinderLib/ArgUtils.h>
#include <DFinderLib/PointLoader.h>
#include <DFinderLib/ImageCallback.h>
#include <DFinderLib/RandomSolver.h>

namespace NVL_App
{
	class Engine
	{
	private:
		NVLib::Parameters * _parameters;
		NVLib::Logger* _logger;
		NVLib::PathHelper * _pathHelper;
		string _pointFolder;
	public:
		Engine(NVLib::Logger* logger, NVLib::Parameters * parameters);
		~Engine();

		void Run();
	private:
		void SaveUPoints(const string& folder, Mat& points);
	};
}
