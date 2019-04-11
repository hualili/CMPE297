/*------------------------------------------------------*
 * CTI One Corporation                                  *
 * Code: focal_Color_projection.cpp                     *
 * Coded by:  Minh Duc Ong                              *
 * Architechted by: Dr. Harry Li 			*
 * Date: Apr 10 2019;                                   *
 * Version: x0.1;                                       *
 * Status : Debug;                                      *
 * Purpose: 1. Use OpenCV, AR,                          *
 *          2. Project focal infor on X axis            *
 *          3. Map color to the 3D image                *
 * Note: for SJSU CMPE 297 educational use, not for     * 
 *       commercial applications.                       * 
 *------------------------------------------------------*/

/*---------------------------------------------------------------------*
 * To compile:                                                         *
 *      cmake .                                                        *
 *      make                                                           *
 * To run the program:                                                 *
 *      ./focal_Color_projection image_BGR_2.png image_focal_2.png     *
 * Enter the eye of view:                                              *
 *       100 0 0                                                       *
 * Zoom in image a little bit by scroll wheel of the mouse             *
 * Use drag and drop to locate to the image                            *
 * --------------------------------------------------------------------*/

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/viz.hpp>
#include <string>
#include <cmath> 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace cv;
#define UpperBD 1900000
#define PI      3.1415926
#define Num_pts 10


float Xe = 200.0f;
float Ye = 200.0f;
float Ze = 200.0f;
float Rho = sqrt(pow(Xe,2) + pow(Ye,2) + pow(Ze,2));
float D_focal = 20.0f;

int pi_near = 80;

typedef struct {
    std::vector <float> X=std::vector <float> (UpperBD);
    std::vector <float> Y=std::vector <float> (UpperBD);
    std::vector <float> Z=std::vector <float> (UpperBD);
} pworld;

typedef struct {
    std::vector <float> X=std::vector <float> (UpperBD);
    std::vector <float> Y=std::vector <float> (UpperBD);
    std::vector <float> Z=std::vector <float> (UpperBD);
} pviewer;

typedef struct {
    std::vector <float> B=std::vector <float> (UpperBD);
    std::vector <float> G=std::vector <float> (UpperBD);
    std::vector <float> R=std::vector <float> (UpperBD);
} colorBGR;

typedef struct{
    std::vector <float> X=std::vector <float> (UpperBD);
    std::vector <float> Y=std::vector <float> (UpperBD);
} pperspective;

typedef struct{
    std::vector <float> X=std::vector <float> (UpperBD);
    std::vector <float> Y=std::vector <float> (UpperBD);
} letter;

typedef union {
    int i;
    float f;
} ftoi_bits;

struct {
    float X;
    float Y;
    float Z;
} Points;

void mydisplay(cv::Mat frame,long focal, cv::Mat image_BGR, cv::Mat image_Gray);
void linear_func(float x1, float y1, float x2, float y2, float x3);

int main(int argc, char **argv) {
    cv::Mat image_BGR;
    cv::Mat image_Gray;
//Read 2 images
    image_BGR = imread(argv[1], cv::IMREAD_COLOR);
    image_Gray = imread(argv[2], cv::IMREAD_COLOR);
//Read eye position　
    std::cout << "please input the eyes position(Xe, Ye, Ze): " <<endl;
    std::cin >> Xe >> Ye >> Ze;

    cv::Mat frame (2700, 2700, CV_8UC3, Scalar(0,0,0));

#define d_focal 1000
//run projection plane function
    mydisplay(frame, d_focal, image_BGR, image_Gray);

    return 0;
}

