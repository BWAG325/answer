//
// Created by kon on 2/18/24.
//

#include "processImage.h"

ImageProcessing::ImageProcessing(cv::Mat &image) {
    originImage = image;
    ImageProcessing::pretreatment();
    ImageProcessing::judgmentLine();
    ImageProcessing::clickBlock();
}

void ImageProcessing::pretreatment() {
    cv::Mat temporaryImage;
    cv::cvtColor(originImage, temporaryImage, cv::COLOR_BGR2HSV, 0);

    cv::inRange(temporaryImage, cv::Scalar(0, 0, 221), cv::Scalar(180, 30, 255), lineImage);
    cv::inRange(temporaryImage, cv::Scalar(78, 43, 46), cv::Scalar(124, 255, 255), clickBlockImage);

    cv::Mat Core1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(clickBlockImage, clickBlockImage, cv::MORPH_OPEN, Core1);

    cv::Canny(lineImage, lineImage, 30, 10);
    cv::Canny(clickBlockImage, clickBlockImage, 30, 10);
}

void ImageProcessing::judgmentLine() {
    cv::HoughLinesP(lineImage, lines, 1, CV_PI / 180, 100, 150, 10);
}

void ImageProcessing::clickBlock() {
    std::vector<cv::Vec<int, 4>> hierarchy;
    cv::findContours(clickBlockImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
}