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


void bc(float s1[][NYDIM],int i1, int i2, int j1, int j2,int ghost){
	int i,j;
	for(i=i1; i<=i2; j++){
		for(j=1; j<=ghost; j++ ){
			s1[i1][j1-j]=s1[i1][j1];
			s1[i2][j2+j]=s1[i2][j2+j];
		}
	}
	for(j=j1; j<=j2; j++){
                for(i=1; i<=ghost; i++ ){
			s1[i1-i][j1]=s1[i1][j1];
			s1[i1+i][j2]=s1[i1][j2];
		{
	}


}

