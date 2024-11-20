//--------------------------------------------------
// A set of utilities for helping with unit testing
//
// @author: Wild Boar
//
// @date: 2024-11-18
//--------------------------------------------------

#pragma once

#include <iostream>
using namespace std;

#include <NVLib/PoseUtils.h>

#include <opencv2/opencv.hpp>
using namespace cv;

#include <CalibratorLib/HelperUtils.h>
#include <CalibratorLib/LoadUtils.h>
#include <CalibratorLib/PinholeParams.h>
using namespace NVL_App;

class TestUtils
{
public:

    //--------------------------------------------------
    // Build Grid
    //--------------------------------------------------

    /**
     * Add the functionality to build the associated grid
     * @param gridSize The size of the grid that we are making
     * @param blockSize The size of the blocks making up the grid
     * @param parameters The parameters we are using to construct the 3d Points
     */
    static inline unique_ptr<GridPoints> BuildGrid(const Size& gridSize, double blockSize, PinholeParams& parameters) 
    {
        auto result = new GridPoints(gridSize);

        auto pose = parameters.GetPoseMatrix();

        for (auto row = 0; row < gridSize.height; row++) 
        {
            for (auto column = 0; column < gridSize.width; column++) 
            {
                auto scenePoint = Point3d(column * blockSize, row * blockSize, 1);
                auto tscenePoint = NVLib::Math3D::TransformPoint(pose, scenePoint);
                auto imagePoint = NVLib::Math3D::Project(parameters.GetCamera(), tscenePoint);
                result->Update(Point2i(column, row), imagePoint, scenePoint);
            }
        }

        return unique_ptr<GridPoints>(result);
    }
};
