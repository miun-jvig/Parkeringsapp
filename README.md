# -- detectParking --

A repository containing C++ code for a basic parking detector using OpenCV. The parking detector is run on a Raspberry Pi with a Raspberry Pi camera connected.

Currently being built for a school-project.

**Detection**

Detection is being done by converting a frame to a dilated frame. The dilated frame will then detect how many black pixels there is in a certain range of interest. If the black pixels exceed a certain threshhold, then a car is parked in the spot.

**Installation OpenCV on Raspberry Pi**:

OpenCV was installed with the guide https://linuxize.com/post/how-to-install-opencv-on-raspberry-pi/. 

**Hardware**

- Raspberry Pi 2018
- HQ camera V1.0 2018

**Parameters**

If camera is not working, try changing

_int apiID = cv::CAP_V4L2;_

to

_int apiID = cv::CAP_ANY;_
