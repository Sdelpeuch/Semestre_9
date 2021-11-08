#include <iostream>
#include <cstdlib>
#include <math.h>
#include <time.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       4
#define ENDING      ".png"

#define SEUILLAGE   0.1
#define GRAYSCALE   256

using namespace cv;
using namespace std;

void process(int sigma_s, int sigma_g, const char *imsname, const char *imdname) {

}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " sigma_s sigma_g ims imd\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
    return EXIT_SUCCESS;
}
