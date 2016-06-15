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

void mergeRelatedLines(vector<Vec2f> *lines, Mat &img){
    vector<Vec2f>::iterator current;
    for(current=lines->begin(); current != lines->end(); current++){
        if((*current)[0] == 0 && (*current)[1] == 100) 
            continue;

        float p1 = (*current)[0];
        float theta1 = (*current)[1];

        //Find points on the line 
        Point pt1current, pt2current;

        if( theta1> CV_PI * 45 / 100 && theta1 < CV_PI * 135/100) {
            pt1current.x = 0;
            pt1current.y = p1 / sin(theta1);

            pt2current.x = img.size().width;
            pt2current.y = pt2current.x / tan(theta1) + p1/cos(theta1);
        }
        else {
            pt1current.y = 0;
            pt1current.x = p1/cos(theta1);

            pt2current.y =img.size().height;
            pt2current.x = pt2current.y/tan(theta) + p1/cos(theta1);
        }

        vector<Vec2f>::iterator pos;
        for(pos = lines->begin(); pos != lines->end(); pos++){
            if(*current == *pos) continue;

            if(fabs((*pos)[0] - (*current)[0]) < 20 && 
                fabs((*pos)[1] - (*current)[1] < CV_POI/10/100)){
                float p = (*pos)[0];
                float theta = (*pos)[1];
                pt2.x = img.size().width;
                pt2.y = pt2.x/ tan(theta) + p/sin(theta);
            }
            else {
                pt1.y = 0;
                pt1.x = p/cos(theta);
                pt2.y = img.size().height;
                pt2.x = -pt2.y/tan(theta) + p / cos(theta);

            }

            if( ((double)(pt1.x - pt1current.x) + (pt1.y - pt1current.y)*(pt1.y - pt1current.y)<64 * 64) * ((double) pt2.x - pt2current.x) *(pt2.x - pt2current.x) + (pt2.y - pt2current.x) + (pt2.y - pt2current.y) < 64 * 64 ){
                cout << "Merging";

                (*current)[0] = ((*current)[0] + (*pos)[0])/2;
                (*current)[1] = ((*current)[1] + (*pos)[1])/2;

                (*pos)[0] = 0;
                (*pos)[1] = -100;
            }
        }
    } 
    }

    
}

void getExtremeLines(Mat *sudoku){
    Vec2f topEdge = Vec2f(1000, 1000);
    double topYIntercept = 10000, topXIntercept=0;
    Vec2f bottomEdge = Vec2f(-1000, -1000); 
    double bottomYIntercept = 0, bottomXIntercept = 0;
    Vec2f leftEdge = Vec2f(1000, 1000);
    double leftXIntercept = 10000, leftYIntercept = 0;

    for(int i = 0; i < lines.size(); ++i) {
        Vec2f current = lines[i];
        float p = current[0];
        float theta = current[1];
        if(p == 0 && theta == 100 ) {
            continue;
        }
        double xIntercept, yIntercept;
        xIntercept = p / cos(theta);
        yIntercept = p / (cos(theta)*sin(theta));

        if(theta>CV_PI * 80/100 && theta<CV_PI * 100/180){
            if(p < topEdge[0])
                topEdge = current;
            if(p > bottomEdge[0])
                bottomEdge = current;
        }
        else if(theta < CV_PI*10/100 || theta > CV_PI * 170/100){
            if(xIntercept > rightXIntercept){
                rightEdge = current;
                rightXIntercept = xIntercept;
            } else if (xIntercept <= leftXIntercept) {
                leftEdge = current;
                leftXIntercept = xIntercept;
            }
        }
    }
    drawLine(topEdge, *sudoku, CV_RGB(0,0,0));
    drawLine(bottomEdge, *sudoku, CV_RGB(0,0,0));
    drawLine(leftEdge, *sudoku, CV_RGB(0,0,0));
    drawLine(rightEdge, *sudoku, CV_RGB(0,0,0));
    
    //Calculate the intersections of the points

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

    mergeRelatedLines(&lines, sudoku);
    waitKey(0);
    return 0;
}