void mydisplay(cv:: Mat frame, long focal, cv::Mat image_BGR, cv::Mat image_Gray)
{
    pworld  world;
    pviewer viewer;
    pperspective perspective;
    letter letterL;
    letter Point;
    letter arrow;
    D_focal = float (focal);
    colorBGR color_PC;
    Mat frame_tmp=frame.clone();

    int ep =4;
    //Load B G R and focal information
    for (int j=0; j< image_BGR.rows; j++){
        for (int i=0; i< image_BGR.cols; i++){
#define ScaleFac_x 0.5
#define ScalFac_z 0.28
#define ScalFac_y 0.16
              world.X[4 + i+j*image_BGR.cols] = 
                               (255-image_Gray.at<cv::Vec3b>(cv::Point(i, j))[0])*ScaleFac_x;
              world.Y[4 + i+j*image_BGR.cols] = i*ScalFac_y;
              world.Z[4 + i+j*image_BGR.cols] = (image_BGR.cols-j)*ScalFac_z;
              color_PC.B[4 + i+j*image_BGR.cols]=image_BGR.at<cv::Vec3b>(cv::Point(i, j))[0];
              color_PC.G[4 + i+j*image_BGR.cols]=image_BGR.at<cv::Vec3b>(cv::Point(i, j))[1];
              color_PC.R[4 + i+j*image_BGR.cols]=image_BGR.at<cv::Vec3b>(cv::Point(i, j))[2];
        }
    }

    world.X[0] = 0.0;    world.Y[0] =  0.0;   world.Z[0] =  0.0;    // origin
    world.X[1] = 150.0;  world.Y[1] =  0.0;   world.Z[1] =  0.0;    // x-axis
    world.X[2] = 0.0;    world.Y[2] =  150.0;  world.Z[2] =  0.0;    // y-axis
    world.X[3] = 0.0;    world.Y[3] =  0.0;   world.Z[3] =  150.0;	// z-axis

modify_e:
    frame = frame_tmp.clone();
    //fine angles of world to view
    float sPheta = Ye / sqrt(pow(Xe,2) + pow(Ye,2));
    float cPheta = Xe / sqrt(pow(Xe,2) + pow(Ye,2));
    float sPhi = sqrt(pow(Xe,2) + pow(Ye,2)) / Rho;
    float cPhi = Ze / Rho;

    float xMin = 1000.0, xMax = -1000.0;
    float yMin = 1000.0, yMax = -1000.0;

    //world to view
    for(unsigned long i = 0; i <=world.X.size(); i++)
    {
        viewer.X[i] = -sPheta * world.X[i] + cPheta * world.Y[i];
        viewer.Y[i] = -cPheta * cPhi * world.X[i]
                - cPhi * sPheta * world.Y[i]
                + sPhi * world.Z[i];
        viewer.Z[i] = -sPhi * cPheta * world.X[i]
                - sPhi * cPheta * world.Y[i]
                -cPheta * world.Z[i] + Rho;
    }

    //Perspective Projection: Convert all world points to Projection Plane
    for(unsigned long i = 0; i <= world.X.size(); i++)
    {
        perspective.X[i] = D_focal * viewer.X[i] / viewer.Z[i] + frame.cols/2-300;
        perspective.Y[i] = -(D_focal * viewer.Y[i] / viewer.Z[i]) + frame.rows/2-300;
        if (perspective.X[i] > xMax) xMax = perspective.X[i];
        if (perspective.X[i] < xMin) xMin = perspective.X[i];
        if (perspective.Y[i] > yMax) yMax = perspective.Y[i];
        if (perspective.Y[i] < yMin) yMin = perspective.Y[i];
    }
#define color 200
    //Point Cloud data drawing
    for (unsigned long index =4 ; index<world.X.size(); index ++)
    {
        frame.at<cv::Vec3b>(cv::Point(perspective.X[index],
                                      perspective.Y[index]))[0] = color_PC.B[index];
        frame.at<cv::Vec3b>(cv::Point(perspective.X[index],
                                      perspective.Y[index]))[1] = color_PC.G[index];
        frame.at<cv::Vec3b>(cv::Point(perspective.X[index],
                                      perspective.Y[index]))[2] = color_PC.R[index];
    }

    //To draw World XYZ coodinate
    cv::line(frame, cv::Point (perspective.X[0],perspective.Y[0]),
            cv::Point (perspective.X[1],perspective.Y[1]),
            cv::Scalar(0, 0, 255), 1, 8);//X red
    cv::line(frame, cv::Point (perspective.X[0],perspective.Y[0]),
            cv::Point (perspective.X[2],perspective.Y[2]),
            cv::Scalar(0, 255, 0), 1, 8);//Y green
    cv::line(frame, cv::Point (perspective.X[0],perspective.Y[0]),
            cv::Point (perspective.X[3],perspective.Y[3]),
            cv::Scalar(255, 0, 0), 1, 8);//Z blue
    cv::namedWindow("Image", cv::WINDOW_NORMAL);
    //cv::resizeWindow("Image", frame.cols, frame.rows);

    //get button events to modify position of eye
    while(true){
        cv::imshow("Image", frame);
        int key= cv::waitKey(10);
        if (key == 119)
            {
                cout <<"up" <<endl; // up
                Ze=Ze+5;
                goto modify_e;
             }
        if (key == 115)
            {
                cout <<"down" <<endl;   // down
                Ze=Ze-5;
                goto modify_e;
            }

        if (key == 97)
            {
                cout <<"left" <<endl;   //  left
                Ye=Ye-5;
                goto modify_e;
            }
        if (key == 100)
            {
                cout <<"right" <<endl;
                Ye=Ye+5;
                goto modify_e;
            }
        if (key == 120)
            {
                cout <<"zoom in" <<endl;
                Xe=Xe+2;
                Ye=Ye+2;
                goto modify_e;
            }
        if (key == 122)
            {
                cout <<"zoom out" <<endl;
                Xe=Xe-2;
                Ye=Ye-2;
                goto modify_e;
            }
    }
}


