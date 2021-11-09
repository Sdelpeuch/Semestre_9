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
 * @brief process a bilateral filter without using opencv
 * @param image : the image
 * @param sigma_s : the spatial sigma
 * @param sigma_g : the color sigma
 * @return the filtered image
 */
Mat bilateralFilterNoOcv(Mat ims, double sigma_s, double sigma_g) {
    int height = int(ims.size().height);
    int width = int(ims.size().width);
    int i_max = (height > width) ? height : width;
    double Gs[i_max];
    int radius = i_max;

    for (int i = 0; i < i_max; i++) {
        Gs[i] = exp(-(i * i) / (2.0 * (sigma_s * sigma_s)));
        if (Gs[i] <= SEUILLAGE) {
            radius = i;
            break;
        }
    }

    // Pré-calcul de tous les coefficients possible de Gg (Intensité de 0 à 255)
    double Gg[GRAYSCALE];
    for (int i = 0; i < GRAYSCALE; i++) {
        Gg[i] = exp(-(i * i) / (2.0 * (sigma_g * sigma_g)));
    }
    Mat bilateral = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            double numerator = 0.0;
            double denominator = 0.0;

            // On traite le carré autour du pixel
            for (int a = (i - radius); a <= (i + radius); a++) {
                for (int b = (j - radius); b <= (j + radius); b++) {
                    // On vérifie qu'on n'est pas hors zone image
                    if ((a >= 0 && a < height) && (b >= 0 && b < width)) {
                        // On calcule la distance entre les deux pixels
                        int distance = (int) sqrt(pow((i - a), 2) + pow((j - b), 2));
                        // On vérifie qu'on est bien dans le cercle dessiné par radius autour du point central (i;j)
                        if (distance <= radius) {
                            int diff_I = (int) abs(ims.at<uchar>(i, j) - ims.at<uchar>(a, b));
                            numerator += (Gs[distance] * Gg[diff_I] * (double) ims.at<uchar>(a, b));
                            denominator += (Gs[distance] * Gg[diff_I]);
                        }
                    }
                }
            }
            if (denominator > 0.0)
                bilateral.at<uchar>(i, j) = (uchar) (numerator / denominator);
            else
                bilateral.at<uchar>(i, j) = ims.at<uchar>(i, j);
        }
    }
    return bilateral;
}

/*
 * @brief process a bilateral filter using opencv
 * @param image : the image
 * @param sigma_s : the spatial sigma
 * @param sigma_g : the color sigma
 * @return the filtered image
 */
Mat bilateralFilterOcv(Mat image, double sigma_s, double sigma_g) {
    Mat filtered = Mat::zeros(image.rows, image.cols, CV_8UC1);
    bilateralFilter(image, filtered, -1, sigma_s, sigma_g);
    return filtered;
}

void process(int sigma_s, int sigma_g, const char* imsname, const char* imdname) {
    Mat image = loadGrayImage(imsname);
    Mat filteredNoOcv = bilateralFilterNoOcv(image, sigma_s, sigma_g);
    Mat filtered = bilateralFilterOcv(image, sigma_s, sigma_g);
    Mat diff = difference(filtered, filteredNoOcv);
    saveGrayImage(imdname, filtered);
    displayGrayImage(image, "Original");
    displayGrayImage(filteredNoOcv, "Filtered (no ocv)");
    displayGrayImage(filtered, "Filtered");
    displayGrayImage(diff, "Difference");
}

void usage(const char* s) {
    std::cerr << "Usage: " << s << " sigma_s sigma_g ims imd\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
    return EXIT_SUCCESS;
}
