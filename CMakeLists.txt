cmake_minimum_required(VERSION 3.7)
project(img_similar)

set(CMAKE_CXX_STANDARD 11)

set(LIB_SOURCE_FILES
        PythonToOpenCV.h
        PythonToOpenCV.cpp
        img_similar.h
        img_similar.cpp
        libimg_similar.cpp
        libimg_similar.h)

set(EXE_SOURCE_FILES
        main.cpp
        img_similar.h
        img_similar.cpp)

INCLUDE_DIRECTORIES(
        /usr/local/opt/opencv3/include
        /usr/local/Cellar/boost/1.64.0_1/include/
        /System/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7/
        /usr/local/lib/python2.7/site-packages/numpy/core/include
)

link_directories(
        /usr/local/opt/opencv3/lib
        /usr/local/Cellar/boost-python/1.64.0/lib
        /System/Library/Frameworks/Python.framework/Versions/2.7/lib
        /usr/local/lib/python2.7/site-packages/numpy/core/lib
)

add_executable(img_similar ${EXE_SOURCE_FILES})
add_library(img_similar_shared SHARED ${LIB_SOURCE_FILES})
#add_library(img_similar_static STATIC ${SOURCE_FILES})

#SET_TARGET_PROPERTIES (img_similar_static PROPERTIES OUTPUT_NAME "img_similar")
#GET_TARGET_PROPERTY (OUTPUT_VALUE img_similar_static OUTPUT_NAME)
#MESSAGE (STATUS "This is the img_similar_static OUTPUT_NAME: " ${OUTPUT_VALUE})

SET_TARGET_PROPERTIES (img_similar_shared PROPERTIES OUTPUT_NAME "img_similar")
GET_TARGET_PROPERTY (OUTPUT_VALUE img_similar_shared OUTPUT_NAME)
MESSAGE (STATUS "This is the img_similar_shared OUTPUT_NAME: " ${OUTPUT_VALUE})

#SET_TARGET_PROPERTIES (img_similar PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES (img_similar_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES (img_similar_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)

SET_TARGET_PROPERTIES (img_similar_shared PROPERTIES VERSION 0.1 SOVERSION 1)

target_link_libraries(img_similar libopencv_core.dylib)
target_link_libraries(img_similar libopencv_imgproc.dylib)
target_link_libraries(img_similar libopencv_highgui.dylib)
target_link_libraries(img_similar libopencv_imgcodecs.dylib)

#target_link_libraries(img_similar_static libopencv_core.dylib)
#target_link_libraries(img_similar_static libopencv_imgproc.dylib)
#target_link_libraries(img_similar_static libopencv_highgui.dylib)
#target_link_libraries(img_similar_static libopencv_imgcodecs.dylib)
#target_link_libraries(img_similar_static libpython2.7.dylib)
#target_link_libraries(img_similar_static libboost_python.a)

target_link_libraries(img_similar_shared libopencv_core.dylib)
target_link_libraries(img_similar_shared libopencv_imgproc.dylib)
target_link_libraries(img_similar_shared libopencv_highgui.dylib)
target_link_libraries(img_similar_shared libopencv_imgcodecs.dylib)
target_link_libraries(img_similar_shared libpython2.7.dylib)
target_link_libraries(img_similar_shared libboost_python.a)
