#include <iostream>
#include <string>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

int main(int argc, char** argv){
    Mat orig_image;
    Mat gray, src_gray;
    int ddepth = CV_16S;
    int scale = 1;
    int delta = 0;
    char *window_name = "Seam Carving";

    orig_image = imread(argv[1], 1);
    namedWindow("Original Image", WINDOW_AUTOSIZE);
    imshow("Original Image", orig_image);
    waitKey(0);
    cvtColor(orig_image, src_gray, CV_BGR2GRAY);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat grad;
    Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);

    Sobel(src_gray, grad_y, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    //addWeighted(abs_grad_x, 0.5, abs_grad_y, .5, grad, 0, grad );
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
   namedWindow(window_name, WINDOW_AUTOSIZE);
   imshow(window_name, grad);


    waitKey(0);
    return 0;
}
