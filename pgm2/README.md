# pgm2
## Description
- Problem:  2-D linear advection via fractional step (directional) splitting
- Boundary conditions: 0-gradient in both directions (ghost point values = nearest edge value)
- Flow field: rotational flow (counter-clockwise), constant w/time.
- Evaluation: Use Takacs (1985) error statistics over the entire 2-D domain; initial condition = "true" solution at final time.
- Methods:  Lax-Wendroff (from program 1) and Takacs methods
- [details](https://atmos.illinois.edu/courses/atmos502-sp2020/Handouts/ComputerProb2.pdf)

## Requirement
- Plots: contour and 3D surface plots of the initial condition and, for each method,
solution at 600 steps. Also, for each method, plots of smin(t) and smax(t).
- Print and hand in Takacs error data to 5 decimal places for your final solutions.

## Result 
![image](https://github.com/leo811121/CSE-566-Numerical-Fluid-Dynamics/blob/master/image/pgm2.JPG)
