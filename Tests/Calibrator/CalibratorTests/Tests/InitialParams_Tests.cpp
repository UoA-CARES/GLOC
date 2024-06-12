//--------------------------------------------------
// Unit Tests for class InitialParams
//
// @author: Wild Boar
//
// @date: 2024-06-12
//--------------------------------------------------

#include <gtest/gtest.h>

#include <CalibratorLib/InitialParams.h>
using namespace NVL_App;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Determine that the file initialize is as expected
 */
TEST(InitialParams_Test, file_initialize)
{
	// Setup: Setup test data
	auto camera = (Mat) (Mat_<double>(3,3) << 1500, 0, 640, 0, 1499, 480, 0, 0, 1);
	auto distortion = (Mat) (Mat_<double>(4,1) << 0.1, -0.2, 0.3, -0.5 );
	auto size = Size(1280, 960);

	// Write this data to file
	auto writer = FileStorage("params.xml", FileStorage::FORMAT_XML | FileStorage::WRITE);
	writer << "camera" << camera << "distortion" << distortion << "size" << size;
	writer.release();

	// Execute
	auto params = InitialParams("params.xml");

	// Confirm
	auto expected = (double *) camera.data; auto actual = (double *) params.GetCamera().data; 
	for (auto i = 0; i < 9; i++) ASSERT_EQ(expected[i], actual[i]);

	expected = (double *) distortion.data; actual = (double *) params.GetDistortion().data; 
	for (auto i = 0; i < 4; i++) ASSERT_EQ(expected[i], actual[i]);

	ASSERT_EQ(size.width, params.GetImageSize().width);
	ASSERT_EQ(size.height, params.GetImageSize().height);
}