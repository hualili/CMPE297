/*------------------------------------------------------*
 * Code: videoCanny.cpp                                 *
 * Coded by:  Harry Li;                                 *
 * Date: May 8 2018;                                    *
 * Version: x0.1;                                       *
 * Status : release;                                    *
　*          production;  5/24/18                        * 
 * Purpose: 1. simple demo program for Canny edge       *
 *             detection on video input.                *       
 *------------------------------------------------------*/ 
#include <iostream>   
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    bool playVideo = true;
    //VideoCapture cap(argv[1]);  //command line input video file
    VideoCapture cap(0);  //input video from default video cam 
    if(!cap.isOpened())
    {
        cout<<"Unable to open video "<<argv[1]<<"\n";
        return 0;
    }

    Mat frame;

    while(1)
    {
        if(playVideo)
            cap >> frame;
        if(frame.empty())
        {
            cout<<"Empty Frame\n";
            return 0;
        }

	Mat frame_canny;   
	Canny(frame, frame_canny, 10, 100, 3); // src, dst 
	imshow("Canny", frame_canny); 
        imshow("Video",frame);  
  
        char key = waitKey(5);     //delay 5 milliseconds 
        if(key == 'p')
            playVideo = !playVideo; 
    }
    return 0;
}
