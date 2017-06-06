//
// Created by 武智辉 on 2017/6/6.
//

#ifndef IMG_SIMILAR_LIBIMG_SIMILAR_H
#define IMG_SIMILAR_LIBIMG_SIMILAR_H
#define PY_ARRAY_UNIQUE_SYMBOL pbcvt_ARRAY_API
#define BOOST_PYTHON_SOURCE

#include "img_similar.h"
#include <Python.h>
#include <boost/python.hpp>
#include "PythonToOpenCV.h"

using namespace boost::python;
using namespace cv;

Mat decode_imgbytes(PyObject* o);
Mat get_fp_from_str(PyObject* o);
double get_similarity(PyObject* img1, PyObject* img2);

#endif //IMG_SIMILAR_LIBIMG_SIMILAR_H
