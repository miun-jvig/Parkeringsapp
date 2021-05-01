#ifndef PARKING
#define PARKING

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "functions.h"

class Parking{  
public:
    std::string alias;
    bool occupied;
    cv::Rect spot;
    cv::Mat roi;

    void occupied_Spot(std::string alias, cv::Mat frame, cv::Mat frame_dil, cv::Rect spot, std::map<std::string, bool>& parkingSpots);
    void setStatus(bool status) noexcept;
    bool getStatus() noexcept;    
};

#endif