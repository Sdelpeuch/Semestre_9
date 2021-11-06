#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// This function create a new image with convert function and -resize function
void process(const char* imsname){
    Mat src = imread(imsname, CV_LOAD_IMAGE_COLOR);
    Mat dst;
    cvtColor(src, dst, CV_BGR2GRAY);
    resize(dst, dst, Size(src.cols/2, src.rows/2));
    imwrite("pixels-loops.png", dst);
}

void 
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
  exit(EXIT_FAILURE);
}

#define param 1
int 
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(NULL);
  return EXIT_SUCCESS;  
}
