#include <iostream>
#include <sl/Camera.hpp>
#include <opencv2/opencv.hpp>
#include "utils_perf.hpp"
#include "utils_zed.hpp"
#include "zed_cam.hpp"
#include "aruco_detection.hpp"
#include "udp_server.hpp"
#include <flatbuffers/flatbuffers.h>
#include "definitions/aruco_msgs_generated.h"

using namespace sl;

std::vector<uint8_t> packArUcoMarkerInfo(const std::vector<int> &left_marker_ids, const std::vector<std::vector<cv::Point2f>> &left_marker_corners,
                                         const std::vector<int> &right_marker_ids, const std::vector<std::vector<cv::Point2f>> &right_marker_corners);

int main(int argc, char **argv)
{

    UDPServer udp_server(12345);
    if (!udp_server.initialize())
        return 1;

    TimerTicTok timer;
    ArucoDetectorWrapper left_ar_detector;
    ArucoDetectorWrapper right_ar_detector;

    ZEDCam zed_cam; // true indicates that depth information is needed
    if (!zed_cam.openCam())
        return 1;
    char key = ' ';
    while (key != 'q')
    {

        // Grab the ZED camera
        if (!zed_cam.updateCam())
        {
            std::cerr << "Failed to grab the ZED camera" << std::endl;
            break;
        }

        // timer.update();
        // timer.pprint();

        cv::Mat left_image, right_image;
        cv::cvtColor(zed_cam.getLeftImage(), left_image, cv::COLOR_BGRA2BGR);
        cv::cvtColor(zed_cam.getRightImage(), right_image, cv::COLOR_BGRA2BGR);

        // aruco detection
        left_ar_detector.detectMarkers(left_image);
        right_ar_detector.detectMarkers(right_image);
        


        udp_server.receiveMessage();
        // udp_server.sendMessage("Hello from ZED camera123123123123123");

        // Pack the ArUco marker information into a FlatBuffer message
        auto packed_message = packArUcoMarkerInfo(left_ar_detector.getMarkerIds(), left_ar_detector.getMarkerCorners(),
                                                  right_ar_detector.getMarkerIds(), right_ar_detector.getMarkerCorners());

        // Send the packed message using sendMessageFB
        udp_server.sendMessageFB(reinterpret_cast<const char *>(packed_message.data()), packed_message.size());

        // arucoDetector.drawMarkers(left_image);
        // std::vector<std::pair<int, cv::Point2f>> left_marker_info = left_ar_detector.get_xy_info();
        // std::vector<std::pair<int, cv::Point2f>> right_marker_info = right_ar_detector.get_xy_info();
        // arucoDetector.print_xy_info(left_image);

        // cv::Mat depth_image_ocv = zed_cam.getDepthMapImage();

        // if (!left_image.empty()) cv::imshow("Left Image", left_image);
        // if (!depth_image_ocv.empty()) cv::imshow("Depth Image", depth_image_ocv);

        key = cv::waitKey(1);
    }

    zed_cam.closeCam();
    return 0;
}

std::vector<uint8_t> packArUcoMarkerInfo(const std::vector<int> &left_marker_ids, const std::vector<std::vector<cv::Point2f>> &left_marker_corners,
                                         const std::vector<int> &right_marker_ids, const std::vector<std::vector<cv::Point2f>> &right_marker_corners)
{
    // Create a FlatBufferBuilder
    flatbuffers::FlatBufferBuilder builder;

    // Create vectors of Markers for left and right images
    std::vector<flatbuffers::Offset<ArUco::Marker>> left_markers;
    std::vector<flatbuffers::Offset<ArUco::Marker>> right_markers;

    // Populate left_markers vector
    for (size_t i = 0; i < left_marker_ids.size(); ++i)
    {
        std::vector<ArUco::Point2D> corners;
        for (const auto &corner : left_marker_corners[i])
        {
            corners.emplace_back(corner.x, corner.y);
        }
        auto corners_offset = builder.CreateVectorOfStructs(corners);
        left_markers.push_back(ArUco::CreateMarker(builder, left_marker_ids[i], corners_offset));
    }

    // Populate right_markers vector
    for (size_t i = 0; i < right_marker_ids.size(); ++i)
    {
        std::vector<ArUco::Point2D> corners;
        for (const auto &corner : right_marker_corners[i])
        {
            corners.emplace_back(corner.x, corner.y);
        }
        auto corners_offset = builder.CreateVectorOfStructs(corners);
        right_markers.push_back(ArUco::CreateMarker(builder, right_marker_ids[i], corners_offset));
    }

    // Create the ImageMarkers for left and right images
    auto left_image_markers = ArUco::CreateImageMarkers(builder, builder.CreateString("left_image"), builder.CreateVector(left_markers));
    auto right_image_markers = ArUco::CreateImageMarkers(builder, builder.CreateString("right_image"), builder.CreateVector(right_markers));

    // Create StereoImageMarkers
    auto stereo_markers = ArUco::CreateStereoImageMarkers(builder, left_image_markers, right_image_markers);

    // Finish the FlatBuffer
    ArUco::FinishStereoImageMarkersBuffer(builder, stereo_markers);

    // Return the serialized data as a vector of bytes
    return std::vector<uint8_t>(builder.GetBufferPointer(), builder.GetBufferPointer() + builder.GetSize());
}