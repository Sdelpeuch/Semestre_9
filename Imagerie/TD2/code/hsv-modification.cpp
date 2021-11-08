#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       5
#define ENDING      ".png"

using namespace cv;
using namespace std;

// This function load an image and return it as a Mat
Mat loadImage(const char *imsname){
    Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
    if(ims.empty()){
        cout << ERROR << "Image " << imsname << " not found" << endl;
        exit(EXIT_FAILURE);
    }
    return ims;
}

// This function convert a Mat in a HSV image
Mat convertToHSV(Mat ims){
    Mat imsHSV;
    cvtColor(ims, imsHSV, CV_BGR2HSV);
    return imsHSV;
}

// This function change HSV chanels width parameters h, s and v
Mat changeHSV(Mat ims, int h, int s, int v){
    for(int i = 0; i < ims.rows; i++){
        for(int j = 0; j < ims.cols; j++){
            ims.at<Vec3b>(i, j)[0] = ims.at<Vec3b>(i, j)[0] + h;
            ims.at<Vec3b>(i, j)[1] = ims.at<Vec3b>(i, j)[1] + s;
            ims.at<Vec3b>(i, j)[2] = ims.at<Vec3b>(i, j)[2] + v;
        }
    }
    return ims;
}

// This function save an image on imd name
void saveImage(Mat ims, const char *imd){
    imwrite(imd, ims);
}

// This function display an image
void displayImage(Mat ims){
    imshow("HSV modification", ims);
    waitKey(0);
}


void process(int h, int s, int v, const char *imsname, const char *imdname) {
    Mat ims = loadImage(imsname);
    Mat imsHSV = convertToHSV(ims);
    displayImage(imsHSV);
    Mat imsHSVModified = changeHSV(imsHSV, h, s, v);
    saveImage(imsHSVModified, imdname);
    displayImage(imsHSVModified);
}

void usage(const char *s) {
    std::cerr << ERROR << "Usage: " << s << " h s v ims imd\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5]);
    return EXIT_SUCCESS;
}
