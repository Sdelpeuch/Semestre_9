#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void process(const char* imsname, const char* imdname) {
    FILE* fp = fopen( imsname, "rb" );
    if( fp != nullptr ){
        Mat ims = imread(imsname);
        imshow("Image chargée", ims);
        cout << "Width " << ims.size().width << " Height " << ims.size().height << endl;
    }
    else{
        cerr << "Image path is incorrect" << endl;
    }
    Mat imd(100, 200, CV_8UC3, Scalar(255, 0, 255));
    imshow("Image Magenta", imd);
    imwrite(imdname, imd);
    cv::waitKey(0);
}

void usage(const char* s) {
    std::cerr << "Usage: " << s << " imsname imdname\n" << std::endl;
    exit(EXIT_FAILURE);
}

#define param 2

int main(int argc, char* argv[]) {
    if (argc != (param + 1))
        usage(argv[0]);
    process(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
