#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

#define INFO        "\033[32mInfo : \033[0m"
#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       3
#define ENDING      ".png"

using namespace cv;
using namespace std;

enum {
    SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS
};

bool hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void saveImage(const char *imdname, Mat *image) {
    // On vérifie le nom rentré par l'utilisateur
    if (!hasEnding(imdname, ENDING)) { // On vérifie que ca se termine bien par .png sinon OpenCV plante
        cout << WARNING << "name provide is not complete, adding \"" << ENDING << "\"." << endl;
        imdname = string(imdname).append(ENDING).c_str();
    }

    cout << INFO << "Saving matrice to " << imdname << " ..." << endl;
    imwrite(imdname, *image); // sauvegarde
}

void process(const int shape, const int halfsize, const char *imdname) {

    // Création de la matrice
    int length = 2 * halfsize + 1;
    Mat ims = Mat::zeros(length, length, CV_8U);

    // Création du shape suivant le cas
    if (shape == SQUARE) {
        cout << INFO << "Making a square shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                ims.at<uchar>(i, j) = 255;
            }
        }
        saveImage(imdname, &ims);
    } else if (shape == DIAMOND) {
        cout << INFO << "Making a diamond shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if ((i + j >= halfsize) & (i + j <= 3 * halfsize) & (i - j >= -halfsize) & (i - j <= halfsize)) {
                    ims.at<uchar>(i, j) = 255;
                } else {
                    ims.at<uchar>(i, j) = 0;
                }
            }
        }
        saveImage(imdname, &ims);
    } else if (shape == DISK) {
        cout << INFO << "Making a disk shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                int disk = (i - halfsize) * (i - halfsize) + (j - halfsize) * (j - halfsize);
                if (disk <= halfsize * halfsize) {
                    ims.at<uchar>(i, j) = 255;
                } else {
                    ims.at<uchar>(i, j) = 0;
                }
            }
        }
        saveImage(imdname, &ims);
    } else if (shape == LINE_V) {
        cout << INFO << "Making a vertical line shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if (j == halfsize) {
                    ims.at<uchar>(i, j) = 255;
                } else {
                    ims.at<uchar>(i, j) = 0;
                }
            }
        }
        saveImage(imdname, &ims);
    } else if (shape == DIAG_R) {
        cout << INFO << "Making a right diagonal shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if (i == 2 * halfsize - j) {
                    ims.at<uchar>(i, j) = 255;
                } else {
                    ims.at<uchar>(i, j) = 0;
                }
            }
        }
        saveImage(imdname, &ims);
    } else if (shape == LINE_H) {
        cout << INFO << "Making a horizontal line shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if (i == halfsize) {
                    ims.at<uchar>(i, j) = 255;
                } else {
                    ims.at<uchar>(i, j) = 0;
                }
            }
        }
        saveImage(imdname, &ims);
    } else if (shape == DIAG_L) {
        cout << INFO << "Making a left diagonal shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if (i == j) {
                    ims.at<uchar>(i, j) = 255;
                } else {
                    ims.at<uchar>(i, j) = 0;
                }
            }
        }
        saveImage(imdname, &ims);
    } else if (shape == CROSS) {
        cout << INFO << "Making a cross shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if ((i == 2 * halfsize - j) | (i == j)) {
                    ims.at<uchar>(i, j) = 255;
                } else {
                    ims.at<uchar>(i, j) = 0;
                }
            }
        }
        saveImage(imdname, &ims);
    } else if (shape == PLUS) {
        cout << INFO << "Making a plus shape image (" << length << "x" << length << ")..." << endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if ((j == halfsize) | (i == halfsize)) {
                    ims.at<uchar>(i, j) = 255;
                } else {
                    ims.at<uchar>(i, j) = 0;
                }
            }
        }
        saveImage(imdname, &ims);
    } else {
        cout << ERROR << "not a recognized shape." << endl;
        exit(1);
    }
//  imshow(imdname, ims);
//  waitKey(0);
}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " shape halfsize se-name" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), atoi(argv[2]), argv[3]);
    return EXIT_SUCCESS;
}
