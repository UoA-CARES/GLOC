//--------------------------------------------------
// The base class for holding refined results for the application
//
// @author: Wild Boar
//
// @date: 2024-06-13
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include "GridPoints.h"

namespace NVL_App
{
	class RefineResult
	{
	private:
		double _lastError;
		int _iterators;
	public:
		RefineResult() {}

		virtual double CalculateError(GridPoints * points, vector<double>& errors) = 0;
		virtual void SetState(vector<double>& variables) = 0;

		inline double& GetLastError() { return _lastError; }
		inline int& GetIterators() { return _iterators; }
	protected:
		inline void SetLastError(double value) { _lastError = value; }
	};
}
