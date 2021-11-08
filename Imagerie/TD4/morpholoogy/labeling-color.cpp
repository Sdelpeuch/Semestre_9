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

