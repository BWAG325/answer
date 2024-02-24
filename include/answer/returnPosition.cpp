//
// Created by kon on 2/18/24.
//

#include "returnPosition.h"

ImageProcessing::ImageProcessing(cv::Mat &image) {
    originImage = image;
    decision = 0;
    ImageProcessing::pretreatment();
    ImageProcessing::judgmentLine();
    ImageProcessing::clickBlock();
    ImageProcessing::clickPosition();
}

void ImageProcessing::pretreatment() {
    cv::Mat temporaryImage;
    cv::Mat Mask = cv::imread("src/answer/include/mask/mask.png", 0);
    cv::cvtColor(originImage, temporaryImage, cv::COLOR_BGR2GRAY, 0); //灰度图像
//    cv::adaptiveThreshold(temporaryImage,temporaryImage,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,3,0); //自适应二值化，效果不好
    cv::threshold(temporaryImage, temporaryImage, 180, 255, cv::THRESH_BINARY); // 二值化
    cv::bitwise_and(temporaryImage, Mask, temporaryImage);                  //去掉帧数和分数

    cv::Mat closeCore = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)); //开运算处理click边缘
    cv::morphologyEx(temporaryImage, temporaryImage, cv::MORPH_CLOSE, closeCore);

    cv::Canny(temporaryImage, pretreatmentImage, 100, 300); //边缘检测
    //cv::imwrite("pretreatment.png", pretreatmentImage);
}

void ImageProcessing::judgmentLine() {
    cv::HoughLinesP(pretreatmentImage, lines, 1, CV_PI / 180, 100, 200, 10);
//    double theta = lines[1][1];  //旋转图像
//    cv::Mat rotate = cv::getRotationMatrix2D(cv::Point2d ((pretreatmentImage.cols-1)/2.0,(pretreatmentImage.rows-1)/2.0),(CV_PI/2-theta)*360/CV_PI,1);
//    cv::warpAffine(pretreatmentImage,rotatedImage,rotate,originImage.size());
//    cv::imwrite("rotate.png",rotatedImage);
}

void ImageProcessing::clickBlock() {
//    int i = 0;
    std::vector<cv::Vec<int, 4>> hierarchy;
    cv::findContours(pretreatmentImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE); //轮廓检测，且只记录拐点
    //    for (auto &p: contours) {
//        cv::drawContours(pretreatmentImage, contours, i, 255, -1);  //不用循环
//        i++;
//    }
//    cv::imwrite("clickBlock.png", pretreatmentImage);
}

void ImageProcessing::clickPosition() {
    cv::Point2d clickPoint;
    int count=0;
    double A=0, B=0, C=0, distance = 200, log = 100;
//    A = lines[0][1] - lines[0][3];
//    B = lines[0][2] - lines[0][0];
//    C = lines[0][0] * lines[0][3] - lines[0][2] * lines[0][1];
    for (auto &p: lines) {
        count ++;
        A += p[1] - p[3];
        B += p[2] - p[0];
        C += p[0] * p[3] - p[2] * p[1];
    }
    A = A / count;
    B = B / count;
    C = C / count;
    for (auto &p: contours) {
//        cv::RotatedRect rotateRect = cv::minAreaRect(p);
//        clickPoint = rotateRect.center;
        auto middle = cv::moments(p, false);
        clickPoint.x = middle.m10 / middle.m00;
        clickPoint.y = middle.m01 / middle.m00;
        distance = fabs(A * clickPoint.x + B * clickPoint.y + C) / sqrt(A * A + B * B);
        if (distance > log) distance = log;
        else log = distance;
    }
    std::cout << "distance : " << distance << "   (x,y) " << clickPoint.x << "   " << clickPoint.y << "  C " << -C / B
              << std::endl;
    if (distance < 60 && distance > 0) {
        decision = 1;
        cv::imwrite("clickNow.png", originImage);
    } else decision = 0;
}

//colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
//source install/setup.bash
//ros2 launch answer answer.py