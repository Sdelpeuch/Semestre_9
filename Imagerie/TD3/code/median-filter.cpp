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

/*
 * Load a grayscale image from a file
 */
Mat loadImage(const char* filename) {
    Mat image = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    if (image.empty()) {
        cout << ERROR << "Could not open or find the image" << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

/*
 * Display and save an image
 * @param image : image to display
 * @param filename : name of the file to save
 * @param windowName : name of the window
 */
void displaySaveImage(const Mat image, const char* filename, const char* windowName) {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, image);
    imwrite(filename, image);
    waitKey(0);
}

/*
 * Compute the difference between two images
 */
Mat difference(const Mat image1, const Mat image2) {
    Mat difference;
    absdiff(image1, image2, difference);
    return difference;
}

void quickSort(int* array, int low, int high) {
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2];
    int temp;

    while (i <= j) {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(array, low, j);
    if (i < high)
        quickSort(array, i, high);
}

void mat_to_tab(Mat matrix, int* tab) {
    int height = int(matrix.size().height);
    int width = int(matrix.size().width);
    //int tab[height*width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int k = width * i + j;
            tab[k] = int(matrix.at<uchar>(i, j));
        }
    }
}

/*
 * @brief : median filter
 * Perform a median filter on an image whee the search radius is set to 2*r+1
 * @param image : image to filter
 * @param radius : radius of the filter
 */
