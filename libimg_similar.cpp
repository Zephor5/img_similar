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


double get_similarity(PyObject* img1, PyObject* img2){
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
    // This function needs to be included to pass PyObjects as numpy array ( http://mail.python.org/pipermail/cplusplus-sig/2006-September/011021.html )
//    boost::python::converter::registry::insert( &extract_pyarray, type_id<PyArrayObject>( ) );
    def("get_fp_from_nparr", get_fp);
    def("get_fp_from_str", get_fp_from_str);
    def("calc_similarity", calc_similarity);
    def("get_similarity", get_similarity);
    def("set_fp_size", set_fp_size);
//    def("get_similarity_", get_similarity);
    def("decode_imgbytes", decode_imgbytes);
}
