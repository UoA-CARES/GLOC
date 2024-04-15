# Diary Notes #

**Diary Nodes**

**18 April 2024**

So far, the following successes have been achieved:

* A synthetic point generator, that can basically create points for the purpose of testing whether I can acquire the original configuration.
* A random search based distortion estimation engine, that can estimate the distortion for a single homography.

The next set of goals are built around the problem of calibrating a given set of "real world" images. The following are expected to be the related tasks:

* Create a point convert to extract point measurements from the calibration tool.
* Update Distortion Estimator to process two homographies (left and right).
* Extract the calibration parameters for a single image with two calibration grids.
* Build a stereo finder for the system.
* Test with stereo matching.
* Test with stereo size estimation.

**05 March 2024**

So I am working towards distortion estimation from images. The first step is to do this with synthetic images. Therefore, the following steps are next:

* Generate points based on a configuration file.
* Attempt to estimate the distortion and remove the distortion from the points
* Perform a calibration on the undistorted points and see the effect.

**01 March 2024**

Light travels in a straight line, therefore you would expect optical models to be linear equations. This is true, mostly, but there is a component called _distortion_ that is non-linear. Distortion exists because lenses bend the light, as well as many real-world physical effects such as refraction. This non-linear aspect is essentially undesirable because it greatly complicates mathematical optimization, and many optical models are developed precisely for the purpose of solving optimization problems. 

Our purpose, in this work, is to develop a camera calibration tool. Traditional camera, calibration approaches use linear equations to model an initial estimation of calibration, which is then "refined" using a non-linear optimizer with respect to some distortion model. The proposal that my work explores, is that I attempt to estimate the distortion upfront, and then optimize the linear equations afterwards. Assuming that it is possible to estimate distortion upfront (from a checkerboard), there are several advantages of doing so:

* The linear equation solution deals with "real" values rather than approximated values - making debugging the process more intuitive.
* If only distortion removal is required, there is no need to calculate camera parameters.
* Distortion can be more explicily optimized as a force of non-linearity in the system, rather than an explanation of error with respect to the linear equations.

My first step in this research is to revisit the problem of grid-based distortion estimation. In my PhD thesis, I solved this problem using a traditional Levenberg-Marquardt iterative optimizer.