Mat medianFilter(const Mat ims, const int r) {
    int length = 2 * r + 1;
    const int height = int(ims.size().height);
    const int width = int(ims.size().width);
    Mat imd = Mat::zeros(height, width, ims.type());


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //bord haut
            if (i < r) {
                //coin haut gauche
                if (j < r) {
                    int diff_i = r - i;
                    int diff_j = r - j;
                    Mat H = Mat::zeros(length - diff_i, length - diff_j, ims.type());
                    int* tab_H;
                    tab_H = new int[(length - diff_i) * (length -
                                                         diff_j)];  //tableau ou on va stocker les niveaux de gris des pixels voisins
                    for (int k = 0; k < int(sizeof(tab_H)); k++) {
                        tab_H[k] = 0;
                    }
                    for (int u = 0; u < length - i; u++) {
                        for (int v = 0; v < length - j; v++) {
                            H.at<uchar>(u, v) = ims.at<uchar>(u, v); //on stocke les pixels voisins
                        }
                    }
                    mat_to_tab(H, tab_H);
                    quickSort(tab_H, 0, (length - diff_i) * (length - diff_j) -
                                        1); //on tri en fonctions de l'intensite des pixels
                    imd.at<uchar>(i, j) = tab_H[int(
                            ((length - diff_i) * (length - diff_j)) / 2)]; // on recupere le pixel median
                    delete[] tab_H;
                }
                    //coin haut droit
                else if (j + r > width - 1) {
                    int diff_i = r - i;
                    int diff_j = r - ((width - 1) - j);
                    Mat H = Mat::zeros(length - diff_i, length - diff_j, ims.type());
                    int* tab_H;
                    tab_H = new int[(length - diff_i) * (length - diff_j)];
                    for (int k = 0; k < int(sizeof(tab_H)); k++) {
                        tab_H[k] = 0;
                    }
                    for (int u = 0; u < length - i; u++) {
                        for (int v = 0; v < length - diff_j; v++) {
                            H.at<uchar>(u, v) = ims.at<uchar>(u, v + j - r);
                        }
                    }
                    mat_to_tab(H, tab_H);
                    quickSort(tab_H, 0, (length - diff_i) * (length - diff_j) - 1);
                    imd.at<uchar>(i, j) = tab_H[int(((length - diff_i) * (length - diff_j)) / 2)];
                    delete[] tab_H;
                }
                    //entre les coins
                else {
                    int diff_i = r - i;
                    Mat H = Mat::zeros(length - diff_i, length, ims.type());
                    int* tab_H;
                    tab_H = new int[(length - diff_i) * (length)];
                    for (int k = 0; k < int(sizeof(tab_H)); k++) {
                        tab_H[k] = 0;
                    }
                    for (int u = 0; u < length - i; u++) {
                        for (int v = 0; v < length; v++) {
                            H.at<uchar>(u, v) = ims.at<uchar>(u, v + j - r);
                        }
                    }
                    mat_to_tab(H, tab_H);
                    quickSort(tab_H, 0, (length - diff_i) * (length) - 1);
                    imd.at<uchar>(i, j) = tab_H[int(((length - diff_i) * (length)) / 2)];
                    delete[] tab_H;
                }
            }
                //bord bas
            else if (i + r > height - 1) {
                //coin bas gauche
                if (j < r) {
                    int diff_i = r - ((height - 1) - i);
                    int diff_j = r - j;
                    Mat H = Mat::zeros(length - diff_i, length - diff_j, ims.type());
                    int* tab_H;
                    tab_H = new int[(length - diff_i) * (length - diff_j)];
                    for (int k = 0; k < int(sizeof(tab_H)); k++) {
                        tab_H[k] = 0;
                    }
                    for (int u = 0; u < length - diff_i; u++) {
                        for (int v = 0; v < length - j; v++) {
                            H.at<uchar>(u, v) = ims.at<uchar>(u + i - r, v);
                        }
                    }
                    mat_to_tab(H, tab_H);
                    quickSort(tab_H, 0, (length - diff_i) * (length - diff_j) - 1);
                    imd.at<uchar>(i, j) = tab_H[int(((length - diff_i) * (length - diff_j)) / 2)];
                    delete[] tab_H;
                }
                    //coin bas droit
                else if (j + r > width - 1) {
                    int diff_i = r - ((height - 1) - i);
                    int diff_j = r - ((width - 1) - j);
                    Mat H = Mat::zeros(length - diff_i, length - diff_j, ims.type());
                    int* tab_H;
                    tab_H = new int[(length - diff_i) * (length - diff_j)];
                    for (int k = 0; k < int(sizeof(tab_H)); k++) {
                        tab_H[k] = 0;
                    }
                    for (int u = 0; u < length - diff_i; u++) {
                        for (int v = 0; v < length - diff_j; v++) {
                            H.at<uchar>(u, v) = ims.at<uchar>(u + i - r, v + j - r);
                        }
                    }
                    mat_to_tab(H, tab_H);
                    quickSort(tab_H, 0, (length - diff_i) * (length - diff_j) - 1);
                    imd.at<uchar>(i, j) = tab_H[int(((length - diff_i) * (length - diff_j)) / 2)];
                    delete[] tab_H;
                }
                    //entre les coins
                else {
                    int diff_i = r - ((height - 1) - i);
                    Mat H = Mat::zeros(length - diff_i, length, ims.type());
                    int* tab_H;
                    tab_H = new int[(length - diff_i) * (length)];
                    for (int k = 0; k < int(sizeof(tab_H)); k++) {
                        tab_H[k] = 0;
                    }
                    for (int u = 0; u < length - diff_i; u++) {
                        for (int v = 0; v < length; v++) {
                            H.at<uchar>(u, v) = ims.at<uchar>(u + i - r, v + j - r);
                        }
                    }
                    mat_to_tab(H, tab_H);
                    quickSort(tab_H, 0, (length - diff_i) * (length) - 1);
                    imd.at<uchar>(i, j) = tab_H[int(((length - diff_i) * (length)) / 2)];
                    delete[] tab_H;
                }
            }
                //bord gauche
            else if (j < r) {
                //entre les coins (le cas des coins sont traites precedement)
                if ((i >= r) & (i + r < (height - 1))) {
                    int diff_j = r - j;
                    Mat H = Mat::zeros(length, length - diff_j, ims.type());
                    int* tab_H;
                    tab_H = new int[(length) * (length - diff_j)];
                    for (int k = 0; k < int(sizeof(tab_H)); k++) {
                        tab_H[k] = 0;
                    }
                    for (int u = 0; u < length; u++) {
                        for (int v = 0; v < length - j; v++) {
                            H.at<uchar>(u, v) = ims.at<uchar>(u + i - r, v);
                        }
                    }
                    mat_to_tab(H, tab_H);
                    quickSort(tab_H, 0, (length) * (length - diff_j) - 1);
                    imd.at<uchar>(i, j) = tab_H[int(((length) * (length - diff_j)) / 2)];
                    delete[] tab_H;
                }
            }
                //bord droit
            else if (j + r > width - 1) {
                //entre les coins (le cas des coins sont traites precedement)
                if ((i >= r) & (i + r < (height - 1))) {
                    int diff_j = r - ((width - 1) - j);
                    Mat H = Mat::zeros(length, length - diff_j, ims.type());
                    int* tab_H;
                    tab_H = new int[(length) * (length - diff_j)];
                    for (int k = 0; k < int(sizeof(tab_H)); k++) {
                        tab_H[k] = 0;
                    }
                    for (int u = 0; u < length; u++) {
                        for (int v = 0; v < length - diff_j; v++) {
                            H.at<uchar>(u, v) = ims.at<uchar>(u + i - r, v + j - r);
                        }
                    }
                    mat_to_tab(H, tab_H);
                    quickSort(tab_H, 0, (length) * (length - diff_j) - 1);
                    imd.at<uchar>(i, j) = tab_H[int(((length) * (length - diff_j)) / 2)];
                    delete[] tab_H;
                }
            }
                //entre le bord haut et le bord bas
            else {
                Mat H = Mat::zeros(length, length, ims.type());
                int* tab_H;
                tab_H = new int[length * length];
                for (int k = 0; k < int(sizeof(tab_H)); k++) {
                    tab_H[k] = 0;
                }
                for (int u = 0; u < length; u++) {
                    for (int v = 0; v < length; v++) {
                        H.at<uchar>(u, v) = ims.at<uchar>(i + u - r, j + v - r);
                    }
                }
                mat_to_tab(H, tab_H);
                quickSort(tab_H, 0, length * length - 1);
                imd.at<uchar>(i, j) = tab_H[int(((length) * (length)) / 2)];
                delete[] tab_H;
            }
        }
    }
    return imd;
}

/*
 * @brief : median filter opencv
 * Perform a median filter on an image whee the search radius is set to 2*r+1 with opencv
 * @param image : image to filter
 * @param radius : radius of the filter
 */
Mat medianFilterOpenCV(const Mat image, const int radius) {
    Mat filteredImage = Mat::zeros(image.rows, image.cols, CV_8UC1);
    medianBlur(image, filteredImage, 4 * radius + 1);
    return filteredImage;
}

void process(int r, const char* imsname, const char* imdname) {
    Mat image = loadImage(imsname);
    Mat filteredImage = medianFilter(image, r);
    Mat filteredImageOpenCV = medianFilterOpenCV(image, r);
    Mat diff = difference(filteredImage, filteredImageOpenCV);
    displaySaveImage(filteredImage, imdname, "Median filtered image");
    displaySaveImage(filteredImageOpenCV, "median-ocv.png", "Median filtered image with opencv");
    displaySaveImage(diff, "diff.png", "Difference between the two median filtered images");
}

void usage(const char* s) {
    std::cerr << "Usage: " << s << " r imsname imdname\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), argv[2], argv[3]);

    return EXIT_SUCCESS;
}
