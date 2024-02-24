//
// Created by kon on 2/18/24.
//

#ifndef ANSWER_RETURNPOSITION_H
#define ANSWER_RETURNPOSITION_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <cmath>

class ImageProcessing {
private:
    int delayTime;

    cv::Mat originImage;
    cv::Mat lineImage;
    cv::Mat clickBlockImage;
    cv::Mat checkImage;

    std::vector<cv::Vec4i>lines;
    std::vector<std::vector<cv::Point>> contours;

    void pretreatment();

    void judgmentLine();

    void clickBlock();

    void clickPosition();
public:
    int decision;
    double distance;
    cv::Point2d clickPoint;

    ImageProcessing(cv::Mat &image,int delay);
};

#endif //ANSWER_RETURNPOSITION_H
