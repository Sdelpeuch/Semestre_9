#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// This function print in the console the fps, width, height and total frames of the video
void process(const char* vidname) {
    VideoCapture cap(vidname);
    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return;
    }
    int fps = cap.get(CV_CAP_PROP_FPS);
    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
    cout << "FPS: " << fps << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Total Frames: " << totalFrames << endl;
}

// This function display, during the 1000 first frames
void process2(const char* vidname){
    VideoCapture cap(vidname);
    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return;
    }
    int fps = cap.get(CV_CAP_PROP_FPS);
    int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    int totalFrames = cap.get(CV_CAP_PROP_FRAME_COUNT);
    cout << "FPS: " << fps << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "Total Frames: " << totalFrames << endl;
    int i = 0;
    while (i < 1000) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cout << "End of video" << endl;
            break;
        }
        imshow("Video", frame);
        waitKey(1);
        i++;
    }
}

void
usage(const char* s) {
    fprintf(stderr, "Usage: %s imsname\n", s);
    exit(EXIT_FAILURE);
}

#define param 1

int
main(int argc, char* argv[]) {
    if (argc != (param + 1))
        usage(argv[0]);
//    process(argv[1]);
//    proccess2(argv[1]);
//    proccess3(argv[1]);
    return EXIT_SUCCESS;
}
