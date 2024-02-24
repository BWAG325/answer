//
// Created by kon on 2/18/24.
//

#include "returnPosition.h"

ImageProcessing::ImageProcessing(cv::Mat &image, int delay) {
    delayTime = delay;
    originImage = image;
    decision = 0;
    ImageProcessing::pretreatment();
    ImageProcessing::judgmentLine();
    ImageProcessing::clickBlock();
    ImageProcessing::clickPosition();
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

void ImageProcessing::clickPosition() {
    int count = 0;
    double A = 0, B = 0, C = 0, log = 200;

    for (auto &p: lines) {
        count++;
        A += p[1] - p[3];
        B += p[2] - p[0];
        C += p[0] * p[3] - p[2] * p[1];
    }
    A = A / count;
    B = B / count;
    C = C / count;

    for (auto &p: contours) {
        auto middle = cv::moments(p, false);
        clickPoint.x = middle.m10 / middle.m00;
        clickPoint.y = middle.m01 / middle.m00;

        distance = fabs(A * clickPoint.x + B * clickPoint.y + C) / sqrt(A * A + B * B);
        if (fabs(distance - log) < 5) log = distance;
    }

    if (distance < 120 + delayTime && distance > 90 + delayTime) {
        decision = 1;
    } else decision = 0;
}