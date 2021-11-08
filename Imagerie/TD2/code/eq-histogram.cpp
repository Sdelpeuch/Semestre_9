#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

#define ERROR       "\033[31mError : \033[0m"
#define PARAM       1

using namespace cv;
using namespace std;

// This function loads an image from a file and returns it.
Mat loadImage(const char* imsname) {
    Mat image;
    image = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data) {
        cout << ERROR << "Could not open or find the image" << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

//This function realize the method of histogram equalization without using equalizeHist function and save the result in a new image eq.png.
Mat histogramEqualization(Mat ims) {
    int height = int(ims.size().height);
    int width = int(ims.size().width);
    Mat eq_main = Mat::zeros(height, width, ims.type());
    int I_max = 256;
    int hist[I_max];
    float hist_n[I_max];
    int hist_c[I_max];
    float hist_cn[I_max];

    int temp;
    //initialisation des tableaux
    for(int i = 0; i < I_max; i++){
        hist_c[i] = 0;
        hist[i] = 0;
        hist_cn[i] = 0.0f;
        hist_n[i] = 0.0f;
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            temp = int(ims.at<uchar>(i, j));
            hist[temp] ++;
        }
    }

    //determination des histogrammes normalises, cumules et cumules normalises
    for(int i = 0; i < I_max; i++){
        hist_n[i] = hist[i]/(float(height*width));
        if (i==0){
            hist_c[i] = hist[i];
            hist_cn[1] = hist_n[i];
        }
        else{
            hist_c[i] = hist_c[i-1] + hist[i];
            hist_cn[i] = hist_cn[i-1] + hist_n[i];
        }
    }

    //construction de l'image equilibree
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            temp = (I_max)*hist_cn[int(ims.at<uchar>(i, j))];
            eq_main.at<uchar>(i, j) = uchar(temp);
        }
    }
    return eq_main;
}

// This function realize the methode of histogram equalization using equalizeHist function and save the result in a new image eq_ocv.png.
Mat histogramEqualizationOcv(Mat image) {
    Mat histogram_eq_image;
    equalizeHist(image, histogram_eq_image);
    imwrite("eq_ocv.png", histogram_eq_image);
    return histogram_eq_image;
}

// This function compute the difference between the two images and save the result in a new image diff.png.
Mat computeDiff(const Mat &image1, const Mat &image2) {
    Mat diff;
    absdiff(image1, image2, diff);
    imwrite("diff.png", diff);
    return diff;
}

// This function display the image in a window.
void displayImage(const Mat &image, const char* windowName) {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, image);
    waitKey(0);
}

void process(const char* imsname) {
    Mat image = loadImage(imsname);
    Mat histogram_eq_image = histogramEqualization(image);
    Mat histogram_eq_image_ocv = histogramEqualizationOcv(image);
    Mat diff = computeDiff(histogram_eq_image, histogram_eq_image_ocv);
    displayImage(image, "Original image");
    displayImage(histogram_eq_image, "Histogram equalization");
    displayImage(histogram_eq_image_ocv, "Histogram equalization using OpenCV");
    displayImage(diff, "Difference");
}

void usage(const char* s) {
    std::cerr << "Usage: " << s << " imsname\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1]);
    return EXIT_SUCCESS;
}
