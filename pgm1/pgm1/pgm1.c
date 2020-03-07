/*
 *  ATMS 502 / CSE 566 -- Spring, 2019
 *  Demo for pgm1:  Linear and nonlinear advection
 *  ===>>>>> Yen Wen Lu <<<=== and in "name" variable below <<<<<===
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

#define NX 75
#define BC_WIDTH 1
#define I1 BC_WIDTH
#define I2 I1+NX-1
#define NXDIM NX+2*BC_WIDTH
#define MAXSTEP 500

char *name  = "Yen Wen Lu";
char *title = "Program 1";

/* Arrays and other variables */

	float s1[NXDIM],s2[NXDIM],strue[NXDIM];
	float strace[MAXSTEP],dt,courant,smax,c,dx;
	int i,n,nstep,nplot;
	char advection_type, reply[10];

/* Variables for run history */

	float history[NX][MAXSTEP];

/* Variables to reverse default black/white colors in NCAR Graphics */

	Gcolr_rep rgb1,rgb2;

/* Function prototype declarations
 * Prototypes declarations in C, like Interface blocks in Fortran, can
 * prevent difficult-to-track errors when functions are called incorrectly. 
 * More info:  https://computer.howstuffworks.com/c13.htm
 */

	void ic(float s[],float dx,int i1,int i2,int nx);
	void stats(float s[],int i1,int i2,int nx,int nstep,float *smax);
	void plot1d(float s[],int i1,int i2,int nx,int n,float smax,
		    int overlay,float strue[],char *title,char *name);
	void sfc(int nx,int maxstep,int nstep,float history[NX][MAXSTEP],
		 float simtime,float angh,float angv,char *title,char *name);
	void bc(float s[],int i1,int i2,int nx);
	void advection(float s1[],float s2[],float c,float dx,float dt,
		       int i1,int i2,int nx,char advection_type);
 	void update(float s1[],float s2[],int i1,int i2,int nx);

/* Parameters and input .................................... */

	printf("Program #1       Numerical Fluid Dynamics\n\n");
	printf("NX=%d, BC_WIDTH=%d, I1=%d, I2=%d, NXDIM=%d\n",
		NX,BC_WIDTH,I1,I2,NXDIM);

	c = 1.0;
	dx = 0.1;

	printf("Enter courant number (normally <= 1; use 1.0 for nonlinear): ");
	scanf("%f",&courant);
	dt = courant*dx/c;

 	printf("For Courant number %5.2f, time step dt = %6.3f\n", courant, dt);
 	printf("Number of steps for one complete cycle = %.0f\n",( dx*(float)NX / c / dt ));

	printf("Enter number of time steps to take: ");
	scanf("%d",&nstep);
 	if (nstep > MAXSTEP) {
 	  printf("nstep too large: exceeds MAXSTEP, which equals %d\n",MAXSTEP);
 	  printf("increase MAXSTEP and recompile.\n");
 	  exit(1);
 	}

	printf("Enter plot interval, in steps (1=every step): ");
	scanf("%d",&nplot);

	printf("Enter L for linear, N for nonlinear advection: ");
	scanf("%s",reply);
	advection_type = reply[0];
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
	ic(s1,dx,I1,I2,NX);
	stats(s1,I1,I2,NX,0,&smax);
	plot1d(s1,I1,I2,NX,0,smax,0,strue,"Initial condition",name);
/*
 * Copy the initial condition to the "strue" array.
 *  We use it later since the initial condition is the true final solution.
 */
	for (i=I1; i<=I2; i++) strue[i]=s1[i];

/*
 * .. Integrate .....................................................
 */

	for (n=1; n<=nstep; n++) {

/*  . . . Set boundary conditions				*/
	  bc(s1,I1,I2,NX);

/*  . . . Compute values at next step				*/
	  advection(s1,s2,c,dx,dt,I1,I2,NX,advection_type);

/*  . . . Do array update at end of time step			*/
 	  update(s1,s2,I1,I2,NX);

/*  . . . Copy latest solution s2() to history array
 *        "i" used for "s2" array subscripting			*/
	  for (i=I1; i<=I2; i++)
	    history[i-I1][n-1] = s2[i];

/*  . . . Stats							*/
	  stats(s2,I1,I2,NX,n,&smax);
	  strace[n-1] = smax;

/*  . . . Plot fields when needed				*/
	  if (n == nstep || n%nplot == 0) {
	    if (advection_type == 'L') {
	      plot1d(s2,I1,I2,NX,n,smax,1,strue,title,name);
	    } else {
	      plot1d(s2,I1,I2,NX,n,smax,0,strue,title,name);
	    }
	  }

/*  . . . Check if problem out of bounds			*/
	  if (smax > 1.5) {
	    printf("Stop - solution blowing up at step %d\n",n);
	    plot1d(s2,I1,I2,NX,n,smax,0,strue,"Solution blowing up",name);
	    nstep = n;
	    break;
	  }

	}	/* end of time loop n = 1,...,nstep */

/*
 * Run complete - do final plots
 */

/* . . Plot Smax(t)						*/
	c_agsetf("Y/MINIMUM.",0.0);
	c_agsetf("Y/MAXIMUM.",1.5);
	c_anotat("N","Max value",0,0,0,0);
	stats(strace,0,nstep-1,nstep,nstep,&smax);
	plot1d(strace,0,nstep-1,nstep,nstep,smax,0,strue,"Smax vs. time",name);

/* . . Plot history surface s(x,t)
 *     Three different viewpoints are used */
	sfc(NX,MAXSTEP,nstep,history,(dt*(float)nstep),-90., 0.,
          "Time-Space evolution (view: -90,  0)",name);
	sfc(NX,MAXSTEP,nstep,history,(dt*(float)nstep),-75., 5.,
	  "Time-Space evolution (view: -75, +5)",name);
	sfc(NX,MAXSTEP,nstep,history,(dt*(float)nstep),-30.,20.,
	  "Time-Space evolution (view: -30,+20)",name);

/*
 *  Close the graphics package and stop.
 */

	gdeactivate_ws(WKID);
	gclose_ws(WKID);
	gclose_gks();

	exit;
}
