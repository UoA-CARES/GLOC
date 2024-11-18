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
                auto scenePoint = Point3d(column * blockSize, row * blockSize, 800);
                auto tscenePoint = NVLib::Math3D::TransformPoint(pose, scenePoint);
                auto imagePoint = NVLib::Math3D::Project(parameters.GetCamera(), tscenePoint);
                result->Update(Point2i(column, row), imagePoint, scenePoint);
            }
        }

        return unique_ptr<GridPoints>(result);
    }

    //--------------------------------------------------
    // Build parameters
    //--------------------------------------------------

    /**
     * Convert the matrices into a vector of parameters
     * @param camera The provided camera matrix
     * @param pose_1 The pose of the first grid
     * @param pose_2 The pose of the second grid
     */
    static inline Mat BuildParameters(Mat& camera, Mat& pose_1, Mat& pose_2) 
    {
        auto clink = (double *) camera.data;
        auto p_1link = (double *) pose_1.data;
        auto P_2link = (double *) pose_2.data;

        // Get the camera matrix parameters
        auto fx = clink[0], fy = clink[4], cx = clink[2], cy = clink[5];

        // Get the p_1 parameters
        auto rvec_1 = Vec3d(); auto tvec_1 = Vec3d(); NVLib::PoseUtils::Pose2Vectors(pose_1, rvec_1, tvec_1);

        // Get the p_2 parameters
        auto rvec_2 = Vec3d(); auto tvec_2 = Vec3d(); NVLib::PoseUtils::Pose2Vectors(pose_2, rvec_2, tvec_2);

        return (Mat_<double>(16,1) << fx, fy, cx, cy, rvec_1[0], rvec_1[1], rvec_1[2], tvec_1[0], tvec_1[1], tvec_1[2], rvec_2[0], rvec_2[1], rvec_2[2], tvec_2[0], tvec_2[1], tvec_2[2]);  
    }
};
