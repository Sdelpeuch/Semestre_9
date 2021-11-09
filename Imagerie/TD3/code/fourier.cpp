#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       2
#define ENDING      ".png"

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
 * Perform a Fourier transform using the dft function
 * @param image : the image
 * @param frequency : the frequency
 * @return the Fourier transform
 */
Mat fourier(Mat image) {
    Mat fourier = Mat(image.rows, image.cols, CV_32FC1);
    dft(image, fourier, DFT_REAL_OUTPUT);
    return fourier;
}

/*
 * Perform the amplitude of the Fourier transform
 * @param fourier : the Fourier transform
 * @return the amplitude
 */
Mat amplitude(Mat fourier) {
    Mat amplitude = Mat(fourier.rows, fourier.cols, CV_32FC1);
    for (int i = 0; i < fourier.rows; i++) {
        for (int j = 0; j < fourier.cols; j++) {
            amplitude.at<float>(i, j) = sqrt(pow(fourier.at<float>(i, j), 2) + pow(fourier.at<float>(i, j), 2));
        }
    }
    return amplitude;
}

/*
 * Perform the phase of the Fourier transform
 * @param fourier : the Fourier transform
 * @return the phase
 */
Mat phase(Mat fourier) {
    Mat phase = Mat(fourier.rows, fourier.cols, CV_32FC1);
    for (int i = 0; i < fourier.rows; i++) {
        for (int j = 0; j < fourier.cols; j++) {
            phase.at<float>(i, j) = atan2(fourier.at<float>(i, j), fourier.at<float>(i, j));
        }
    }
    return phase;
}

/*
 * Do a fourier filter and cancel the frequency
 * @param fourier : the Fourier transform
 * @return the filtered Fourier transform
 */
Mat fourierFilter(Mat fourier, float frequency) {
    Mat filteredFourier = Mat(fourier.rows, fourier.cols, CV_32FC1);
    for (int i = 0; i < fourier.rows; i++) {
        for (int j = 0; j < fourier.cols; j++) {
            filteredFourier.at<float>(i, j) =
                    fourier.at<float>(i, j) * (1 - (pow(frequency, 2) / (pow(i, 2) + pow(j, 2))));
        }
    }
    return filteredFourier;
}

/*
 * Perform the inverse Fourier transform
 */
Mat inverseFourier(Mat fourier) {
    Mat inverseFourier = Mat(fourier.rows, fourier.cols, CV_32FC1);
    idft(fourier, inverseFourier);
    return inverseFourier;
}


void process(const char* imsname, float frequency) {
    frequency++;
    Mat image = loadGrayImage(imsname);
    int m = getOptimalDFTSize( image.rows );
    int n = getOptimalDFTSize( image.cols ); // on the border add zero values
    copyMakeBorder(image, image, 0, m - image.rows, 0, n - image.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(image), Mat::zeros(image.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);

    Mat f = fourier(complexI);
//    saveGrayImage("fourier.png", f);
    Mat fF = fourierFilter(f, frequency);
//    saveGrayImage("fourierFilter.png", fF);
    Mat iF = inverseFourier(complexI);
//    saveGrayImage("inverseFourier.png", iF);
    Mat a = amplitude(f);
//    saveGrayImage("amplitude.png", a);
    Mat p = phase(f);
//    saveGrayImage("phase.png", p);
//    displayGrayImage(image, "Original image");
//    displayGrayImage(f, "Fourier transform");
//    displayGrayImage(a, "Amplitude");
//    displayGrayImage(p, "Phase");
//    displayGrayImage(fF, "Fourier filter");
//    displayGrayImage(iF, "Inverse Fourier transform");
}

void usage(const char* s) {
    std::cerr << "Usage: " << s << " imsname radius const\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], atoi(argv[2]));
    return EXIT_SUCCESS;
}
