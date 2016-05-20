#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

void preprocess(Mat *sudoku, Mat *outerBox){
    //Preprocess
    // What is the purpose of Gaussian Blurring things?
    // Supposedely smooths out the noise and makes detecting
    // lines easier
    GaussianBlur(*sudoku, *sudoku, Size(11,11), 0);
    // Purpose of Adaptive Threshold?
    //    Used for segmenting images based on illumination or color
    //    Becomes easier for a comp to analyse 
    //    adaptive allows it to be based on the mean illumination
    //    keeps the thing illumination independent
    //    The 5 and the 2 are mean over 5x5 window and subtracts 2 from the mean
    adaptiveThreshold(*sudoku, *outerBox,255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5,2);
    //invert the image since the borders are actually black
    bitwise_not(*outerBox, *outerBox);
    //Threshold can disconnect connected regions so fill them back
    Mat kernel = (Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);
    dilate(*outerBox, *outerBox, kernel);
 
}
int main(){
    Mat sudoku = imread("sudoku.jpg");
    Mat outerBox = Mat(sudoku.rows, sudoku.cols, CV_8UC1);

    preprocess(&sudoku, &outerBox);
   imshow("OuterBox", outerBox);
    waitKey(0);
    return 0;
}
