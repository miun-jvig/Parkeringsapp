#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <map>
#include <iostream>
#include "functions.h"
#include "parking.h" 

int main()
{
    int deviceID = 0;
    int apiID = cv::CAP_V4L2;
    std::map<std::string, bool> parkingSpots;

    cv::VideoCapture video_Capture(deviceID, apiID);
    std::cout << "Loading connected camera..." << '\n'; 
    video_Capture.open(deviceID, apiID);
    cv::waitKey(1);

    if(!video_Capture.isOpened()){
        std::cout << "Could not open camera." << '\n';
        return -1;
    }    

    while(video_Capture.isOpened()){
        cv::Mat frame;
        video_Capture.read(frame);
        cv::Mat frame_dil = getDil(frame);
        
        detect(frame, frame_dil, parkingSpots);

        // to check taken spots
        /*std::map<std::string, bool>::iterator iter;
        for(iter = parkingSpots.begin(); iter != parkingSpots.end(); iter++){
            std::cout << iter->first << " " << iter->second << std::endl;
        }*/
        
        cv::imshow("Overview", frame);
        cv::waitKey(1);
    }

    return 0;
}
