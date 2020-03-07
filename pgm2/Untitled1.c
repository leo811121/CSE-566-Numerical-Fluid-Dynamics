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
#define BC_WIDTH 3
#define NXDIM NX+3*BC_WIDTH
#define NYDIM NY+3*BC_WIDTH
#define MAXSTEP 600

