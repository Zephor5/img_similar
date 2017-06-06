//
// Created by 武智辉 on 2017/6/6.
//
#include "img_similar.h"


int FP_SIZE = 64;
int FP_BLUR = 3;


bool set_fp_size(int size){
    if(size < 5 || size > 300){
        return false;
    }
    FP_SIZE = size;
    return true;
}


int _get_threshold(Mat img){
    if (img.channels() != 1) {
        return -1;
    }
    int grey_n[256]={0};
    for (int i=0; i < img.rows; i++){
        for(int j=0; j < img.cols; j++){
            grey_n[img.at<uchar>(i, j)]++;
        }
    }
    int total = (int)img.total();
    float sum = 0;
    for (int t=0 ; t<256 ; t++) sum += t * grey_n[t];
    float sumb = 0;
    int wb = 0;
    int wf = 0;

    float var_max = 0;
    int threshold = 0;

    for (int t=0 ; t<256 ; t++) {
        wb += grey_n[t];               // Weight Background
        if (wb == 0) continue;

        wf = total - wb;                 // Weight Foreground
        if (wf == 0) break;

        sumb += (float) (t * grey_n[t]);

        float mb = sumb / wb;            // Mean Background
        float mf = (sum - sumb) / wf;    // Mean Foreground

        // Calculate Between Class Variance
        float var_between = (float)wb * (float)wf * (mb - mf) * (mb - mf);

        // Check if new maximum found
        if (var_between > var_max) {
            var_max = var_between;
            threshold = t;
        }
    }
    return threshold;
}


Mat get_fp(Mat img){
    Mat dst;
//    img = pbcvt::fromNDArrayToMat(obj);
    cvtColor(img, dst, CV_BGR2GRAY);
    int width = dst.size[1];  // notice 0 for height, 1 for width
    int height = dst.size[0];
    Mat sq_grey, std_grey, bw_img;
    if (width < height){
        sq_grey = dst(Rect(0, (height - width) / 2, width, width));
    }
    else {
        sq_grey = dst(Rect((width - height) / 2, 0, height, height));
    }
    resize(sq_grey, std_grey, Size(FP_SIZE, FP_SIZE));
    int th = _get_threshold(std_grey);
    threshold(std_grey, bw_img, th, 255, THRESH_BINARY);
//    PyObject* ret = pbcvt::fromMatToNDArray(bw_img);
//    return ret;
    return bw_img;
}


double calc_similarity(Mat fp1, Mat fp2){
    Mat ori_diff = ~(fp1 ^ fp2), blur_diff;
    blur(ori_diff, blur_diff, Size(FP_BLUR, FP_BLUR));
    double ori_diffn=0.,blur_diffn=0.;
    for (int i=0; i < ori_diff.rows; i++){
        for(int j=0; j < ori_diff.cols; j++){
            if(ori_diff.at<uchar>(i, j)<80) ori_diffn++;
            if(blur_diff.at<uchar>(i, j)<80) blur_diffn++;
        }
    }
    double similar = 1 - (ori_diffn * 0.2 + blur_diffn * 0.8)/ori_diff.total();
//    cout << "similarity: " << similar << endl;
    return similar;
}
