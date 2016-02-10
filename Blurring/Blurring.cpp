#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;


int MAX_KERNEL_LENGTH = 31;

int main(int argc, char** argv){
	if ( argc != 2 )
	{
	    printf("usage: Blurring.out <Image_Path>\n");
	    return -1;
	}

	Mat image, blurredImage;
    image = imread( argv[1], 1 );

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    blurredImage = image.clone();

    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 ){ 
		   GaussianBlur( image, blurredImage, Size(i,i) , 3, 3 );
      // }



    namedWindow("Blurred Image", WINDOW_AUTOSIZE );
    imshow("Blurred Image", blurredImage);

    waitKey(0);

    return 0;
}
