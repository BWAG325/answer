//
// Created by kon on 2/18/24.
//

#ifndef ANSWER_PROCESSIMAGE_H
#define ANSWER_PROCESSIMAGE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

class ImageProcessing {
private:
    cv::Mat originImage;
    cv::Mat lineImage;
    cv::Mat clickBlockImage;
    cv::Mat checkImage;

    void pretreatment();

    void judgmentLine();

    void clickBlock();

public:
    std::vector<cv::Vec4i>lines;
    std::vector<std::vector<cv::Point>> contours;

    ImageProcessing(cv::Mat &image);
};

#endif //ANSWER_PROCESSIMAGE_H
