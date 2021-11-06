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

    cout << "Saving matrice to " << imdname << " ..." << endl;
    imwrite(imdname, *image); // sauvegarde
}

void process(int sigma_s, int sigma_g, const char *imsname, const char *imdname) {

    // Ouverture de l'image en niveau de gris
    Mat ims = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
    if (!ims.data) {
        cout << ERROR << "Could not open the image " << imsname << endl;
        exit(1);
    }
    int height = int(ims.size().height);
    int width = int(ims.size().width);


    // Détermination de la taille max du voisinage en fonction de sigma_s
    // On en profite pour enregistrer le calcul des coefficients de Gs
    int i_max = (height > width) ? height : width;
    double Gs[i_max]; // Tableau de valeurs de Gs
    int radius = i_max; // Au cas où on atteint jamais le seuillage min

    for (int i = 0; i < i_max; i++) {
        Gs[i] = exp(-(i * i) / (2.0 * (sigma_s * sigma_s)));
        //cout << "x="<<i<<"\tGs="<<tab_Gs[i]<<endl;
        if (Gs[i] <= SEUILLAGE) {
            radius = i; // à diviser par deux ??
            break;
        }
    }
    cout << "Max distance value between two pixels for sigma_s=" << sigma_s << " and Gs_min=" << SEUILLAGE << " is radius=" << radius << "." << endl;

    // Pré-calcul de tout les coefficients possible de Gg (Intensité de 0 à 255)
    double Gg[GRAYSCALE]; // Tableau de valeurs de Gs
    for (int i = 0; i < GRAYSCALE; i++) {
        Gg[i] = exp(-(i * i) / (2.0 * (sigma_g * sigma_g)));
        //cout << "I=" << i << "\tGg=" << Gg[i] << endl;
    }

    // On applique le filtre bilatéral
    clock_t start, end;
    double duration_sec;
    Mat bilateral = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    cout << "Applying Bilateral filter to \"" << imsname << "\" with sigma_s="<< sigma_s << " and sigma_g="<< sigma_g << " ..." << endl;
    start = clock();
    for (int i = 0; i < height; i++) { //ligne
        for (int j = 0; j < width; j++) { //colonne

            double numerator = 0.0;
            double denominator = 0.0;

            // On traite le carré autour du pixel
            for (int a = (i - radius); a <= (i + radius); a++) {
                for (int b = (j - radius); b <= (j + radius); b++) {

                    // On vérifie qu'on est pas hors zone image
                    if ((a >= 0 && a < height) && (b >= 0 && b < width)) {

                        // On calcule la distance entre les deux pixels
                        int distance = (int) sqrt(pow((i - a), 2) + pow((j - b), 2));

                        // On vérifie qu'on est bien dans le cercle dessiné par radius autour du point central (i;j)
                        if (distance <= radius) {
                            //cout << "distance between ("<<i<<";"<<j<<") and ("<<a<<";"<<b<<") is "<<distance<<"."<<endl;

                            int diff_I = (int)abs(ims.at<uchar>(i, j) - ims.at<uchar>(a, b));
                            numerator += (Gs[distance] * Gg[diff_I] * (double) ims.at<uchar>(a, b));
                            denominator += (Gs[distance] * Gg[diff_I]);

                        }
                    }
                }
            }

            if (denominator>0.0) // Juste au cas où
                bilateral.at<uchar>(i, j) = (uchar)(numerator/denominator);
            else
                bilateral.at<uchar>(i, j) = ims.at<uchar>(i, j);

        }
    }
    end = clock();
    duration_sec = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time elapsed while applying bilateral filter : " << duration_sec << "s" << endl;


    saveImage(imdname, &bilateral);


}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " sigma_s sigma_g ims imd\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), atoi(argv[2]), argv[3], argv[4]);
    return EXIT_SUCCESS;
}
