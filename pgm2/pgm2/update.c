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

void update(float s1[][NYDIM],float s2[][NYDIM],int i1,int i2,int j1,int j2)
{
	int i,j;

	for (i=i1; i<=i2; i++){
		for (j=j1; j<=j2; j++){ 
	  		s1[i][j] = s2[i][j];
		}
	
	}
	return;
}

