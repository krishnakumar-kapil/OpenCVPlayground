#ifndef SEAMCARVER_H_
#define SEAMCARVER_H_

#include <opencv2/opencv.hpp>
#include <stdio.h>
// #include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

class SeamCarver {
    Mat_<Vec3b>  image;
    Mat_<Vec3b>  duplicate;
    Mat  energy;

    void computeEnergy();
    void computeEnergyAfterSeamRemoval(vector<uint> seam);

public: 
    SeamCarver(Mat_<Vec3b> im) {
        image = im;
        duplicate = image;
        energy = Mat(image.rows, image.cols, CV_32S, Scalar(195075));
        computeEnergy();
    }

    virtual ~SeamCarver(){
        duplicate.release();
        energy.release();
    }

    void showEnergy(){
        imshow("ENERGY", energy);
    }

    Mat getImage(){
        return image;
    }

    unsigned int getEnergy(unsigned int row, unsigned int col){
        return energy.at<uint32_t>(row, col);
    }

    vector<uint> findVerticalSeam();
    vector<uint> findHorizontalSeam();
    
    void removeHorizontalSeam(vector<uint> seam);
    void removeVerticalSeam(vector<uint> seam);

    void showHorizontalSeam(vector<uint> seam);
    void showVerticalSeam(vector<uint> seam);
};

#endif /* SEAMCARVER_H_ */
