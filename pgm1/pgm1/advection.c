/*
 * ======================= advection ===================
 * Integrate forward (advection only) by one time step.
 * Arguments:
 *
 *	s1	real array	values at current step
 *	s2	real array	values at next step
 *	c	real		flow speed in linear case
 *	dx	real		grid spacing
 *	dt	real		time step
 *	i1,i2	integers	indices bounding array data
 *	nx	integer		number of physical grid points
 *	advection_type
 *              char 		if 'L', linear advection;
 *				otherwise, nonlinear
 */
#include <math.h>
void advection(float s1[],float s2[],float c,float dx,float dt,
                   int i1,int i2,int nx,char advection_type)
{
	int i;
	float courant;
        float sigma;
	if (advection_type == 'L') {

	  printf(" >Put integration code here for linear advection.\n");
	  for (i=i1; i<=i2; i++) {
	    courant = c*dt/dx;
            sigma =pow(courant,2)/2;
	    s2[i] = s1[i] - courant/2*(s1[i+1]-s1[i-1]) + sigma*(s1[i+1]-2*s1[i]+s1[i-1]);
	  }

	} else if (advection_type == 'N') {

	  printf(" >Put integration code here for nonlinear advection.\n");
	  for (i=i1; i<=i2; i++) {
	    courant = s1[i]*dt/dx;
            sigma = pow(courant,2)/2;
	    s2[i] = s1[i] - courant/2*(s1[i+1]-s1[i-1]) + sigma*(s1[i+1]-2*s1[i]+s1[i-1]);
	  }

	} else {
	  printf("Integrate: Error, unrecognized advection type '%c'\n",advection_type);
	  exit(1);
	}

	return;
}

