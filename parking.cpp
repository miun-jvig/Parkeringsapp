#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "parking.h"
#include "functions.h"

/*
* constructor/destructor/copyconstructor for future
*
Parking::Parking(){ }
Parking::~Parking(){ }
Parking::Parking(const Parking& src) { }
}*/

void Parking::setStatus(bool status) noexcept {
    occupied = status;
}

bool Parking::getStatus() noexcept {
    return occupied;
}

void Parking::occupied_Spot(std::string alias, cv::Mat frame, cv::Mat frame_dil, cv::Rect spot, std::map<std::string, bool>& parkingSpots){
    cv::Mat roi(frame_dil, spot);
    int whitePixels = cv::countNonZero(roi);

    /*
    * Counts the amount of black pixels on the screen, if whitepixels are above a certain treshhold (0.1 * spot.width & spot.height in this case),
    * then a car is parked in the spot.
    */
    if(whitePixels > (0.1 * spot.width * spot.height)){
        cv::rectangle(frame, spot, cv::Scalar(0, 0, 255), 2); //red
        Parking::setStatus(true);
        parkingSpots[alias] = Parking::getStatus();
    }
    else{
        cv::rectangle(frame, spot, cv::Scalar(0, 255, 0), 2); //green
        Parking::setStatus(false);
        parkingSpots[alias] = Parking::getStatus();
    }
}