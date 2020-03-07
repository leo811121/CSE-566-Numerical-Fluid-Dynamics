/*
 * ============================ bc =====================
 * BC sets the boundary conditions
 * Arguments:
 *
 *	s1	real array	values at current time step
 *	i1,i2	integers	indices bounding array data
 *	nx	integer		main array size, not including
 *				extra 'ghost' zones/points
 */

void bc(float s1[],int i1,int i2,int nx)
{
	printf(" >Set boundary conditions here.\n");       
        s1[i1-1] = s1[i2];
        s1[i2+1] = s1[i1];
	return;
}

