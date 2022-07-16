/*
author: plapacz6@gmail.com
date: 2022-07-15
ver.0.1.0
*/
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;


void pasteMat2Mat(const Mat &src, const Rect &roi, Mat& dst){
  
  for(int rowS = 0, rowD = roi.y; rowD < roi.y + roi.height; ++rowS, ++rowD){
    for(int colS = 0, colD = roi.x; colD < roi.x + roi.width; ++colS, ++colD){      
      dst.at<Vec3b>(rowD,colD) = src.at<Vec3b>(rowS,colS);            
    }
  }
}


/** 
 * @brief generate quasi chessboard
 * 
 * @param img - image being being base of chessboard background
 */
void printCheesboard(const Mat& img_org){

  Mat img = img_org.clone();
  resize(img, img, Size(512,512), INTER_LINEAR);
  Mat background = img.clone();  
  background += Scalar(-100, -100, -100);
  Mat chessboard = Mat::zeros(img.size(), img.type());
    
  //cutting image to the tiles  
  
  const int parts_amount = 4;
  int field_width = img.cols / parts_amount;
  int field_height = img.rows / parts_amount;

  struct {
    Mat t;   //t - tile
    Rect r;
  } field16[parts_amount][parts_amount];

  for(int row = 0; row < parts_amount; ++row){
    for(int col = 0; col < parts_amount; ++col){      
      field16[row][col].r = Rect(col * field_width, row * field_height, field_width, field_height);               
      field16[row][col].t = Mat(img,
        field16[row][col].r
      );            
    }
  }

  pasteMat2Mat(
    background, 
    Rect(0,0,img.rows, img.cols), 
    chessboard);  
    
  for(int row = 0; row < parts_amount; row++){
    for(int col = (row%2) ? 0 : 1; col < parts_amount; col+=2){
      pasteMat2Mat(
        field16[row][col].t, 
        field16[row][col].r,        
        chessboard);
  
    }
  }
  cout << endl << "... click on the chessboard image, and press any key" << endl;
  imshow("chessboard", chessboard);
  waitKey(0);
}

int main(int argc, char **argv){
  CommandLineParser cmd_parser(argc, argv,\
  "\
  {help --help -h || this message}\
  {@img | sample_img.png | base image}\
  ");
  if(cmd_parser.has("help")){
    cmd_parser.printMessage();
    return EXIT_SUCCESS;
  }
  try{
    Mat img = imread(cmd_parser.get<string>("@img"), IMREAD_UNCHANGED);
    if(img.empty()){
      cerr << endl << "can't open image" << endl;
      //return EXIT_FAILURE;
    }    
    printCheesboard(img);
  }
  catch(...){
    cmd_parser.printMessage();
  }
  return EXIT_SUCCESS;
}


