#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       3
#define ENDING      ".png"

using namespace cv;
using namespace std;

// This function load s an image from a file and returns it.
Mat loadImage(const char* fileName) {
    Mat image;
    image = imread(fileName, CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data) {
        cout << ERROR << "Could not open or find the image" << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

//This function performs adaptive thresholding without using the OpenCV function.
Mat adaptiveThresholding(Mat image, int radius, int constantinople) {
    // Préparation d'une nouvelle matrice th
    const int height = int(image.size().height);
    const int width = int(image.size().width);
    Mat th = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);

    // Application du seuillage adaptatif
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            double value = 0.0;
            int mean_size = 0;

            // On traite le carré autour du pixel
            for (int a = (i - radius); a <= (i + radius); a++) {
                for (int b = (j - radius); b <= (j + radius); b++) {

                    // On vérifie qu'on est pas hors zone image
                    if ((a >= 0 && a < height) && (b >= 0 && b < width)) {
                        value += (double) image.at<uchar>(a, b);
                        mean_size++;
                    }
                }
            }

            // On fait la moyenne finale
            if (mean_size > 0) // théoriquement tout le temps > 0
                value = (value / (double) mean_size); // Ici que ca foire je pense, perte de précision ?

            // On retire la constante
            value -= (double) constantinople;

            // On applique le seuillage
            uchar seuillage = 0;
            if (((double) image.at<uchar>(i, j)) > value)
                seuillage = 255;

            // On enregistre dans la matrice de seuillage
            th.at<uchar>(i, j) = seuillage;
        }
    }
    return th;
}

// This function performs adaptive thresholding using adaptiveThreshold with the mean where the neighborhood is determined by the parameter <radiuis>, (V∈2radius+1×2radius+1) and parameterized by the constant <constant>
Mat adaptiveThresholdingOCV(Mat image, int radius, int constant) {
    Mat result;
    result = Mat::zeros(image.rows, image.cols, CV_8UC1);
    adaptiveThreshold(image, result, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 2 * radius + 1, constant);
    return result;
}


//This function saves the image in a file with the name <fileName> and window name <windowName>.
void saveImage(Mat image, const char* fileName, const char* windowName) {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, image);
    imwrite(fileName, image);
}

// This function compute the difference between two images using opencv
Mat computeDifference(Mat image1, Mat image2) {
    Mat difference;
    absdiff(image1, image2, difference);
    return difference;
}

//This function displays the image and the window name <windowName>.
void displayImage(Mat image, const char* windowName) {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, image);
    waitKey(0);
}

void process(const char* imsname, int radius, int constantinople) {
    Mat image = loadImage(imsname);
    Mat result = adaptiveThresholding(image, radius, constantinople);
    Mat resultOCV = adaptiveThresholdingOCV(image, radius, constantinople);
    Mat difference = computeDifference(result, resultOCV);
    saveImage(result, "adaptative-th-result.png", "Adaptative Thresholding");
    saveImage(resultOCV, "adaptative-th-result-ocv.png", "Adaptative Thresholding OpenCV");
    displayImage(result, "Adaptative Thresholding");
    displayImage(resultOCV, "Adaptative Thresholding OpenCV");
    displayImage(difference, "Difference");
}

void usage(const char* s) {
    std::cerr << "Usage: " << s << " imsname radius const\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], atoi(argv[2]), atoi(argv[3]));
    return EXIT_SUCCESS;
}
