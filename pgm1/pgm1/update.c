/*
 * ========================= update ====================
 * Update: replace old values with new ones
 * We are not copying ghost points here.
 * Arguments:
 *
 *	s1,s2	real arrays	old, new data arrays
 *	i1,i2	integers	indices bounding array data
 *	nx	integer		size of arrays w/o ghost points
 *
 */

void update(float s1[],float s2[],int i1,int i2,int nx)
{
	int i;

	for (i=i1; i<=i2; i++)
	  s1[i] = s2[i];

	return;
}

