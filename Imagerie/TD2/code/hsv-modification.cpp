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

void process(int h, int s, int v, const char *imsname, const char *imdname) {
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
