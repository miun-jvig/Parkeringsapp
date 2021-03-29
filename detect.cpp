#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include "detect.h"

std::map<std::string, int> detect(cv::Mat imgDil, cv::Mat img, cv::Mat starterState)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    std::vector<cv::Rect> boundRect(contours.size());
    std::map<std::string, int> takenSpots;
    cv::Rect U1 = cv::Rect(150, 180, 120, 150);
    cv::Rect U2 = cv::Rect(272, 180, 120, 150);
    cv::Rect U3 = cv::Rect(394, 180, 120, 150);

    cv::findContours(imgDil,contours,hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    cv::Mat roiStarter1(starterState, U1);
    cv::Mat roiStarter2(starterState, U2);
    cv::Mat roiStarter3(starterState, U3);

    for(int i = 0; i < contours.size(); i++)
    {
        int area = cv::contourArea(contours[i]);     
        std::string objectType;

        cv::Mat roi1(img, U1);
        cv::Mat roi2(img, U2);
        cv::Mat roi3(img, U3);
        
        // ROI1
        if(mean(roi1)[0] < mean(roiStarter1)[0]){
            cv::rectangle(img, U1, cv::Scalar(0, 0, 255), 2);
            takenSpots.insert(std::pair<std::string, int>("Spot 1", 1));
        }
        else{
            cv::rectangle(img, U1, cv::Scalar(0, 255, 0), 2);
            takenSpots.insert(std::pair<std::string, int>("Spot 1", 0));
        }
        // ROI2
        if(mean(roi2)[0] < mean(roiStarter2)[0]){
            cv::rectangle(img, U2, cv::Scalar(0, 0, 255), 2);
            takenSpots.insert(std::pair<std::string, int>("Spot 2", 1));
        }
        else{
            cv::rectangle(img, U2, cv::Scalar(0, 255, 0), 2);
            takenSpots.insert(std::pair<std::string, int>("Spot 2", 0));
        }
        // ROI3
        if(mean(roi3)[0] < mean(roiStarter3)[0]){
            cv::rectangle(img, U3, cv::Scalar(0, 0, 255), 2);
            takenSpots.insert(std::pair<std::string, int>("Spot 3", 1));
        }
        else{
            cv::rectangle(img, U3, cv::Scalar(0, 255, 0), 2);
            takenSpots.insert(std::make_pair("Spot 3", 0));
        }
    }
    
    return takenSpots;
}