/**
 *  @file  morphology.hpp
 *  @brief header for morphology.hpp that implements functions for mathematical
 *         image processing, in particular dilation and erosion basis
 */

#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

#define INFO        "\033[32mInfo : \033[0m"
#define WARNING     "\033[33mWarning : \033[0m"
#define ERROR       "\033[31mError : \033[0m"
#define ENDING      ".png"

using namespace cv;
using namespace std;

/**
 * @brief  compute a morphological dilation or erosion on a grayscale image
 *         with a given structuring element. Dilation or erosion 
 *         processing depends on an order function  defined by the pointer pf
 * @param  se: the structuring element shape (created with make-se)
 * @param  ims: the input image source to process
 * @param  imd: the destination image
 * @param  pf: a pointer on a ordering function
 */
void mm(cv::Mat se, cv::Mat ims, cv::Mat imd, void (*pf)(uchar, uchar *));


/**
 * @brief  ordering function, if val is greater than max then update max
 * @param  val: the input value
 * @param  max: the value to update
 */
void maximum(uchar val, uchar *max);

/**
 * @brief  ordering function, if val is lesser than min then update min
 * @param  val: the input value
 * @param  max: the value to update
 */
void minimum(uchar val, uchar *min);


