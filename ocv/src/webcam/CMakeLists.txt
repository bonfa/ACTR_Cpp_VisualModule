project(opencv)

add_executable(opencv main.cpp LSWMS.h LSWMS.cpp)
target_link_libraries( opencv opencv_highgui opencv_core opencv_objdetect opencv_imgproc)
