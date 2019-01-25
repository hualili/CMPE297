#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
using namespace cv;
using namespace std;
 
int main(  )
{
/*
    Mat drawing1 = Mat::zeros( Size(400,200), CV_8UC1 );
    Mat drawing2 = Mat::zeros( Size(400,200), CV_8UC1 );

    drawing1(Range(0,drawing1.rows),Range(0,drawing1.cols/2))=255; imshow("drawing1",drawing1);
    drawing2(Range(100,150),Range(150,350))=255; imshow("drawing2",drawing2);
*/ 
 
    Mat src1, src2, dst;
    cout<<" Bitwise Operations "<<endl; 
 
    src1 = imread("1image.jpg");
    src2 = imread("2image.jpg");

    namedWindow("AND", CV_WINDOW_NORMAL); 
    namedWindow("OR",  CV_WINDOW_NORMAL); 
    namedWindow("XOR", CV_WINDOW_NORMAL); 
    namedWindow("NOT", CV_WINDOW_NORMAL); 

    Mat res;
    bitwise_and(src1,src2,res);     imshow("AND",res);
    bitwise_or(src1,src2,res);      imshow("OR",res);
    bitwise_xor(src1,src2,res);     imshow("XOR",res);
    bitwise_not(src1,res);          imshow("NOT",res);
 
    waitKey(0);
    return(0);
}
