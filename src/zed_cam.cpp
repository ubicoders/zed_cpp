// zed_cam.cpp

#include "zed_cam.hpp"
using namespace sl;

ZEDCam::ZEDCam() {
    init_params.camera_resolution = sl::RESOLUTION::HD720;
    init_params.camera_fps = 60;
    init_params.depth_mode = sl::DEPTH_MODE::PERFORMANCE;
    init_params.coordinate_units = sl::UNIT::MILLIMETER;

    image_size = zed.getCameraInformation().camera_configuration.resolution;
    sl_depth_map_gpu = sl::Mat(image_size.width, image_size.height, MAT_TYPE::U8_C4, sl::MEM::GPU); 
}

ZEDCam::~ZEDCam() {
    closeCam();
}

bool ZEDCam::openCam() {
    sl::ERROR_CODE err = zed.open(init_params);
    if (err != sl::ERROR_CODE::SUCCESS) {
        std::cerr << "Failed to open the ZED camera: " << sl::toString(err) << std::endl;
        return false;
    }
    return true;
}

bool ZEDCam::updateCam() {
    return (zed.grab(runtime_parameters) == sl::ERROR_CODE::SUCCESS);
}

cv::Mat ZEDCam::getLeftImage() {
    zed.retrieveImage(sl_image_left, sl::VIEW::LEFT, MEM::CPU, image_size);
    return slMat2cvMat(sl_image_left).clone();
}

cv::Mat ZEDCam::getRightImage() {
    zed.retrieveImage(sl_image_right, sl::VIEW::LEFT , MEM::CPU, image_size);
    return slMat2cvMat(sl_image_right).clone();
}

sl::Mat ZEDCam::getDepthMapGPU() {
    zed.retrieveImage(sl_depth_map_gpu, VIEW::DEPTH, MEM::GPU, image_size);
    return sl_depth_map_gpu;
}

cv::Mat ZEDCam::getDepthMapImage(){
    getDepthMapGPU();
    depth_image_ocv_gpu = slMat2cvMatGPU(sl_depth_map_gpu);
    depth_image_ocv_gpu.download(depth_image_ocv);
    return depth_image_ocv.clone();
}

sl::Mat ZEDCam::getPointCloud() {    
    zed.retrieveMeasure(sl_point_cloud_gpu, MEASURE::XYZRGBA, MEM::GPU, image_size);
    return sl_point_cloud_gpu;  
}

void ZEDCam::closeCam() {
    zed.close();
    sl_depth_map_gpu.free();
    sl_point_cloud_gpu.free();    
}