/*
 * ============================ ic =====================
 * IC sets the initial condition
 * Arguments:
 *
 *	s1	real array	IC data. Set i1..i2 here;
 *				  [i1-1],[i2+1] = ghost zones
 *				  if 1 ghost point on each side
 *	dx	real		grid spacing
 *	i1,i2	integers	indices bounding array data
 *	nx	integer		number of physical grid points
 *
 */
#include <math.h>

void ic(float s1[],float dx,int i1,int i2,int nx)
{
	int i;
	float x,pi,length;

	pi = 4.0*atan(1.0);
 	length = dx * (float) nx;

 	/* In loop below:
 	 * i runs i1...i2 and is actual array offset/memory adddress
 	 * i=i1 is the first physical point; i-i1 used to find X value
 	 */

	for (i=i1; i<=i2; i++) {
	  x = dx * (float)(i-i1);
	  s1[i] = sin( 2.*pi/length*x );
	}

	return;
}

