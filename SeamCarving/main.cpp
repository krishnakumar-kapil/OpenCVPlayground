
#include "SeamCarver.h"

int main(){
    Mat_<Vec3b> image = imread("bench.jpg");
//  Mat_<Vec3b> image = imread("lighthouse.jpg");
//  Mat_<Vec3b> image = imread("bench.jpg");
    if (!image.data) {
        cout << "Invalid input";
        image.release();
        return -1;
    }

    imshow("Original Image", image);
    SeamCarver s(image);

	for (int i = 0; i < 160; ++i) {
		vector<uint> seam = s.findVerticalSeam();
//		s.showHorizontalSeam(seam);
		s.removeVerticalSeam(seam);
	}
	imshow("Carved Image", s.getImage());
	waitKey(0);
	image.release();
    return 0;
}
