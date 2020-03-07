# pgm1
## Description
- Problem:  1-D linear and nonlinear advection
- Boundary conditions: periodic
- Flow field: constant (for linear cases), nonlinear in third case.
- Evaluation: save and plot maximum absolute value vs. time
- Method:  Lax-Wendroff

## Requiremnet
In the results shown below I have left the grid point count at 25 but have modified the code, namely:
added the two lines to implement periodic boundaries in the bc routine;
altered the advection.f90 file for Lax-Wendroff for linear and nonlinear cases
To test your code, fix your bc.f90 and advection.f90 routines and run the code, still with NX=25.
Remember to change the grid point count NX to 75 before running the official problem to plot and hand in!!!!
For these test cases, nx should be left at 25.
Set the plot frequency to be as often as you wish (e.g. every step).

## Results
- Case A: Courant number 0.5; run 50 steps; Linear.
- Case B: Courant number 1.5; (try to) run 20 steps; Linear.
- Case C: Courant number: I entered 1; run 20 steps; Nonlinear.


