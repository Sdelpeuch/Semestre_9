#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       1
#define OFFSET      50

using namespace cv;
using namespace std;

/*
 * This function display R,G and B chanels of an image wich name is given in parameter
 */
void display_chanels(const char* imsname) {
    Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
    if (ims.empty()) {
        cout << ERROR << "Can't open image " << imsname << endl;
        exit(EXIT_FAILURE);
    }
    Mat ims_rgb[3];
    split(ims, ims_rgb);
    namedWindow("R", CV_WINDOW_AUTOSIZE);
    namedWindow("G", CV_WINDOW_AUTOSIZE);
    namedWindow("B", CV_WINDOW_AUTOSIZE);
    imshow("R", ims_rgb[2]);
    imshow("G", ims_rgb[1]);
    imshow("B", ims_rgb[0]);
    waitKey(0);
}

/*
 * This function display Y,Cb and Cr chanels of an image wich name is given in parameter
 */
void display_chanels_Y_Cb_Cr(const char* imsname){
    Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
    if (ims.empty()) {
        cout << ERROR << "Can't open image " << imsname << endl;
        exit(EXIT_FAILURE);
    }
    cvtColor(ims, ims, CV_BGR2YCrCb);
    Mat ims_ycrcb[3];
    split(ims, ims_ycrcb);
    namedWindow("Y", CV_WINDOW_AUTOSIZE);
    namedWindow("Cb", CV_WINDOW_AUTOSIZE);
    namedWindow("Cr", CV_WINDOW_AUTOSIZE);
    imshow("Y", ims_ycrcb[0]);
    imshow("Cb", ims_ycrcb[1]);
    imshow("Cr", ims_ycrcb[2]);
    waitKey(0);
}

/*
 * This function convert an image in gray scale
 */
void gray_scale(const char* imsname) {
    Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
    if (ims.empty()) {
        cout << ERROR << "Can't open image " << imsname << endl;
        exit(EXIT_FAILURE);
    }
    Mat ims_gray;
    cvtColor(ims, ims_gray, CV_BGR2GRAY);
    namedWindow("Gray", CV_WINDOW_AUTOSIZE);
    imshow("Gray", ims_gray);
    waitKey(0);
}

/*
 * This function convert an image in YCbCr
 */
Mat RGB_YCbCr(const char* imsname) {
    Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
    if (ims.empty()) {
        cout << ERROR << "Can't open image " << imsname << endl;
        exit(EXIT_FAILURE);
    }
    Mat ims_ycbcr;
    cvtColor(ims, ims_ycbcr, CV_BGR2YCrCb);
    return ims_ycbcr;
}

/*
 * This function convert an image from YCbCr to RGB
 */
Mat YCbCr_RGB(Mat ims_ycbcr) {
    Mat ims_rgb;
    cvtColor(ims_ycbcr, ims_rgb, CV_YCrCb2BGR);
    return ims_rgb;
}

/*
 * This function display an Mat image
 */
void display_image(Mat ims) {
    namedWindow("Image", CV_WINDOW_AUTOSIZE);
    imshow("Image", ims);
    waitKey(0);
}

void process(const char* imsname) {
    display_chanels(imsname);
    gray_scale(imsname);
    Mat ims_ycbcr = RGB_YCbCr(imsname);
    Mat ims_rgb = YCbCr_RGB(ims_ycbcr);
    display_image(ims_rgb);
    display_chanels_Y_Cb_Cr(imsname);
}

void usage(const char* s) {
    std::cerr << "Usage: " << s << " imsname\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1]);
    return EXIT_SUCCESS;
}
