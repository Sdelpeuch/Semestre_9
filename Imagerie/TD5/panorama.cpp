#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

// Include header files from OpenCV directory
// required to stitch images.
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"


#define PARAM       2


using namespace cv;

using namespace std;


void process(char *ims_name_1, char *ims_name_2){
    Mat img_1 = imread(ims_name_1, CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_2 = imread(ims_name_2, CV_LOAD_IMAGE_GRAYSCALE);
    Mat img_1c = imread(ims_name_1, CV_LOAD_IMAGE_COLOR);
    Mat img_2c = imread(ims_name_2, CV_LOAD_IMAGE_COLOR);
    if(img_1.empty() || img_2.empty())
    {
      cerr<<"Can't read one of the images"<<endl;
    }

    imshow(ims_name_1, img_1c);
    imshow(ims_name_2, img_2c);
    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;

    SurfFeatureDetector detector( minHessian );

    std::vector<KeyPoint> keypoints_1, keypoints_2;

    detector.detect( img_1, keypoints_1 );
    detector.detect( img_2, keypoints_2 );

    //-- Draw keypoints
    Mat img_keypoints_1; Mat img_keypoints_2;

    drawKeypoints( img_1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
    drawKeypoints( img_2, keypoints_2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

    //-- Show detected (drawn) keypoints
    imshow("Descripteur SURF image 1", img_keypoints_1 );
    imshow("Descripteur SURF image 1", img_keypoints_2 );

    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;

    Mat descriptors_1, descriptors_2;

    extractor.compute( img_1, keypoints_1, descriptors_1 );
    extractor.compute( img_2, keypoints_2, descriptors_2 );

    //-- Step 3: Matching descriptor vectors with a brute force matcher
    BFMatcher matcher(NORM_L2);
    std::vector< DMatch > matches;
    matcher.match( descriptors_1, descriptors_2, matches );

    //-- Draw matches
    Mat img_matches;
    drawMatches( img_1, keypoints_1, img_2, keypoints_2, matches, img_matches );

    //-- Show detected matches
    imshow("Appariements Brute Force", img_matches );

    double max_dist = 0; double min_dist = 100;

    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_1.rows; i++ )
    { double dist = matches[i].distance;
      if( dist < min_dist ) min_dist = dist;
      if( dist > max_dist ) max_dist = dist;
    }


    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
    //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
    //-- small)
    //-- PS.- radiusMatch can also be used here.
    std::vector< DMatch > good_matches;

    for( int i = 0; i < descriptors_1.rows; i++ )
    { if( matches[i].distance <= max(3*min_dist, 0.02) )
      { good_matches.push_back( matches[i]); }
    }

    //-- Draw only "good" matches
    //Mat img_matches;
    drawMatches( img_1, keypoints_1, img_2, keypoints_2,
                 good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                 vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    //-- Show detected matches
    imshow( "Appariements seuillés", img_matches );


    std::vector<Point2f> scene1;
    std::vector<Point2f> scene2;

    for( int i = 0; i < int(good_matches.size()); i++ )
    {
      //-- Get the keypoints from the good matches
      scene2.push_back( keypoints_1[ good_matches[i].queryIdx ].pt );
      scene1.push_back( keypoints_2[ good_matches[i].trainIdx ].pt );
    }

    Mat H = findHomography( scene1, scene2, CV_RANSAC );
    cout << H << endl;
    cv::Mat result;


		warpPerspective( img_2c, result, H, cv::Size( img_1.cols+img_2.cols, img_1.rows) );
    imshow( "Image 2 déformée par H", result );

		cv::Mat half(result, cv::Rect(0, 0, img_2.cols, img_2.rows) );
		img_1c.copyTo(half);

    imshow( "Panorama", result);

    /* To remove the black portion after stitching, and confine in a rectangular region*/

		// vector with all non-black point positions
		std::vector<cv::Point> nonBlackList;
		nonBlackList.reserve(result.rows*result.cols);

		// add all non-black points to the vector
		// there are more efficient ways to iterate through the image
		for(int j=0; j<result.rows; ++j)
				for(int i=0; i<result.cols; ++i)
				{
						// if not black: add to the list
						if(result.at<cv::Vec3b>(j,i) != cv::Vec3b(0,0,0))
						{
								nonBlackList.push_back(cv::Point(i,j));
						}
				}

		// create bounding rect around those points
		cv::Rect bb = cv::boundingRect(nonBlackList);

		cv::imshow("Panorama final", result(bb));

    waitKey(0);

}

void usage(const char *s) {
    std::cerr << "Usage: " << s << " ims-name-1 ims-name-2" << endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != (PARAM + 1))
        usage(argv[0]);
    process(argv[1], argv[2]);
    return EXIT_SUCCESS;
}
