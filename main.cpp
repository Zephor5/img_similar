
#include <iostream>
#include "img_similar.h"

using namespace std;


int main(int argc, char *argv[]){
    if (argc < 3){
        return -1;
    }
    Mat img1 = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (img1.empty())
        return -1;
    Mat img2 = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);
    if (img2.empty())
        return -1;
    int blur1=(img1.size[0] > img1.size[1] ? img1.size[0] : img1.size[1]) / 20;
    int blur2=(img2.size[0] > img2.size[1] ? img2.size[0] : img2.size[1]) / 20;
    blur(img1, img1, Size(blur1, blur1));
    blur(img2, img2, Size(blur2, blur2));
    set_fp_size(8);
    Mat fp1 = get_fp(img1);
    Mat fp2 = get_fp(img2);
    double si = calc_similarity(fp1, fp2);
    cout << "similarity: " << si << endl;
    cout << fp1 << endl;
    cout << fp2 << endl;
    namedWindow("f1");
    imshow("f1", img1);
    namedWindow("f2");
    imshow("f2", img2);
    waitKey(0);
    return 0;
}
