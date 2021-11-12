#include <iostream>
#include <cstdlib>

#include "morphology.hpp"

#define PARAM       3

using namespace cv;
using namespace std;

//Load a grayscale image
Mat loadImage(const char* filename)
{
    Mat image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if(image.empty())
    {
        cout << "Could not open or find the image" << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

//Load a structured element (a gray scale image)
Mat loadStructuringElement(const char* filename)
{
    Mat element = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if(element.empty())
    {
        cout << "Could not open or find the element" << endl;
        exit(EXIT_FAILURE);
    }
    return element;
}

//Save and display an image
void saveAndDisplay(const char* filename, Mat image)
{
    imwrite(filename, image);
    imshow(filename, image);
    waitKey(0);
}

// Dilate an image
Mat dilate(Mat image, Mat element)
{
    Mat dilated = Mat::zeros(image.size(), CV_LOAD_IMAGE_GRAYSCALE);
    mm(element, image, dilated, &maximum);
    return dilated;
}

void process(const char *sename, const char *imsname, const char *imdname) {
    Mat image = loadImage(imsname);
    Mat element = loadStructuringElement(sename);
    Mat dilated = dilate(image, element);
    saveAndDisplay(imdname, dilated);
}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " im-se ims imd" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], argv[2], argv[3]);
    return EXIT_SUCCESS;
}

