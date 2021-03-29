#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include "detect.h"

int main()
{
    int deviceID = 0;
    int apiID = cv::CAP_V4L2;

    cv::VideoCapture video_Capture(deviceID, apiID);
    std::cout << "Loading connected camera..." << '\n';
    video_Capture.open(deviceID, apiID);
    cv::waitKey(300);

    //start picture
    cv::Mat starterState;
    video_Capture.read(starterState);

    if(!video_Capture.isOpened()){
        std::cout << "Could not open camera." << '\n';
        return -1;
    }
    
    cv::Mat frame, frame_blur, frame_gray, frame_canny, frame_dil, outputMat, maskMat;
    cv::Size blur_kernel = cv::Size(5,5);

    while(video_Capture.isOpened()){
        video_Capture.read(frame);
        if(frame.empty()){
            std::cout << "Error reading frame." << '\n';
            return -1;
        }
        cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(frame_gray, frame_blur, blur_kernel, 3, 3);
        cv::Canny(frame_blur, frame_canny, 25, 75);
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::dilate(frame_canny, frame_dil, kernel);

        std::map<std::string, int> parkingSpots = detect(frame_dil, frame, starterState);

        std::map<std::string, int>::iterator iter;
        for(iter = parkingSpots.begin(); iter != parkingSpots.end(); iter++){
            std::cout << iter->first << " = " << iter->second << '\n';
            std::cout << iter->first << " = " << iter->second << '\n';
            std::cout << iter->first << " = " << iter->second << '\n';
        }
        parkingSpots.clear();

        cv::imshow("test", frame_dil);
        cv::imshow("vanlig", frame);
        cv::waitKey(1);
    }

    return 0;
}
