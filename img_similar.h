//
// Created by 武智辉 on 2017/6/6.
//

#ifndef IMG_SIMILAR_IMG_SIMILAR_H
#define IMG_SIMILAR_IMG_SIMILAR_H
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

extern int FP_SIZE;
extern int FP_BLUR;

bool set_fp_size(int size);

int _get_threshold(Mat img);

Mat get_fp(Mat img);

double calc_similarity(Mat fp1, Mat fp2);

#endif //IMG_SIMILAR_IMG_SIMILAR_H
