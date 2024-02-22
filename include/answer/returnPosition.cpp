//
// Created by kon on 2/18/24.
//

#include "returnPosition.h"

ImageProcessing::ImageProcessing(cv::Mat &image) {
    originImage = image;
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

    cv::Canny(temporaryImage, pretreatmentImage, 3, 1, 3); //边缘检测
    cv::imwrite("pretreatment.png", pretreatmentImage);
}

void ImageProcessing::judgmentLine() {
    cv::HoughLines(pretreatmentImage, lines, 1, CV_PI / 180, 250);

//    double rho = lines[0][1],theta = lines[1][1];  //旋转图像，没用上
//    cv::Mat rotate = cv::getRotationMatrix2D(cv::Point2d ((pretreatmentImage.cols-1)/2.0,(pretreatmentImage.rows-1)/2.0),-(theta*360)/CV_PI,1);
//    cv::warpAffine(pretreatmentImage,pretreatmentImage,rotate,originImage.size());
//    cv::imwrite("rotate.png",pretreatmentImage);
//
//    cv::Point pt1, pt2;
//    double a = cos(theta), b = sin(theta);
//    double x0 = a * rho, y0 = b * rho;
//    pt1.x = cvRound(x0 + 1000 * (-b));
//    pt1.y = cvRound(y0 + 1000 * (a));
//    pt2.x = cvRound(x0 - 1000 * (-b));
//    pt2.y = cvRound(y0 - 1000 * (a));
//    line(originImage, pt1, pt2, cv::Scalar(255, 255, 0), 1, cv::LINE_AA);
//    cv::imwrite("line.png", originImage);
}

void ImageProcessing::clickBlock() {
    std::vector<cv::Vec<int, 4>> hierarchy;
    cv::findContours(pretreatmentImage, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE); //轮廓检测，且只记录拐点
    cv::drawContours(pretreatmentImage, contours, 0, 255, -1);  //不用循环
    cv::imwrite("click.png", pretreatmentImage);
}

void ImageProcessing::clickPosition() {
    // y = k x + b
    // y = ( -cos a / sin a ) x + ( r / sin a )
    // cos a X + sin a Y - r / sin a = 0
    // a X + b y + c = 0
    int distance,log=20;
    cv::Point clickPoint;
    clickPoint.x = 0;
    clickPoint.y = 0;
    double rho = lines[0][1], theta = lines[1][1];
    for (auto &p:contours) {
        auto middle = cv::moments(p, false);
        clickPoint.x = middle.m10 / middle.m00;
        clickPoint.y = middle.m01 / middle.m00;
        distance = fabs(cos(theta) * clickPoint.x + sin(theta) * clickPoint.y - rho / sin(theta)) /
                   sqrt(pow(clickPoint.x, 2) + pow(clickPoint.y, 2));
        if(distance < log) log = distance;
    }
    if (log < 10 && log > 0) {
        std::cout << "distance " << log << "x " << clickPoint.x << "y "<< clickPoint.y<< std::endl;
    }
}