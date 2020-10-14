#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap;
    
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(0)) return 0;
    
    for(;;)
    {
        Mat frame; Mat outframe;
        cap >> frame; cap >> outframe;
        if( frame.empty() ) break; // end of video stream
        
        // range warna biru gk tau berapa :D
        inRange(frame, Scalar(78,158,124), Scalar(138,255,255), outframe);
        
        imshow("ini kamera kawan!", outframe);
        
        if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
    }
    
    // the camera will be closed automatically upon exit
    // cap.close();
    
    return 0;
}