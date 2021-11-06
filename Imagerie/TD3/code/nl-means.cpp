#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       3
#define ENDING      ".png"

#define PATCH_SIZE  7
#define SQUARE_SIZE 11

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

void process(int sigma, const char *imsname, const char *imdname) {

    // Ouverture de l'image en niveau de gris
    Mat ims = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
    if (!ims.data) {
        cout << ERROR << "Could not open the image " << imsname << endl;
        exit(1);
    }
    int height = int(ims.size().height);
    int width = int(ims.size().width);

    // Application de l'algorithme d'NL means en respectant les distances inter-patch-pixel
    int square_radius = (SQUARE_SIZE - 1) / 2;
    int patch_radius = (PATCH_SIZE - 1) / 2;
    clock_t start, end;
    double duration_sec;
    Mat nl_means = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    cout << "Applying NL Means Algorithm to \"" << imsname << "\" with sigma="<< sigma << " ..." << endl;
    start = clock();
    for (int i = 0; i < height; i++) { //ligne
        for (int j = 0; j < width; j++) { //colonne

            double numerator = 0.0;
            double denominator = 0.0;

            // On traite le carré autour du pixel
            for (int a = (i - square_radius); a <= (i + square_radius); a++) {
                for (int b = (j - square_radius); b <= (j + square_radius); b++) {

                    double w, d;

                    // On vérifie qu'on est pas hors zone image
                    if ((a >= 0 && a < height) && (b >= 0 && b < width)) {

                        // à partir d'ici :
                        //  - [i:j] est le pixel central
                        //  - [a:b] est le pixel que l'on balade dans le carré 11x11

                        double d_summ = 0.0;
                        // On calcule le magnifique d(P(p), P(q)) en respectant les distances inter-patch-pixel
                        for (int u = -patch_radius; u <= +patch_radius; u++) {
                            for (int v = -patch_radius; v <= +patch_radius; v++) {
                                // On vérifie qu'on est pas hors zone image
                                if ((((i + u) >= 0 && (i + u) < height) && ((j + v) >= 0 && (j + v) < width))
                                    && (((a + u) >= 0 && (a + u) < height) && ((b + v) >= 0 && (b + v) < width))) {

                                    d_summ += pow((ims.at<uchar>((i + u), (j + v)) - ims.at<uchar>((a + u), (b + v))), 2);

                                } else {
                                    // GESTION HORS-IMAGE A REVOIR
                                    d_summ += 0.0;
                                }
                            }
                        }

                        // Calcul final de d(P(p), P(q))
                        d = d_summ / ((double) (PATCH_SIZE * PATCH_SIZE));

                        // Mis a jour du numerator et du denominator
                        w = exp(-d / (2.0 * ((double) (sigma * sigma))));
                        numerator += w * ((double) ims.at<uchar>(a, b));
                        denominator += w;
                    }

                }
            }

            if (denominator > 0.0) // Juste au cas où
                nl_means.at<uchar>(i, j) = (uchar) (numerator / denominator);
            else
                cout << WARNING << "this case should not appear." << endl;

        }
    }
    end = clock();
    duration_sec = double(end - start) / CLOCKS_PER_SEC;
    cout << "Time elapsed while applying NL Means Algorithm : " << duration_sec << "s" << endl;

    saveImage(imdname, &nl_means);

}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " sigma imsname imdname\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(atoi(argv[1]), argv[2], argv[3]);
    return EXIT_SUCCESS;
}
