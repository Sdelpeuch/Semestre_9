#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define INFO        "\033[32mInfo : \033[0m"
#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define ENDING      ".png"
#define PARAM       2
#define MAX_PIXEL_LEVELS 256

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

    cout << INFO << "Saving matrice to " << imdname << " ..." << endl;
    imwrite(imdname, *image); // sauvegarde
}


void process(const char *imsname, const char *imdname) {

    // Lecture de l'image
    Mat ims = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
    if (!ims.data) {
        cout << ERROR << "Could not open the image." << imsname << endl;
        exit(1);
    }
    int height = int(ims.size().height);
    int width = int(ims.size().width);

    // création des differents histogrames
    int hist[MAX_PIXEL_LEVELS];

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

    // Méthode Otsu en utilisant OpenCV
    Mat im_thr_ocv = Mat::zeros(height, width, ims.type());
    double thr_ocv = threshold(ims, im_thr_ocv, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    // Différence des deux méthodes
    Mat sub = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    subtract(im_thr_manual, im_thr_ocv, sub);

    // Affichage des thresholds
    cout << "manual otsu treeshold = " << thr_manual << endl;
    cout << "ocv otsu treeshold    = " << thr_ocv << endl;

    // Affichage des images
//    imshow("manual_th_ocv", im_thr_manual);
//    imshow("otsu_th_ocv", im_thr_ocv);
//    imshow("diff", sub);

    // Enregistrement des images
//    imwrite("otsu_th.png", im_thr_manual);
//    imwrite("otsu_th_ocv.png", im_thr_ocv);

    saveImage(imdname, &im_thr_manual);

    // On attend le retour utilisateur pour fermer les fenêtres
//    waitKey(0);
}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " imsname\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
