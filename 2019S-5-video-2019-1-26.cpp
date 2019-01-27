/*------------------------------------------------------*
 * Code: video.cpp                                      *
 * Coded by:  Harry Li;                                 *
 * Date: May 8 2018;                                    *
 * Version: x0.1;                                       *
 * Status : release;                                    *
　*          production;  5/24/18                        * 
 * Purpose: 1. simple demo program for video file       *
 *             display.                                 *       
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

    Mat frame, frame_threshold, frame_hsv;
  
    namedWindow("Video", WINDOW_NORMAL);
    namedWindow("hsv", WINDOW_NORMAL); 

    while(1)
    {
        if(playVideo)
            cap >> frame;
        if(frame.empty())
        {
            cout<<"Empty Frame\n";
            return 0;
        }

        cvtColor(frame, frame_hsv, CV_BGR2HSV); 
   
        imshow("Video",frame);
        imshow("hsv", frame_hsv);  
  
        char key = waitKey(5);     //delay 5 milliseconds 
        if(key == 'p')
            playVideo = !playVideo; 
    }
    return 0;
}
