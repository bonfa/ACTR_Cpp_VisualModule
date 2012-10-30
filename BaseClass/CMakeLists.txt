project(opencv)

add_executable(opencv BaseClass.h BaseClass.cpp)
target_link_libraries( opencv opencv_highgui opencv_core opencv_objdetect opencv_imgproc)
