#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

void preprocess(Mat *sudoku, Mat *outerBox, Mat *kernel){
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
    dilate(*outerBox, *outerBox, *kernel);
}

void blobDetector(Mat *outerBox, Mat *kernel){
    int count = 0;
    int max = 1;
    Point maxPt;

    for(int y = 0; y < outerBox->size().height; ++y){
        uchar *row = outerBox->ptr(y);
        for(int x = 0; x < outerBox->size().width; ++x){
            //Ensures that only the white areas are flooded
            if(row[x] >= 128){
                // Fill out all the illuminated points with a dull gray
                int area = floodFill(*outerBox, Point(x, y), CV_RGB(0,0,64));
                if(area > max){
                    maxPt = Point(x,y);
                    max = area;
                }
            }
        }
    }
    //Flood fill the point with the maximum area with white.
    // Biggest blob is now white
    floodFill(*outerBox, maxPt, CV_RGB(255,255,255));
    //Need to turn the other blobs that were grey black
    for(int y = 0; y < outerBox->size().height; ++y){
        uchar *row = outerBox->ptr(y);
        for(int x = 0; x < outerBox->size().width; ++x){
            if(row[x] == 64 && x != maxPt.x && y != maxPt.y){
                int area = floodFill(*outerBox, Point(x,y), CV_RGB(0,0,0));
            }
        }
    } 
    //Need to erode a bit since we dilated before
    erode(*outerBox, *outerBox, *kernel);
}

void drawLine(Vec2f line, Mat *img, Scalar rgb = CV_RGB(0,0,255)){
    if(line[1] != 0){
        float m = -1/tan(line[1]);
        float c = line[0]/sin(line[1]);
        cv::line(*img, Point(0, c), Point(img->size().width, m*img->size().width+c), rgb);
    }
    else {
        cv::line(*img, Point(line[0], 0), Point(line[0], img->size().height), rgb);
    }
}

vector<Vec2f> getLines(Mat *outerBox){
   vector<Vec2f> lines; 
   HoughLines(*outerBox, lines, 1, CV_PI/180, 200); 
   for(int i = 0; i < lines.size(); ++i){
       drawLine(lines[i], outerBox, CV_RGB(0,0,128));
   }
   return lines;
}



int main(){
    Mat sudoku = imread("sudoku.jpg",CV_LOAD_IMAGE_GRAYSCALE);
    Mat outerBox = Mat(sudoku.rows, sudoku.cols, CV_8UC1);
    Mat kernel = (Mat_<uchar>(3,3) << 0,1,0,1,1,1,0,1,0);

    vector<Vec2f> lines;
    preprocess(&sudoku, &outerBox, &kernel);
   // imshow("OuterBox", outerBox);

    blobDetector(&outerBox, &kernel);
    //imshow("Threshold", outerBox);

    lines = getLines(&outerBox);
    imshow("Lines", outerBox);
    waitKey(0);
    return 0;
}
