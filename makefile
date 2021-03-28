CPPFLAGS=-g -Wall -I. -DDEBUG
LDFLAGS=-g
LDLIBS=-lopencv_core -lopencv_calib3d -lopencv_highgui -lopencv_imgproc -lopencv_stitching -lopencv_video
LIBRARIES += opencv_core opencv_highgui opencv_imgproc opencv_videoio

exeMain: FreePark.cpp
	g++ $(LDFLAGS) FreePark.cpp -o exeMain -I/usr/local/include/opencv4 -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio -lopencv_highgui -lopencv_objdetect $(LDLIBS)

run: exeMain
	./exeMain

clean:
	rm exeMain
