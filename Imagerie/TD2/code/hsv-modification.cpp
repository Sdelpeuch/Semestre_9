#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       5
#define ENDING      ".png"

using namespace cv;
using namespace std;

bool hasEnding(std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void process(int h, int s, int v, const char *imsname, const char *imdname) {

    // Chargement de 'limage
    Mat image = imread(imsname, CV_LOAD_IMAGE_COLOR);
    if (!image.data) {
        cout << ERROR << "Could not open the image." << imsname << endl;
        exit(1);
    }

    int height = int(image.size().height);
    int width = int(image.size().width);
    Mat image_hsv;
    cvtColor(image, image_hsv, CV_BGR2HSV);

    // Affichage des canaux H, S et V dans 3 images monochromes
    Mat im_h = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    Mat im_s = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    Mat im_v = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            im_h.at<uchar>(i, j) = image_hsv.at<Vec3b>(i, j)[0];
            im_s.at<uchar>(i, j) = image_hsv.at<Vec3b>(i, j)[1];
            im_v.at<uchar>(i, j) = image_hsv.at<Vec3b>(i, j)[2];
        }
    }
    imshow("h", im_h);
    imshow("s", im_s);
    imshow("v", im_v);

    // Modifiation de l'image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image_hsv.at<Vec3b>(i, j)[0] = im_h.at<uchar>(i, j) + h;
            image_hsv.at<Vec3b>(i, j)[1] = im_s.at<uchar>(i, j) + s;
            image_hsv.at<Vec3b>(i, j)[2] = im_v.at<uchar>(i, j) + v;
        }
    }

    Mat image2;
    cvtColor(image_hsv, image2, CV_HSV2BGR);

    // On vérifie le nom rentré par l'utilisateur
    if (!hasEnding(imdname, ENDING)) { // On vérifie que ca se termine bien par .png sinon OpenCV plante
        cout << WARNING << "name provide is not complete, adding \"" << ENDING << "\"." << endl;
        imdname = string(imdname).append(ENDING).c_str();
    }

//    // Pour une raison inconnu, le passage suivant entraine un coredump. Optimisation de compilation à éviter ?
//    // En fait, après création de "Mat temp", la variable "imdname" se vide sans aucune raison... problème mémoire ?
//    Mat temp;
//    temp = imread(imdname, CV_LOAD_IMAGE_COLOR);
//    if (temp.data)
//        cout << WARNING << imdname << " already exist and will be erased." << endl;

    imwrite(imdname, image2); // sauvegarde

    waitKey(0);
    destroyAllWindows();

}

void usage(const char *s) {
    std::cerr << ERROR << "Usage: " << s << " h s v ims imd\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), argv[4], argv[5]);
    return EXIT_SUCCESS;
}
