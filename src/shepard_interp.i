/* File : example.i */
%module shepard_interp
%{
/* Put headers and other declarations here */
#define SWIG_FILE_WITH_INIT

#ifdef __cplusplus
extern "C"
{
#endif
#include "shepard_interp_nd.h"
#ifdef __cplusplus
}
#endif

%}

%include "numpy.i"

%init %{
    import_array();
%}

%apply (int DIM1, int DIM2, double* IN_ARRAY2) {(int m1, int nd1, double* xd)};
%apply (int DIM1, double* IN_ARRAY1) {(int nd2, double* zd)};
%apply (int DIM1, int DIM2, double* IN_ARRAY2) {(int m3, int nd3, double* xi)};
%apply (int DIM1, double* ARGOUT_ARRAY1) {(int nd4, double* za)};

%rename (shepard_interp_nd) _shepard_interp_nd;
%ignore shepard_interp_nd;
/*%include "shepard_interp_nd.h"*/
/*double *shepard_interp_nd ( int m, int nd, double xd[], double zd[], double p, int ni, double xi[] );*/

%exception _shepard_interp_nd {
    $action
    if (PyErr_Occurred()) SWIG_fail;
}
%inline %{
void _shepard_interp_nd( int m1, int nd1, double* xd, int nd2, double* zd, int m3, int nd3, double* xi, int nd4, double* za, double p)  
{
    if (m1 != m3) {
        PyErr_Format(PyExc_ValueError,
                     "Dimensions of Arrays don't match, lengths (%d,%d) given",
                     m1, m3);
    }
    if (nd1 != nd2) {
        PyErr_Format(PyExc_ValueError,
                     "Dimensions of Arrays don't match, lengths (%d,%d) given",
                     nd1, nd2);
    }
    if (nd3 != nd4) {
        PyErr_Format(PyExc_ValueError,
                     "Dimensions of Arrays don't match, lengths (%d,%d) given",
                     nd3, nd4);
    }

    int i;
    double *tmp = NULL;
    tmp = shepard_interp_nd(m1,nd1,xd,zd,p,nd3,xi);
    for( i = 0; i < nd3; i++){
        za[i] = tmp[i];
    } 
    free(tmp);
}
%}

/*%pythoncode %{
def shepard_interp_nd(X,f, Xk, p):
    return test._shepard_interp_nd(X,f,p,Xk,Xk.shape[1])
}%*/

%clear (int m1, int nd1, double* xd),(int nd2, double* zd),(int m3, int nd3, double* xi),(int nd4, double* za);

