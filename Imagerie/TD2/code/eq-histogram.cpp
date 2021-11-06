#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       1

using namespace cv;
using namespace std;

void process(const char *imsname) {

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
