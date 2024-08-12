// zed_cam_gpu.hpp

#ifndef ZED_CAM_HPP
#define ZED_CAM_HPP

#include <sl/Camera.hpp>
#include <opencv2/opencv.hpp>
#include "utils_zed.hpp"

class ZEDCam {
public:
    ZEDCam();
    ~ZEDCam();

    bool openCam();
    bool updateCam();
    void closeCam();

    cv::Mat getLeftImage();
    cv::Mat getRightImage();
    sl::Mat getDepthMapGPU();
    cv::Mat getDepthMapImage();
    sl::Mat getPointCloud();

private:
    sl::InitParameters init_params;
    sl::RuntimeParameters runtime_parameters;
    sl::Camera zed;
    sl::Resolution image_size;

    sl::Mat sl_image_left;
    sl::Mat sl_image_right;
    sl::Mat sl_depth_map_gpu;
    sl::Mat sl_point_cloud_gpu;

    cv::cuda::GpuMat depth_image_ocv_gpu;
    cv::Mat depth_image_ocv;
};

#endif // ZED_CAM_HPP
