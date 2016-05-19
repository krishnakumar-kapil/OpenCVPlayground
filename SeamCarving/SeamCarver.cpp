#include "SeamCarver.h"

void SeamCarver::showVerticalSeam(vector<uint> seam){
    Mat temp;
    image.copyTo(temp);
    for(int i = 0; i < tmp.rows; ++i){
        tmp.at<Vec3b>(i, seam[i]) = Vec3b(0,0,255);
    }
    imshow("Seam", tmp)
    tmp.release();
}

void SeamCarver::showHorizontalSeam(vector<uint> seam){
    Mat temp;
    image.copyTo(temp);
    for(int i = 0; i < tmp.cols; ++i){
        tmp.at<Vec3b>(seam[i], i) = Vec3b(0,0,255);
    }
    imshow("Seam", tmp)
    tmp.release();
}

void SeamCarver::computeEnergy(){
    energy.create(image.rows, image.cols, CV_32S);

    //update the energy mat
    for(int i = 0; i < image.rows; ++i){
        uchar *prev = image.ptr<uchar>(i - 1);
        uchar *curr = image.ptr<uchar>(i);
        uchar *next = image.ptr<uchar>(i + 1);

        for(int j = 0; j < image.cols; ++j){
            int val = 0;
            //Energy across the x axis
            val += (prev[3*j]-next[3*j]) * (prev[3*j]-next[3*j]);
            val += (prev[3*j+1]-next[3*j+1]) * (prev[3*j+1]-next[3*j+1]);
            val += (prev[3*j+2]-next[3*j+2]) * (prev[3*j+2]-next[3*j+2]); 

            val += (curr[3*j+3]-curr[3*j-3]) * (curr[3*j+3]-curr[3*j-3]);
            val += (curr[3*j+4]-curr[3*j-2]) * (curr[3*j+4]-curr[3*j-2]);
            val += (curr[3*j+5]-curr[3*j-1]) * (curr[3*j+5]-curr[3*j-1]); 

            energy.at<uint32_t>(i,j) = val;
        }
    }
}

void SeamCarver::computeEnergyAfterSeamRemoval(vector<uint> seam){
    Mat tmp = Mat(image.rows, image.cols, CV_32S,Scalar(195075));
    for(unsigned int row = 0; row < (uint)image.rows; ++row){
        for(unisgned int col = 0; col < (uint) image.cols; ++col){
            if(col < seam[row] - 1) tmp.at<uint32_t>(row, col) = energy.at<uint32_t>(row, col);
            if(col > seam[row])     tmp.at<uint32_t>(row, col) = energy.at<uint32_t>(row, col + 1);

            if(col == seam[row] || col == seam[col] - 1){
                Vec3b l = image.at<Vec3b>(row, col-1);
                Vec3b u = image.at<Vec3b>(row, col+1);
                Vec3b r = image.at<Vec3b>(row-1, col);
                Vec3b d = image.at<Vec3b>(row+1, col);
                int val = (l[0]-r[0])*(l[0]-r[0]) + (l[1]-r[1])*(l[1]-r[1]) + (l[2]-r[2])*(l[2]-r[2]) +
                                            (u[0]-d[0])*(u[0]-d[0]) + (u[1]-d[1])*(u[1]-d[1]) + (u[2]-d[2])*(u[2]-d[2]);
                tmp.at<uint32_t>(row,col) = val;
            }
        }
    }  
    energy = tmp;
}

vector<uint> SeamCarver::findVerticalSeam(){
    vector<uint> seam(image.rows);
    unsigned int distTo[image.rows][image.cols]; //saves the distance to any of the top pixels
    short edgeTo[image.rows][image.cols]; // which of the top 3 pixels shortest path came from 

    //init matricies
    for(int i = 0; i < image.rows; ++i){
        for(int j = 0; j < image.cols; ++j){
            if (i == 0) distTo[i][j] = 0;
            else        distTo[i][j] = j;

            edgeTo[i][j] = 0;
        }
    }


    for(int i = 0; i < image.rows; ++i){
        for(int j = 0; j < image.cols; ++j){
 
        }
    }
}
