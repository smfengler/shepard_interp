# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <string.h>

# include "shepard_interp_nd.h"

double r8vec_dot_product(int n, double a1[], double a2[])

/******************************************************************************/
/*
 Purpose:

 R8VEC_DOT_PRODUCT computes the dot product of a pair of R8VEC's.

 Licensing:

 This code is distributed under the GNU LGPL license.

 Modified:

 26 July 2007

 Author:

 John Burkardt

 Parameters:

 Input, int N, the number of entries in the vectors.

 Input, double A1[N], A2[N], the two vectors to be considered.

 Output, double R8VEC_DOT_PRODUCT, the dot product of the vectors.
 */
{
	int i;
	double value;

	value = 0.0;
	for (i = 0; i < n; i++) {
		value = value + a1[i] * a2[i];
	}
	return value;
}
/******************************************************************************/

/******************************************************************************/

double *shepard_interp_nd(int m, int nd, double xd[], double zd[], double p,
		int ni, double xi[])

/******************************************************************************/
/*
 Purpose:
 SHEPARD_INTERP_ND evaluates a multidimensional Shepard interpolant.

 Licensing:
 This code is distributed under the GNU LGPL license.

 Modified:
 02 October 2012

 Author:
 John Burkardt

 Reference:
 Donald Shepard,
 A two-dimensional interpolation function for irregularly spaced data,
 ACM '68: Proceedings of the 1968 23rd ACM National Conference,
 ACM, pages 517-524, 1969.

 Parameters:
 Input, int M, the spatial dimension.
 Input, int ND, the number of data points.
 Input, double XD[M*ND], the data points.
 Input, double ZD[ND], the data values.
 Input, double P, the power.
 Input, int NI, the number of interpolation points.
 Input, double XI[M*NI], the interpolation points.
 Output, double SHEPARD_INTERP_ND[NI], the interpolated values.
 */
{
	int i;
	int i2;
	int j;
	int k;
	double s;
	double t;
	double *w;
	int z;
	double *zi;

	w = (double *) malloc(nd * sizeof(double));
	zi = (double *) malloc(ni * sizeof(double));

//	for ( i2 = 0; i2 < m; i2++){
//		for( j=0; j<nd; j++){
//			fprintf(stdout,"%f\t",xd[i2 *nd+ j ]);
//
//		}
//		fprintf(stdout,"\n");
//	}


	for (i = 0; i < ni; i++) {
		if (p == 0.0) {
			for (j = 0; j < nd; j++) {
				w[j] = 1.0 / (double) (nd);
			}
		} else {
			z = -1;
			for (j = 0; j < nd; j++) {
				t = 0.0;
				for (i2 = 0; i2 < m; i2++) {
					t = t + pow(xi[i2 *ni+ i] - xd[i2*nd + j], 2);
				}
				w[j] = sqrt(t);
				if (w[j] == 0.0) {
					z = j;
					break;
				}
			}

			if (z != -1) {
				for (j = 0; j < nd; j++) {
					w[j] = 0.0;
				}
				w[z] = 1.0;
			} else {
				for (j = 0; j < nd; j++) {
					w[j] = 1.0 / pow(w[j], p);
				}
				s = 0.0;
				for (j = 0; j < nd; j++) {
					s = s + w[j];
				}
				for (j = 0; j < nd; j++) {
					w[j] = w[j] / s;
				}
			}
		}
		zi[i] = r8vec_dot_product(nd, w, zd);
	}
	free(w);

	return zi;
}
