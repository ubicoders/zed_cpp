#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>

class ArucoDetectorWrapper {
public:
    ArucoDetectorWrapper(int dictionaryId = cv::aruco::DICT_4X4_1000) {
        dictionary = cv::aruco::getPredefinedDictionary(dictionaryId);
        detectorParams = cv::aruco::DetectorParameters();
        detector = cv::aruco::ArucoDetector(dictionary, detectorParams);
    }

    void detectMarkers(cv::Mat& image) {
        detector.detectMarkers(image, markerCorners, markerIds, rejectedCandidates);
    }

    void drawMarkers(cv::Mat& image) const {
        if (!markerIds.empty()) {
            cv::aruco::drawDetectedMarkers(image, markerCorners, markerIds);
        }
    }

    std::vector<int> getMarkerIds() const {
        return markerIds;
    }

    std::vector<std::vector<cv::Point2f>> getMarkerCorners() const {
        return markerCorners;
    }

    std::vector<std::pair<int, cv::Point2f>> get_xy_info() const {
        std::vector<std::pair<int, cv::Point2f>> marker_xy_list;

        for (size_t i = 0; i < markerIds.size(); ++i) {
            // Calculate the center (x, y) coordinates of the marker
            float center_x = 0.0f;
            float center_y = 0.0f;
            for (const auto& corner : markerCorners[i]) {
                center_x += corner.x;
                center_y += corner.y;
            }
            center_x /= 4.0;  // Average of the 4 corner points
            center_y /= 4.0;  // Average of the 4 corner points

            // Append the marker ID and its center coordinates to the list
            marker_xy_list.emplace_back(markerIds[i], cv::Point2f(center_x, center_y));
        }

        return marker_xy_list;
    }

    void print_xy_info(cv::Mat& img) const {
        std::vector<std::pair<int, cv::Point2f>> marker_xy_list = get_xy_info();
        for (const auto& info : marker_xy_list) {
            std::cout << "Marker ID: " << info.first << ", Center: (" << info.second.x << ", " << info.second.y << ")" << std::endl;
            cv::Point2f center = info.second;
            int size = 10; // Size of the rectangle
            cv::rectangle(img, cv::Point2f(center.x - size, center.y - size), 
                        cv::Point2f(center.x + size, center.y + size), 
                        cv::Scalar(255, 255, 0), 2); // Cyan color
        }

    }

private:
    cv::aruco::Dictionary dictionary;
    cv::aruco::DetectorParameters detectorParams;
    cv::aruco::ArucoDetector detector;
    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners;
    std::vector<std::vector<cv::Point2f>> rejectedCandidates;
};