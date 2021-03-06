#author: plapacz6@gmail.com date: 2022-06-15 ver.0.1.0

INCLUDE_DIR=/usr/local/include/opencv4/

LIB_DIR=/usr/local/lib/
#c++1z -> c++17
CXXC=g++ -std=c++1z 
CC=gcc
CFLAGS= -Wall -g 
LFLAGS= 
LIBS_0=-lopencv_calib3d \
-lopencv_core \
-lopencv_dnn \
-lopencv_features2d \
-lopencv_flann \
-lopencv_gapi \
-lopencv_highgui \
-lopencv_imgcodecs \
-lopencv_imgproc \
-lopencv_ml \
-lopencv_objdetect \
-lopencv_photo \
-lopencv_stitching \
-lopencv_videoio \
-lopencv_video \
-ldl
	
create_chessboard: create_chessboard.cc
	g++ -g --std=c++1z $< -I$(INCLUDE_DIR) -L$(LIB_DIR) `pkg-config --libs opencv` -o $@

.PHONY: clean

clean:
	- rm *.o	
	for i in `ls *.cpp`; do printf "deleting: %s \n" $${i%.cpp}; rm $${i%.cpp}; done;
	for i in `ls *.cc`; do printf "deleting: %s \n" $${i%.cc}; rm $${i%.cc}; done;
	for i in `ls *.cxx`; do printf "deleting: %s \n" $${i%.cxx}; rm $${i%.cxx}; done;
	for i in `ls *.c`; do printf "deleting: %s \n" $${i%.c}; rm $${i%.c}; done;
  
