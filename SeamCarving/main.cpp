
#include "SeamCarver.h"
#include <stdio.h>
#include <cstring>
int main(int argc, char **argv){
    if(argc < 4){
        cout << "Please provide more arguments\n";
        return -1;
    }
    string title = argv[1];
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    
    if(title == "")
        return -1;
    Mat_<Vec3b> image = imread(title, CV_LOAD_IMAGE_COLOR);
//  Mat_<Vec3b> image = imread("lighthouse.jpg");
//  Mat_<Vec3b> image = imread("bench.jpg");
    if (!image.data) {
        cout << "Invalid input";
        image.release();
        return -1;
    }
    if(width > 1078 || height > 1000){
        cout << "Please use smaller pictures";
        return -1;
    }

    imshow("Original Image", image);
    SeamCarver s(image);

	for (int i = 0; i < width; ++i) {
		vector<uint> seam = s.findVerticalSeam();
//		s.showHorizontalSeam(seam);
		s.removeVerticalSeam(seam);
	}

	for (int j = 0; j < height; ++j) {
		vector<uint> seam = s.findHorizontalSeam();
//		s.showHorizontalSeam(seam);
		s.removeHorizontalSeam(seam);
	}
	imshow("Carved Image", s.getImage());
    //cout << "Press any key to continue\n";

    //`cout << "Writing out carved image to /carved/";
    //iwrite("./carved/"+title, s.getImage());
	waitKey(0);
	image.release();
    return 0;
}
