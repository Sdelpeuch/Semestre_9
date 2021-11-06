#include <iostream>
#include <cstdlib>
#include <math.h>

#include <opencv2/opencv.hpp>

#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define PARAM       1

using namespace cv;
using namespace std;

void process(const char *imsname) {

    Mat ims = imread(imsname, CV_LOAD_IMAGE_COLOR);
    if (!ims.data) {
        cout << ERROR << "Could not open the image." << imsname << endl;
        exit(1);
    }
    int height = int(ims.size().height);
    int width = int(ims.size().width);

    //conversion en niveau de gris
    cvtColor(ims, ims, CV_BGR2GRAY);

    //creation de l'image equilibree
    Mat eq_main = Mat::zeros(height, width, ims.type());

    int I_max = 256;
    if (!ims.data) {
        cout << "Could not open the image " << imsname << endl;
        exit(1);
    }

    //création des differents histogrames
    int hist[I_max];
    float hist_n[I_max];
    int hist_c[I_max];
    float hist_cn[I_max];


    //equilibrage histogramme à la main

    int temp;
    //initialisation des tableaux
    for(int i = 0; i < I_max; i++){
        hist_c[i] = 0;
        hist[i] = 0;
        hist_cn[i] = 0.0f;
        hist_n[i] = 0.0f;
    }

    //creation de l'histogramme
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            temp = int(ims.at<uchar>(i, j));
            hist[temp] ++;
        }
    }

    //determination des histogrammes normalises, cumules et cumules normalises
    for(int i = 0; i < I_max; i++){
        hist_n[i] = hist[i]/(float(height*width));
        if (i==0){
            hist_c[i] = hist[i];
            hist_cn[1] = hist_n[i];
        }
        else{
            hist_c[i] = hist_c[i-1] + hist[i];
            hist_cn[i] = hist_cn[i-1] + hist_n[i];
        }
    }

    //construction de l'image equilibree
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            temp = (I_max)*hist_cn[int(ims.at<uchar>(i, j))];
            eq_main.at<uchar>(i, j) = uchar(temp);
        }
    }


    Mat eq_ocv;

    equalizeHist(ims, eq_ocv);
//    imshow(imsname, ims);
//    imshow("eq_main", eq_main);
//    imshow("eq_ocv", eq_ocv);

    Mat diff = eq_main-eq_ocv;
//    imshow("Difference", diff);

    imwrite("eq-ocv.png", eq_ocv); // sauvegarde
    imwrite("eq.png", eq_main); // sauvegarde
    imwrite("diff.png", diff); // sauvegarde

    waitKey(0);

}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " imsname\n" << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1]);
    return EXIT_SUCCESS;
}
