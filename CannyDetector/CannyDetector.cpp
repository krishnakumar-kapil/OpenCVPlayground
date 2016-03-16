#include <stdio.h>
#include <stdlib.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


Mat src, src_gray;
Mat dst, detected_edges;

int kernel_size = 3;
int detected_edge
int edgeThresh = 1;
int lowThreshold;
int const maxThreshold = 100;
int ratio = 3;
char* window_name = "Canny Detector";



int main(int argc, char** argv){
	src = imread( argv[1]);
	if( !src.data)
		return -1;

	



}

void CannyThreshold(int, void*){
	blur(src_gray, detected_edge, Size(3,3));
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
	dst= Scalar::all()
}