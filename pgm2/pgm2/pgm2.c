/*
 *  ATMS 502 / CSE 566 -- Spring, 2019
 *  Demo for pgm1:  Linear and nonlinear advection
 *  ===>>>>> PUT YOUR NAME HERE! <<<=== and in "name" variable below <<<<<===
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncarg/ncargC.h>
#include <ncarg/gks.h>
#define IWTYPE 1
#define WKID   1

main()
{

/*
 * Definitions
 */

#define NX 51
#define NY 51
#define BC_WIDTH 6
#define NXDIM NX+BC_WIDTH
#define NYDIM NY+BC_WIDTH
#define MAXSTEP 600

char *name  = "Your name";
char *title = "Program 2";

/* Arrays and other variables */

	float s1[NXDIM][NYDIM],s2[NXDIM][NYDIM],u[NXDIM][NYDIM],v[NXDIM][NYDIM],strue[NXDIM][NYDIM];
        float s1d[NXDIM],s2d[NXDIM],u1d[NXDIM],v1d[NYDIM];
	float strace[MAXSTEP],dt,courant,smax,dx,dy;
	int i,j,n,nstep,ghost,I1,I2,J1,J2,nplot;
	char advection_type, reply[10];
	int colors,pltzero;
/*        char title[25];  */
        float cint,simtime,angh,angv;
        float splot[NX][NY];

/* Variables to reverse default black/white colors in NCAR Graphics */

	Gcolr_rep rgb1,rgb2;

/* Function prototype declarations
 * Prototypes declarations in C, like Interface blocks in Fortran, can
 * prevent difficult-to-track errors when functions are called incorrectly. 
 * More info:  https://computer.howstuffworks.com/c13.htm
 */

	void ic(float s[][NYDIM],float dx,float dy,int i1,int i2,int j1, int j2, float u[][NXDIM], float v[][NYDIM]);
/* 	void stats(float s[],int i1,int i2,int nx,int nstep,float *smax);	 havent modified */
	void sfc(int nx,int ny,int nymax,float splot[NX][NY],float simtime,
         float angh,float angv,char *label,char *name);
	void bc(float s1[][NYDIM],int i1, int i2, int j1, int j2,int ghost);
	void advection(float s1[][NXDIM],float s2[][NYDIM],float u[][NXDIM],float v[][NXDIM], float dx,float dt,
                   int i1,int i2,int j1,int j2,int nx,int ghost);
	void advect1d(float s1[],float s2[],u1d[],float dx,float dt,
                   int i1,int i2,int nx,int ghost);
	void update(float s1[][NYDIM],float s2[][NYDIM],int i1,int i2,int j1,int j2);
	void contr(int nx,int ny,float splot[NX][NY],float cint,float simtime,char *title,int colors,int pltzero,int nestX1,int nestX2,
           	   int nestY1,int nestY2,char *name);


/* Parameters and input .................................... */

	printf("Program #2      Numerical Fluid Dynamics\n\n");
/*	printf("NX=%d BC_WIDTH=%d, I1=%d, I2=%d, NXDIM=%d\n",                  havent modified*/
		NX,BC_WIDTH,I1,I2,NXDIM);

	dx = 1/(NX-1);      
	dy = 1/(NY-1);
	dt = 1/400;          
        int ghost,I1,I2,J1,J2
	printf("Choose scheme(enter 1, 2 or 3): 1 Lax-Wendroff, 2 Takacs, 3 Crowley 6th-order ");
	scanf("%d",&ghost);
	switch (ghost){
        	case1:
			I1 = 1;
			I2 = NX+I1-1;
			J1 = 1;
			J2 = NY+I2-1;
	        case2:
                        I1 = 2;
                        I2 = NX+I1-1;
			J1 = 2;
                        J2 = NY+I2-1;
		case3:
                        I1 = 3;
                        I2 = NX+I1-1;
			J1 = 3;
                        J2 = NY+I2-1;
	}



	printf("Enter number of time steps to take: ");
	scanf("%d",&nstep);
 	if (nstep > MAXSTEP) {
 	  printf("nstep too large: exceeds MAXSTEP, which equals %d\n",MAXSTEP);
 	  printf("increase MAXSTEP and recompile.\n");
 	  exit(1);
 	}

	printf("Enter plot interval, in steps (1=every step): ");
	scanf("%d",&nplot);
	
