# -- detectParking --

A repository containing C++ code for a basic parking detector. The parking detector is run on a Raspberry Pi with a Raspberry Pi camera connected.

Currently being built for a school-project.

**Installation OpenCV on Raspberry Pi**:

OpenCV was installed with the guide https://linuxize.com/post/how-to-install-opencv-on-raspberry-pi/. 

**Parameters**
If camera is not working, try changing

_int apiID = cv::CAP_V4L2;_

to

_int apiID = cv::CAP_ANY; _
