#ifndef DETECTX
#define DETECTX

#include <opencv2/opencv.hpp>
#include <map>
#include "parking.h"

void detect(cv::Mat frame, cv::Mat frame_dil, std::map<std::string, bool>& parkingSpots);
cv::Mat getDil(cv::Mat frame);

#endif
