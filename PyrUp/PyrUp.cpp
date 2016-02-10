#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

using namespace cv;


const String window_name = "Picture";

int main(void  )
{
    Mat src, dst;

    printf( "\n Zoom In-Out demo  \n " );
    printf( "------------------ \n" );
    printf( " * [u] -> Zoom in  \n" );
    printf( " * [d] -> Zoom out \n" );
    printf( " * [ESC] -> Close program \n \n" );

    // Test image - Make sure it s divisible by 2^{n}
    src = imread( "../Pictures/landscape.jpg" );
    if( src.empty() ){ 
        printf(" No data! -- Exiting the program \n");
        return -1; 
    }

        if( src.cols % 2 == 1 ||  ){ 
        printf(" No data! -- Exiting the program \n");
        return -1; 
    }

    namedWindow( window_name, WINDOW_AUTOSIZE );
    imshow( window_name, src );

            pyrUp(src , dst, Size(src.cols/2, src.rows/2));
            printf( "** Zoom In: Image x 2 \n" );

      imshow( window_name, dst );

      waitKey(0);
    return 0;
}
