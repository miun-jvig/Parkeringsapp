#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

void getContours(cv::Mat imgDil, cv::Mat img)
{
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(imgDil,contours,hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());
    cv::Rect U1 = cv::Rect(281, 180, 120, 150);
    //cv::rectangle(img, U1, cv::Scalar(0, 0, 255), 2); 
    // draw lower 
    //cv::rectangle(img, cv::Point(150,350), cv::Point(280, 200), cv::Scalar(0, 0, 255), 2);
    /*cv::rectangle(img, cv::Point(281,350), cv::Point(401, 200), cv::Scalar(0, 0, 255), 2);
    cv::rectangle(img, cv::Point(402,350), cv::Point(522, 200), cv::Scalar(0, 0, 255), 2);
    //draw upper
    cv::rectangle(img, cv::Point(150,190), cv::Point(280, 40), cv::Scalar(0, 0, 255), 2);
    cv::rectangle(img, cv::Point(281,190), cv::Point(401, 40), cv::Scalar(0, 0, 255), 2);
    cv::rectangle(img, cv::Point(402,190), cv::Point(522, 40), cv::Scalar(0, 0, 255), 2);    */ 

    for(int i = 0; i < contours.size(); i++)
    {
        int area = cv::contourArea(contours[i]);     
        std::string objectType;

        // mask to check area change
        cv::Mat roi(img, U1);
        std::cout << mean(roi)[0] << '\n';

        if(mean(roi)[0] < 35){
            cv::rectangle(img, U1, cv::Scalar(0, 255, 0), 2);
        }
        else{
            cv::rectangle(img, U1, cv::Scalar(0, 0, 255), 2);
        }

        if(area > 500)
        {
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i],0.02*peri,true);
            boundRect[i] = cv::boundingRect(conPoly[i]);
            
            int objCor = static_cast<int>(conPoly[i].size());
            if(objCor == 4)
            {
                float aspRatio = static_cast<float>(boundRect[i].width) / static_cast<float>(boundRect[i].height);
                if(aspRatio > 0.85 && aspRatio < 1.15)
                {
                    objectType = "Most likely a car.";
                }

                //cv::drawContours(img, conPoly, i, cv::Scalar(255,0,255),2);
                //cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0, 255, 0), 5);
                cv::putText(img, objectType, {boundRect[i].x, boundRect[i].y-5},cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255,0,255),1);
            }
        }
    }
}

int main()
{
    int deviceID = 0;
    int apiID = cv::CAP_V4L2;

    cv::VideoCapture video_Capture(deviceID, apiID);
    std::cout << "Loading connected camera..." << '\n';
    video_Capture.open(deviceID, apiID);
    cv::waitKey(500);

    if(!video_Capture.isOpened()){
        std::cout << "Could not open camera." << '\n';
        return -1;
    }

    const unsigned long int total_frames = video_Capture.get(cv::CAP_PROP_FRAME_COUNT);
    cv::Size videoSize = cv::Size((int)video_Capture.get(cv::CAP_PROP_FRAME_WIDTH), (int)video_Capture.get(cv::CAP_PROP_FRAME_HEIGHT));
    
    cv::Mat frame, frame_blur, frame_gray, frame_canny, frame_dil, frame_out, roi;
    cv:: Scalar delta, color;
    char c;
    std::ostringstream oss;
    cv::Size blur_kernel = cv::Size(5,5);
    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);

    while(video_Capture.isOpened()){
        video_Capture.read(frame);
        if(frame.empty()){
            std::cout << "Error reading frame." << '\n';
            return -1;
        }
        double video_pos_msec = video_Capture.get(cv::CAP_PROP_POS_MSEC);
        double video_pos_frame = video_Capture.get(cv::CAP_PROP_POS_FRAMES);

        frame_out = frame.clone();
        cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(frame_gray, frame_blur, blur_kernel, 3, 3);
        cv::Canny(frame_blur, frame_canny, 25, 75);
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::dilate(frame_canny, frame_dil, kernel);

        getContours(frame_dil, frame);

        cv::imshow("test", frame_dil);
        cv::imshow("vanlig", frame);
        cv::waitKey(1);

        oss.str("");
        oss << (unsigned long int)video_pos_frame << "/" << total_frames;
    }

    return 0;
}