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


void process(const char *imsname) {

    Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
    if (!ims.data) {
        cout << "Could not open the image " << imsname << endl;
        exit(1);
    }

    //Conversion de l'image couleur en niveaux de gris
    Mat gray;
    cvtColor(ims, gray, CV_BGR2GRAY);
    imshow("RGBtoGray", gray);
    int type = gray.type();

    int height = int(ims.size().height);
    int width = int(ims.size().width);
    cout<< height <<"   "<< width<<endl;
    cout<<ims.type()<<endl;
    // Affichage des canaux R, G et B dans 3 images monochromes
    Mat r = Mat::zeros(height, width, type);
    Mat g = Mat::zeros(height, width, type);
    Mat b = Mat::zeros(height, width, type);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            b.at<uchar>(i, j) = ims.at<Vec3b>(i, j)[0];
            g.at<uchar>(i, j) = ims.at<Vec3b>(i, j)[1];
            r.at<uchar>(i, j) = ims.at<Vec3b>(i, j)[2];
        }
    }
    imshow("r", r);
    imshow("g", g);
    imshow("b", b);
    cout<<int(r.size().width)<<endl;


    //conversion rgb to ycbcr pui ycbcr to rgbtoYCbCr
    Mat im_rgbtoYCbCr = Mat::zeros(height, width, CV_32FC3);
    Mat im_YCbCrtorgb = Mat::zeros(height, width, ims.type());

    cvtColor(ims, im_rgbtoYCbCr, CV_BGR2YCrCb);
    cvtColor(im_rgbtoYCbCr, im_YCbCrtorgb, CV_YCrCb2BGR);

    imshow("RGBtoYCbCrtoRGB", im_YCbCrtorgb);

    Mat Y = Mat::zeros(height, width, type);
    Mat Cb = Mat::zeros(height, width, type);
    Mat Cr = Mat::zeros(height, width, type);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Y.at<uchar>(i, j) = im_rgbtoYCbCr.at<Vec3b>(i, j)[0];
            Cb.at<uchar>(i, j) = im_rgbtoYCbCr.at<Vec3b>(i, j)[1];
            Cr.at<uchar>(i, j) = im_rgbtoYCbCr.at<Vec3b>(i, j)[2];
        }
    }
    imshow("Y", Y);
    imshow("Cb", Cb);
    imshow("Cr", Cr);

    Mat dif = gray-Y;
    Mat dif2 = ims-im_YCbCrtorgb;
    imshow("Difference gray-Y", dif);
    imshow("Difference Original-RGBtoYCbCrtoRGB", dif2);


    waitKey(0);
    destroyAllWindows();

}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " imsname\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1]);
    return EXIT_SUCCESS;
}
