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
    int radius = (se_h - 1) / 2;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int se_i = 0;
            int se_j = 0;
            imd.at<uchar>(i, j) = ims.at<uchar>(i, j);
            for (int a = (i - radius); a <= (i + radius); a++) {
                for (int b = (j - radius); b <= (j + radius); b++) {
                    if ((a >= 0 && a < height) && (b >= 0 && b < width)) {
                        if (se.at<uchar>(se_i, se_j) == 255) {
                            pf(ims.at<uchar>(a, b), &imd.at<uchar>(i, j));
                        }
                    }
                    se_j++;
                }
                se_j = 0;
                se_i++;
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