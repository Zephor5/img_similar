//
// Created by 武智辉 on 2017/6/6.
//

#include "libimg_similar.h"


Mat decode_imgbytes(PyObject* o){
    if(!PyString_CheckExact(o)){
        pbcvt::failmsg("not str");
        throw_error_already_set();
    }
    char* s = PyString_AsString(o);
    u_long n = (u_long)PyString_Size(o);
    std::vector<uchar> sv(s, s + n);
    return imdecode(sv, IMREAD_COLOR);
}


Mat get_fp_from_str(PyObject* o){
    Mat img=decode_imgbytes(o);
    return get_fp(img);
}

list get_fps(PyObject* o){
    std::string* fps;
    list res;
    fps = (std::string*)std::malloc(sizeof(std::string) * 4);
    Mat img = decode_imgbytes(o);
    int blur_size=(img.size[0] > img.size[1] ? img.size[0] : img.size[1]) / 20;
    blur(img, img, Size(blur_size, blur_size));
    set_fp_size(PART_SIZE * 2);
    Mat fp = get_fp(img);
    get_fp_strs(fp, fps);
    for(int i=0; i < 4; i++){
        res.append(str(fps[i]));
    }
    free(fps);
    return res;
}


double get_similarity(PyObject* img1, PyObject* img2, int fp_size=64){
    set_fp_size(fp_size);
    return calc_similarity(get_fp(decode_imgbytes(img1)), get_fp(decode_imgbytes(img2)));
}


static void init_ar(){
    Py_Initialize();

    import_array();
    return NUMPY_IMPORT_ARRAY_RETVAL;
}


BOOST_PYTHON_MODULE(img_similar){
    //using namespace XM;
    init_ar();

    //initialize converters
    to_python_converter<cv::Mat,
            pbcvt::matToNDArrayBoostConverter>();
    pbcvt::matFromNDArrayBoostConverter();
    def("get_similarity", get_similarity, (arg("img1"), arg("img1"), arg("fp_size")=64));
    def("get_fps", get_fps);
}
