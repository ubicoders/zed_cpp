// ZEDOpenCVUtils.hpp

#ifndef ZED_OPENCV_UTILS_HPP
#define ZED_OPENCV_UTILS_HPP

#include <sl/Camera.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>

int getOCVtype(sl::MAT_TYPE type);

cv::Mat slMat2cvMat(sl::Mat& input);

cv::cuda::GpuMat slMat2cvMatGPU(sl::Mat& input);

#endif // ZED_OPENCV_UTILS_HPP
