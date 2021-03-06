#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       1
#define MAX_PIXEL_LEVELS 256

using namespace cv;
using namespace std;


// Load a grayscale image from a file
Mat loadImage(const char* filename) {
    Mat image;
    image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data) {
        cout << ERROR << "Could not open or find the image" << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

// Save a grayscale image to a file
void saveImage(const char* filename, Mat image) {
    imwrite(filename, image);
}

/*
 * Display an image
 * @param image : image to display
 * @param title : title of the window
 */
void displayImage(Mat image, const char* title) {
    namedWindow(title, WINDOW_AUTOSIZE);
    imshow(title, image);
    waitKey(0);
}

/*
 * Compute difference between two images
 */
Mat difference(Mat image1, Mat image2) {
    Mat difference;
    absdiff(image1, image2, difference);
    return difference;
}

/*
 * Perform the method of otsu
 */
Mat otsu(Mat ims) {
    int hist[MAX_PIXEL_LEVELS];
    int height = int(ims.size().height);
    int width = int(ims.size().width);
    // equilibrage histogramme à la main
    int temp;
    // initialisation du tableaux
    for (int i = 0; i < MAX_PIXEL_LEVELS; i++)
        hist[i] = 0;

    // création de l'histogramme
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp = int(ims.at<uchar>(i, j));
            hist[temp]++;
        }
    }

    // Méthode Otsu manuel en passant par la maximisation de la variance inter-classe
    double total_pixels = width * height;
    double total_sum_prob = 0.0, current_prob_summ = 0.0;
    double p1 = 0.0, p2 = 0.0;
    double u1, u2;
    double vb_max = 0.0;
    int thr_manual = 0;
    Mat im_thr_manual = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);

    // On calcule d'abord la somme totale des probabilités
    for (int i = 0; i < MAX_PIXEL_LEVELS; i++) {
        total_sum_prob += (double) (i * hist[i]);
    }

    // On parcours l'histogramme et on applique Otsu
    for (int i = 0; i < MAX_PIXEL_LEVELS; i++) {

        // On met à jours les probabilités P1 et P2
        p1 += hist[i];
        p2 = total_pixels - p1;

        // On met à jour la somme des probabilités
        current_prob_summ += (double) (i * hist[i]);

        // On calcule les nouvelles moyennes à l'aide des propriétés algorithmiques d'Otsu
        u1 = current_prob_summ / p1;
        u2 = (total_sum_prob - current_prob_summ) / p2;

        // On calcule la variance vb
        double vb = p1 * p2 * (u1 - u2) * (u1 - u2);

        // On teste le nouveau seuil par rapport à l'ancien
        if (vb > vb_max) {
            vb_max = vb;
            thr_manual = i;
        }
    }
    // Application du seuillage
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            // On applique le seuillage
            uchar seuillage = 0;
            if (((double) ims.at<uchar>(i, j)) > thr_manual)
                seuillage = 255;

            // On enregistre dans la matrice de seuillage
            im_thr_manual.at<uchar>(i, j) = seuillage;
        }
    }
    return im_thr_manual;
}

/*
 * Use the threshold function with TRESH_BINARY + THRESH_OTSU parameters
 */
Mat otsu_threshold(Mat ims) {
    Mat im_thr_otsu;
    threshold(ims, im_thr_otsu, 0, 255, THRESH_BINARY + THRESH_OTSU);
    return im_thr_otsu;
}

void process(const char* imsname) {
    Mat ims = loadImage(imsname);
    Mat im_thr_manual = otsu(ims);
    Mat im_thr_otsu = otsu_threshold(ims);
    saveImage("otsu-th.png", im_thr_manual);
    saveImage("otsu-th-ocv.png", im_thr_otsu);
    displayImage(ims, "Original image");
    displayImage(im_thr_manual, "Manual thresholding");
    displayImage(im_thr_otsu, "Otsu thresholding");
    Mat diff = difference(im_thr_manual, im_thr_otsu);
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