/*
 * Open the NCAR Graphics package and set colors.
 */
	gopen_gks("stdout",0);
	gopen_ws(WKID, NULL, IWTYPE);
	gactivate_ws(WKID);

	/* omit following four lines to invert black/white colors */
	rgb1.rgb.red = 1.; rgb1.rgb.green = 1.; rgb1.rgb.blue = 1.;
	rgb2.rgb.red = 0.; rgb2.rgb.green = 0.; rgb2.rgb.blue = 0.;
        gset_colr_rep(WKID,0,&rgb1);
        gset_colr_rep(WKID,1,&rgb2);
/*
 * X/Y-axis labels
 */
	c_anotat("X","S",0,0,0,0);
/*
 * Set default Y plot bounds
 */
	c_agsetf("Y/MINIMUM.",-1.2);
	c_agsetf("Y/MAXIMUM.", 1.2);
/*
 * Set and plot the initial condition
 */
	ic(s1,dx,dy,I1,I2,J1,J2,u,v);
/*	stats(s1,I1,I2,NX,0,&smax);		wait */

/*
 * Copy the initial condition to the "strue" array.
 *  We use it later since the initial condition is the true final solution.
 */
	for (i=I1; i<=I2; i++){
		for (j=J1; j<=J2;j++){	
	 	   strue[i][j]=s1[i][j]; 
		}
	}
/*
 * .. Integrate .....................................................
 */

	for (n=1; n<=nstep; n++) {

/*  . . . Set boundary conditions				*/
	  bc(s1,I1,I2,J1,J2);
       	  
/*  . . . Compute values at next step				*/
	  advection(s1,s2,u,v,dx,dt,
                   I1,I2,J1,J2,nx,ghost)
	  
/*  . . . Do array update at end of time step			*/
	  update(float s1,float s2,int I1,int I2,int J1,int J2)


/*  . . . Stats							*/
/*	  stats(s2,I1,I2,NX,n,&smax);           wait            */
/*	  strace[n-1] = smax;                                   */

/*  . . . Plot fields when needed				*/
	  void contr(int nx,int ny,float splot[NX][NY],float cint,float simtime,char *title,int colors,int pltzero,int nestX1,int nestX2,
          	int nestY1,int nestY2,char *name);
          void sfc(int nx,int ny,int nymax,float splot[NX][NY],float simtime,
          	float angh,float angv,char *label,char *name);

	  if (n == nstep || n%nplot == 0) {
/*
 * Plot contours
 * n is our loop counter in the full code (use "0" for initial condition)
 * cint is contour interval ( 5.0 = plot contours at -10, -5, +5, +10, ... )
 * simtime is the integration time in seconds
 * colors is the color setting in the contr routine, 0=default
 * title is the contour/sfc text plotted at the top
 * name is Your name, as usual, in your main program
 * pltzero, if false, skips plotting the zero contour (recommended)
 */

   	printf("Plotting contours.\n"); /* delete this when contour plots are working */

        for (j=J1; j<=J2; j++) {        /* copy s1 to NX,NY plotting array */
          for (i=I1; i<=I2; i++) {
            splot[i-I1][j-J1] = s1[i][j]; } } /* works for any BC_WIDTH */

        cint    = 1.0;  /* contour interval */
        colors  =   0;  /* positive values colored red, negative blue, all solid */
        pltzero =  -1;  /* don't plot the often noisy zero line */
        simtime = dt*(float)n;
        sprintf(title,"Contour plot at n = %d",n);
        contr(NX,NY,splot,cint,simtime,title,colors,pltzero,0,0,0,0,name);

/*
 * Plot surface
 * angh is horizontal viewing angle, degrees, counter-clockwise from X-axis
 * angv is vertical   viewing angle above x-y plane
 */

        printf("Plotting surface.\n");  /* delete this when sfc plots are working */

        for (j=J1; j<=J2; j++) {        /* copy s1>splot if you haven't already done it */
          for (i=I1; i<=I2; i++) {
            splot[i-I1][j-J1] = s1[i][j]; } } /* works for any BC_WIDTH */

        angh = -45.0;
        angv =  20.0;
        sprintf(title,"Surface plot at n = %d",n);
        sfc(NX,NY,NY,splot,simtime,angh,angv,title,name);
	}	 

/*
 *  Close the graphics package and stop.
 */

	gdeactivate_ws(WKID);
	gclose_ws(WKID);
	gclose_gks();

	exit;
}
