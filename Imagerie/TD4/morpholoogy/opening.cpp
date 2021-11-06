#include <iostream>
#include <cstdlib>

#include "morphology.hpp"

#define PARAM       3

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


void process(const char *sename, const char *imsname, const char *imdname) {

    // Chargement de l'image de travail
    Mat ims = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
    if (!ims.data) {
        cout << ERROR << "Could not open the image." << imsname << endl;
        exit(1);
    }

    // Chargement du shape SE
    Mat se = imread(sename, CV_LOAD_IMAGE_GRAYSCALE);
    if (!se.data) {
        cout << ERROR << "Could not open the image." << sename << endl;
        exit(1);
    }

    // Préparation d'une nouvelle matrice pour le résultat
    const int height = int(ims.size().height);
    const int width = int(ims.size().width);
    Mat imd = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);
    Mat imd2 = Mat::zeros(height, width, CV_LOAD_IMAGE_GRAYSCALE);

    // Application de la dilatation
    clock_t start, end;
    double duration_sec;
    cout << INFO << "Applying Opening to \"" << imsname << "\" with SE sharp \"" << sename << "\"..." << endl;
    start = clock();
    mm(se, ims, imd, &minimum); // erosion ...
    mm(se, imd, imd2, &maximum); // ... puis dilatation
    end = clock();
    duration_sec = double(end - start) / CLOCKS_PER_SEC;
    cout << INFO << "Time elapsed while applying Opening : " << duration_sec << "s" << endl;


    // Enregistrement de l'image
    saveImage(imdname, &imd2);

}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " im-se ims imd" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], argv[2], argv[3]);
    return EXIT_SUCCESS;
}

