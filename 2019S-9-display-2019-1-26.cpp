// Example for CMPE297, Coded by: HL, Jan 2019 
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
 
using namespace cv;
using namespace std;
 
int main(int argc, char** argv)
{
    
  Mat image = imread( argv[1], 1 );
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); //wait for any key press
        return -1;
    }
 
    cout<<" Demo Display Image "<<endl; 
  
    namedWindow("Display the image", CV_WINDOW_NORMAL);  

    Mat image_result;
    image_result = image; 
    imshow("Display the image", image_result); 
 
    waitKey(0);
    return(0);
}
