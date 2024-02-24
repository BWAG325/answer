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
    cv::Mat originImage;
    cv::Mat pretreatmentImage;
    cv::Mat rotatedImage;

    std::vector<cv::Vec4i>lines;
    std::vector<std::vector<cv::Point>> contours;

    int decision;

    void pretreatment();

    void judgmentLine();

    void clickBlock();

    void clickPosition();

public:
    ImageProcessing(cv::Mat &image);
};

#endif //ANSWER_RETURNPOSITION_H
