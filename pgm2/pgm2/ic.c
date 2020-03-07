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

void ic(float s[][NYDIM],float dx,float dy,int i1,int i2,int j1, int j2, float u[][NXDIM], float v[][NYDIM])
{    
	pi = 4.0*atan(1.0);
        float x0,y0,x,y,r;
        float distance;            
        x0 = 0;
        y0 = 0.3;
        r = 0.12;  

 	/* In loop below:
 	 * i runs i1...i2 and is actual array offset/memory adddress
 	 * i=i1 is the first physical point; i-i1 used to find X value
 	 */
    
        int i,j;
        for (i = i1; i <= i2; i++){
        	for (j = j1; j <= j2; j++){
                	x = -0.5+dx*(i-i1);
			y = -0.5+dy*(j-j1);
			distance = pow(pow(x-x0,2) + pow(y-y0,2),0.5);
			if (distance > r)
				s1[i][j] = 0;
			else
				s1[i][j] = 5*(1+cos(pi*distance/r));
			u[i][j] = -2*y;
			v[i][j] = -2*x;
		}
        }
	
        u[i2+1][j2] = u[i2][j2];
	v[i2][j2+1] = u[i2][j2]; 

	return;
}

