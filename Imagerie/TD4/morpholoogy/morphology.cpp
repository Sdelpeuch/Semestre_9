#include "morphology.hpp"

using namespace cv;

void mm(Mat se, Mat ims, Mat imd, void (*pf)(uchar, uchar *)) {

    int height = int(ims.size().height);
    int width = int(ims.size().width);

    int se_h = int(se.size().height);
    int se_w = int(se.size().width);

    if (se_h != se_w) {
        cout << ERROR << "The implemented algorythm work only with square SE image. This one is (" << se_h << "x" << se_w << ")." << endl;
        exit(1);
    }

    int radius = (se_h - 1) / 2; // on se place le cas où l'image est forcément carré à cause de make-se

    // Algorithme dilatation/érosion
    for (int i = 0; i < height; i++) { //ligne
        for (int j = 0; j < width; j++) { //colonne

            int se_i = 0;
            int se_j = 0;

            // Initialisation du pixel final
            imd.at<uchar>(i, j) = ims.at<uchar>(i, j);

            // On traite la morphology (dilatation ou érosion) de type SE de centre (i;j)
            for (int a = (i - radius); a <= (i + radius); a++) {
                for (int b = (j - radius); b <= (j + radius); b++) {

                    // On vérifie qu'on est pas hors zone image
                    if ((a >= 0 && a < height) && (b >= 0 && b < width)) {

                        // Si le pixel dans SE est blanc, alors ca fait partie du shape
                        if (se.at<uchar>(se_i, se_j) == 255) {

                            // Application du min ou max selon l'utilisation de l'érosion ou dilatation
                            pf(ims.at<uchar>(a, b), &imd.at<uchar>(i, j));

                        }
                    }

                    se_j++; // on incrémente la colonne pour la prochaine occurence
                }
                se_j = 0; // on reset à 0 pour la prochaine ligne
                se_i++; // on incrémente la ligne pour la prochaine occurence
            }


        }
    }

}

void maximum(uchar val, uchar *max) {
    *max = (*max > val) ? *max : val;
}

void minimum(uchar val, uchar *min) {
    *min = (*min < val) ? *min : val;
}
