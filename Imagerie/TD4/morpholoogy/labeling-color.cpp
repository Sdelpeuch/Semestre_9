#include <iostream>
#include <stdlib.h>
#include <cstdlib>

#include <opencv2/opencv.hpp>

#define INFO        "\033[32mInfo : \033[0m"
#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define ENDING      ".png"
#define PARAM       3

using namespace cv;
using namespace std;

// Load a binary image
Mat loadImage(string path) {
    Mat image = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
    if (image.empty()) {
        cout << ERROR << "Image " << path << " not found" << endl;
        exit(EXIT_FAILURE);
    }
    return image;
}

// Save a binary image
void saveImage(Mat image, string path) {
    imwrite(path, image);
    imshow("Image", image);
    waitKey(0);
}

int _find(int p, int *roots) {
    while (roots[p] != p)
        p = roots[p];
    return p;
}

int _union(int r0, int r1, int *roots) {
    if (r0 == r1) return r0;
    if (r0 == -1) return r1;
    if (r1 == -1) return r0;
    if (r0 < r1) {
        roots[r1] = r0;
        return r0;
    } else {
        roots[r0] = r1;
        return r1;
    }
}

int _add(int p, int r, int *roots) {
    if (r == -1)
        roots[p] = p;
    else
        roots[p] = r;
    return roots[p];
}

void process(const char *imsname, const char *regname, const char *colorname) {
    Mat ims = loadImage(imsname);
    int *roots = new int[ims.total()];
    int rows = ims.rows;
    int cols = ims.cols;
    int p = 0;
    int r = -1;
    uchar *ps = ims.data;
    Mat reg_mat = Mat::zeros(ims.size().height, ims.size().width, CV_LOAD_IMAGE_GRAYSCALE);
    Mat color_mat = Mat::zeros(ims.size().height, ims.size().width, CV_8UC3);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            r = -1;
            if (j > 0 && (*(ps - 1) == (*ps)))
                r = _union(_find(p - 1, roots), r, roots);
            if ((i > 0 && j > 0) && (*(ps - 1 - cols) == (*ps)))
                r = _union(_find(p - 1 - cols, roots), r, roots);
            if (i > 0 && (*(ps - cols) == (*ps)))
                r = _union(_find(p - cols, roots), r, roots);
            if ((j < (cols - 1) && i > 0) && (*(ps + 1 - cols) == (*ps)))
                r = _union(_find(p + 1 - cols, roots), r, roots);
            r = _add(p, r, roots);
            p++;
            ps++;
        }
    }
    for (p = 0; p < rows * cols; p++) {
        roots[p] = _find(p, roots);
    }
    int l = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int p = i * cols + j;
            if (roots[p] == p){
                roots[p] = l++;
            }
            else{
                roots[p] = roots[roots[p]];
            }
            reg_mat.at<uchar>(i,j) = roots[p];
            if (roots[p] > 0) {
                srand(roots[p]);
                color_mat.at<Vec3b>(i, j)[0] = (uchar) (rand()%255); // B
                color_mat.at<Vec3b>(i, j)[1] = (uchar) (rand()%255); // G
                color_mat.at<Vec3b>(i, j)[2] = (uchar) (rand()%255); // R
            }
        }
    }
    cout << "labeling: " << l << " components detected" << endl;
    saveImage(reg_mat, regname);
    saveImage(color_mat, colorname);
    delete[] roots;
}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " ims-name reg-name color-name" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], argv[2], argv[3]);
    return EXIT_SUCCESS;
}

