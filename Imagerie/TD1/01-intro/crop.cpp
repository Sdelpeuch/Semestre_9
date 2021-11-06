#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// This function use opencv2 to extract a sub-picture of imname from (i0, j0) with w width and h height then display it then save it in crop.png
void process(const char* imsname, int i0, int j0, int w, int h){
    Mat im = imread(imsname, CV_LOAD_IMAGE_COLOR);
    Mat crop = im(Rect(j0, i0, w, h));
    imshow("crop", crop);
    imwrite("crop.png", crop);
}

void
usage(const char* s) {
    std::cerr << "Usage: " << s << " imsname i0 j0 w h\n" << std::endl;
    exit(EXIT_FAILURE);
}

#define param 5

int
main(int argc, char* argv[]) {
    if (argc != (param + 1))
        usage(argv[0]);
    cout << argv[1] << endl;
    process(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    return EXIT_SUCCESS;
}
