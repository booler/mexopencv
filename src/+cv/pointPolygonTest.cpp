/**
 * @file pointPolygonTest.cpp
 * @brief mex interface for pointPolygonTest
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
	if (nrhs<2 || nlhs>1)
        mexErrMsgIdAndTxt("mexopencv:error","Wrong number of arguments");
    
	// Argument vector
	vector<MxArray> rhs(prhs,prhs+nrhs);
#if CV_MINOR_VERSION >= 2
	vector<MxArray> vm(rhs[0].toStdVector<MxArray>());
	vector<Point2f> contour(vm.size());
	for (int i=0; i<vm.size(); ++i)
		contour[i] = vm[i].toPoint_<float>();
#else
	Mat contour(rhs[0].toMat(CV_32F));
#endif
	Point2f pt(rhs[1].toPoint_<float>());
	bool measureDist=false;
	for (int i=2; i<nrhs; i+=2) {
		string key(rhs[i].toString());
		if (key=="MeasureDist")
			measureDist = rhs[i+1].toBool();
		else
			mexErrMsgIdAndTxt("mexopencv:error","Wrong number of arguments");
	}
	plhs[0] = MxArray(pointPolygonTest(contour,pt,measureDist));
}