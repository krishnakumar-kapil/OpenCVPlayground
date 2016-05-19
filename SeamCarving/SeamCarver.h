
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

class SeamCarver {
    Mat image;
    Mat duplicate;
    Mat energy;

    void computeEnergy();
    void computeEnergyAfterSeamRemoval(vector<uint> seam);

public: 
    SeamCarver(Mat im){
        image = im;
        duplicate = im;
        // Set the values to that value
        energy = Mat(image.rows, image.cols, Scalar(195075));
        computeEnergy();
    }

    virtual ~SeamCarver(){
        duplicate.release();
        energy.release();
    }

    void showEnergy(){
        imshow(energy);
    }

    Mat getImage(){
        return image;
    }

    unsigned int getEnergy(unsigned int row, unsigned int col){
        return energy.at<uint32_t>(row, col);
    }

    vector<int> findVerticalSeam();
    vector<int> findHorizontalSeam();
    
    void removeHorizontalSeam();
    void removeVerticalSeam();

    void showHorizontalSeam(vector<uint> seam);
    void showVerticalSeam(vector<uint> seam);
}
