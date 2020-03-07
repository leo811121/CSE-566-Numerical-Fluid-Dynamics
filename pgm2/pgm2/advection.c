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
void advection(float s1[][NXDIM],float s2[][NYDIM],float u[][NXDIM],float v[][NYDIM], float dx,float dt,
                   int i1,int i2,int j1,int j2,int nx,int ghost)
{

	for (i=I1;i<=I2;i++){
                for (j=0;j<=NYDIM;j++){
                        s1d[j]=s1[i][j];
                }
          	for (j=0;j<=NYDIM;j++){
                	u1d[j]=u[i][j];
          	}
          	advect1d(s1d,s2d,u1d,dx,dt,I1,I2,ghost);
		for (j=0;j<=NYDIM;j++){
                        s2[i][j]=s2d[j];
                }
     
	}

       for (j=J1;j<=J2;j++){
                for (i=0;i<=NXDIM;i++){
                        s1d[i]=s2[i][j];
                }		
		for (i=0;i<=NXDIM;i++){
                        v1d[i]=v[i][j];
               	}
		advect1d(s1d,s2d,v1d,dy,dt,J1,J2,ghost);
		for (i=0;j<=NXDIM;i++){
                        s2[i][j]=s2d[i];
                }

      }

	return;
}


