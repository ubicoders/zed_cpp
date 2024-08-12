#include <iostream>
#include <sl/Camera.hpp>
#include <opencv2/opencv.hpp>
#include "utils_perf.hpp"
#include "utils_zed.hpp"
#include "zed_cam.hpp"
#include "aruco_detection.hpp"
using namespace sl;


int main(int argc, char **argv) {
    ZEDCam zed_cam; // true indicates that depth information is needed
    
    ArucoDetectorWrapper left_ar_detector;
    ArucoDetectorWrapper right_ar_detector;


    if (!zed_cam.openCam()) {
        return 1; // Quit if camera fails to open
    }

    TimerTicTok timer;
    char key = ' ';
    while (key != 'q') {

        // Grab the ZED camera
        if (!zed_cam.updateCam()) {
            std::cerr << "Failed to grab the ZED camera" << std::endl;
            break;
        }

        timer.update();
        timer.pprint();

        cv::Mat left_image, right_image;
        cv::cvtColor(zed_cam.getLeftImage(),left_image, cv::COLOR_BGRA2BGR);
        cv::cvtColor(zed_cam.getRightImage(),right_image, cv::COLOR_BGRA2BGR);

        // aruco detection
        left_ar_detector.detectMarkers(left_image);
        right_ar_detector.detectMarkers(right_image);
        //arucoDetector.drawMarkers(left_image);
        std::vector<std::pair<int, cv::Point2f>> left_marker_info = left_ar_detector.get_xy_info();
        std::vector<std::pair<int, cv::Point2f>> right_marker_info = right_ar_detector.get_xy_info();
        //arucoDetector.print_xy_info(left_image);
        
        
        //cv::Mat depth_image_ocv = zed_cam.getDepthMapImage();
        
        //if (!left_image.empty()) cv::imshow("Left Image", left_image);
        //if (!depth_image_ocv.empty()) cv::imshow("Depth Image", depth_image_ocv);
        

        key = cv::waitKey(1);
    }

    zed_cam.closeCam();
    return 0;
}