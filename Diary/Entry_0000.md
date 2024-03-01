# Diary Notes #

| Author: WildBoar   |
|--------------------|
| Date: 1 March 2024 |
| Version: 1.00      |

Light travels in a straight line, therefore you would expect optical models to be linear equations. This is true, mostly, but there is a component called _distortion_ that is non-linear. Distortion exists because lenses bend the light, as well as many real-world physical effects such as refraction. This non-linear aspect is essentially undesirable because it greatly complicates mathematical optimization, and many optical models are developed precisely for the purpose of solving optimization problems. 

Our purpose, in this work, is to develop a camera calibration tool. Traditional camera, calibration approaches use linear equations to model an initial estimation of calibration, which is then "refined" using a non-linear optimizer with respect to some distortion model. The proposal that my work explores, is that I attempt to estimate the distortion upfront, and then optimize the linear equations afterwards. Assuming that it is possible to estimate distortion upfront (from a checkerboard), there are several advantages of doing so:

* The linear equation solution deals with "real" values rather than approximated values - making debugging the process more intuitive.
* If only distortion removal is required, there is no need to calculate camera parameters.
* Distortion can be more explicily optimized as a force of non-linearity in the system, rather than an explanation of error with respect to the linear equations.

My first step in this research is to revisit the problem of grid-based distortion estimation. In my PhD thesis, I solved this problem using a traditional Levenberg-Marquardt iterative optimizer

