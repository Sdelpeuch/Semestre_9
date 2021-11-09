#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       3
#define ENDING      ".png"

#define PATCH_SIZE  7
#define SQUARE_SIZE 11

using namespace cv;
using namespace std;


/*
 * @brief Load a gray image from a file
 * @param filename : the name of the file
 * @return the image
 */
Mat loadGrayImage(string filename) {
    Mat image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data) {
        cout << ERROR << "Error while loading the image" << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

/*
 * @biref Save a gray image in a file
 * @param filename : the name of the file
 * @param image : the image
 */
void saveGrayImage(string filename, Mat image) {
    imwrite(filename, image);
}

/*
 * @brief Display a gray image
 * @param image : the image
 * @param title : the title of the window
 */
void displayGrayImage(Mat image, string title) {
    namedWindow(title, CV_WINDOW_AUTOSIZE);
    imshow(title, image);
    waitKey(0);
}

/*
 * @brief Compute the difference between two images
 * @param image1 : the first image
 * @param image2 : the second image
 * @return the difference
 */
Mat difference(Mat image1, Mat image2) {
    Mat difference = Mat(image1.rows, image1.cols, CV_8UC1);
    for (int i = 0; i < image1.rows; i++) {
        for (int j = 0; j < image1.cols; j++) {
            difference.at<uchar>(i, j) = abs(image1.at<uchar>(i, j) - image2.at<uchar>(i, j));
        }
    }
    return difference;
}

/*
 * @brief Filter the image by no local mean
 * @param image : the image
 * @param sigmas : the sigma of the gaussian
 * @param patchSize : the size of the patch
 * @return the filtered image
 */
Mat noLocalMean(Mat image, int sigmas, int patchSize) {
    Mat filteredImage = Mat(image.rows, image.cols, CV_8UC1);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            int sum = 0;
            for (int k = i - patchSize / 2; k <= i + patchSize / 2; k++) {
                for (int l = j - patchSize / 2; l <= j + patchSize / 2; l++) {
                    if (k >= 0 && k < image.rows && l >= 0 && l < image.cols) {
                        sum += image.at<uchar>(k, l);
                    }
                }
            }
            sigmas++;
            filteredImage.at<uchar>(i, j) = sum / (patchSize * patchSize);
        }
    }
    return filteredImage;
}

void process(int sigma, const char *imsname, const char *imdname) {
    Mat image = loadGrayImage(imsname);
    Mat filtered = noLocalMean(image, sigma, PATCH_SIZE);
    displayGrayImage(filtered, "Filtered");
    saveGrayImage(imdname, filtered);
}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " sigma imsname imdname\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), argv[2], argv[3]);
    return EXIT_SUCCESS;
}
