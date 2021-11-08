#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

// Include header files from OpenCV directory
// required to stitch images.
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"


#define PARAM       2


using namespace cv;

using namespace std;


void process(char *ims_name_1, char *ims_name_2){
 
}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " ims-name-1 ims-name-2" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
