#ifndef DETECTX
#define DETECTX

#include <vector>
#include <map>
#include <utility>
#include <opencv2/opencv.hpp>

std::map<std::string, int> detect(cv::Mat, cv::Mat, cv::Mat);

#endif