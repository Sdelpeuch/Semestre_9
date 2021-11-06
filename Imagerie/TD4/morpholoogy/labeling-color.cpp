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

    // Chargement de l'image de travail
    Mat ims = imread(imsname, CV_LOAD_IMAGE_GRAYSCALE);
    if (!ims.data) {
        cout << ERROR << "Could not open the image." << imsname << endl;
        exit(1);
    }


    int *roots = new int[ims.total()]; //nombre de pixels de l'image rentrée
    int rows = ims.rows;
    int cols = ims.cols;
    int p = 0;
    int r = -1;
    uchar *ps = ims.data;

    Mat reg_mat = Mat::zeros(ims.size().height, ims.size().width, CV_LOAD_IMAGE_GRAYSCALE);
    Mat color_mat = Mat::zeros(ims.size().height, ims.size().width, CV_8UC3);

    // On parcours l'ensemble de l'image
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

            // Plus d'infos ici :
            // https://homepages.inf.ed.ac.uk/rbf/HIPR2/label.htm

            // On enregistre roots dans la carte de région
            reg_mat.at<uchar>(i,j) = roots[p];

            // ... et on en profite pour créer une image fausse couleurs
            if (roots[p] > 0) { // On prend pas le premier roots qui correspond au fond de l'image
                srand(roots[p]); // On génère un nouveau seed de couleur
                color_mat.at<Vec3b>(i, j)[0] = (uchar) (rand()%255); // B
                color_mat.at<Vec3b>(i, j)[1] = (uchar) (rand()%255); // G
                color_mat.at<Vec3b>(i, j)[2] = (uchar) (rand()%255); // R
            }
        }
    }

    cout << "labeling: " << l << " components detected" << endl;


    saveImage(regname, &reg_mat);
    saveImage(colorname, &color_mat);

    delete[] roots;
    (void) colorname;
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

