#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <map>
#include <iostream>
#include "parking.h"
#include "functions.h"

void detect(cv::Mat frame, cv::Mat frame_dil, std::map<std::string, bool>& parkingSpots)
{
    std::map<std::string, bool> takenSpots;
    Parking park1, park2, park3, park4;

    // for now spots are made manually via x- and y-coordinates
    park1.spot = cv::Rect(150, 180, 100, 120);
    park2.spot = cv::Rect(252, 180, 100, 120);
    park3.spot = cv::Rect(354, 180, 100, 120);
    park4.spot = cv::Rect(456, 180, 100, 120);

    /*
    * occupied_Spot counts the amount of black pixels on the screen, if whitepixels are above a certain treshhold,
    * then a car is parked in the spot. 
    */
    park1.occupied_Spot("Spot1", frame, frame_dil, park1.spot, parkingSpots);
    park2.occupied_Spot("Spot2", frame, frame_dil, park2.spot, parkingSpots);
    park3.occupied_Spot("Spot3", frame, frame_dil, park3.spot, parkingSpots);
    park4.occupied_Spot("Spot4", frame, frame_dil, park4.spot, parkingSpots);
}

cv::Mat getDil(cv::Mat frame){
    cv::Mat frame_gray, frame_blur, frame_canny, frame_dil;
    cv::Size blur_kernel = cv::Size(5,5);

    cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(frame_gray, frame_blur, blur_kernel, 3, 3);
    cv::Canny(frame_blur, frame_canny, 50, 75);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::dilate(frame_canny, frame_dil, kernel);

    return frame_dil;
}