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


//    // Pour une raison inconnu, le passage suivant entraine un coredump. Optimisation de compilation à éviter ?
//    // En fait, après création de "Mat temp", la variable "imdname" se vide sans aucune raison... problème mémoire ?
//    Mat temp;
//    temp = imread(imdname, CV_LOAD_IMAGE_GRAYSCALE);
//    cout << WARNING << imdname << endl;
//    if (temp.data)
//        cout << WARNING << imdname << " already exist and will be erased." << endl;


    cout << "Saving matrice to " << imdname << " ..." << endl;
    imwrite(imdname, *image); // sauvegarde
}

void process(const char *imsname, int radius, int constantinople) {

    // Chargement de l'image
    Mat image = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
    if (!image.data) {
        cout << ERROR << "Could not open the image." << imsname << endl;
        exit(1);
    }

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

    // Via opencv en utilisant la moyenne
    Mat th_ocv = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    adaptiveThreshold(image, th_ocv, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, (2 * radius + 1), constantinople);

    // Différence des deux méthodes
    Mat sub = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    subtract(th, th_ocv, sub);

    // Via opencv en utilisant la gaussienne
    Mat th_ocv_gauss = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    adaptiveThreshold(image, th_ocv_gauss, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, (2 * radius + 1), constantinople);

    saveImage("th.png", &th);
    saveImage("th-ocv-mean.png", &th_ocv);
    saveImage("diff.png", &sub);
    saveImage("th-ocv-gauss.png", &th_ocv_gauss);
}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " imsname radius const\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], atoi(argv[2]), atoi(argv[3]));
    return EXIT_SUCCESS;
}
