/**
 * @file isContourConvex.cpp
 * @brief mex interface for isContourConvex
 * @author Kota Yamaguchi
 * @date 2011
 */
#include "mexopencv.hpp"
using namespace std;
using namespace cv;

/**
 * Main entry called from Matlab
 * @param nlhs number of left-hand-side arguments
 * @param plhs pointers to mxArrays in the left-hand-side
 * @param nrhs number of right-hand-side arguments
 * @param prhs pointers to mxArrays in the right-hand-side
 */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[] )
{
	// Check the number of arguments
	if (nrhs!=1 || nlhs>1)
        mexErrMsgIdAndTxt("mexopencv:error","Wrong number of arguments");
    
	// Argument vector
	vector<MxArray> rhs(prhs,prhs+nrhs);
#if CV_MINOR_VERSION >= 2
	vector<MxArray> vm(rhs[0].toStdVector<MxArray>());
	vector<Point2f> points(vm.size());
	for (int i=0; i<vm.size(); ++i)
		points[i] = vm[i].toPoint_<float>();
#else
	Mat points(rhs[0].toMat(CV_32F));
#endif
	bool b = isContourConvex(points);
	plhs[0] = MxArray(b);
}