//
// Created by kon on 2/18/24.
//

#include "returnPosition.h"

ImageProcessing::ImageProcessing(cv::Mat &image){
    originImage = image;
    ImageProcessing::pretreatment();
}

void ImageProcessing::pretreatment() {
    cv::Mat temporaryImage;
    cv::cvtColor(originImage, temporaryImage, cv::COLOR_BGR2GRAY, 0);
    cv::imwrite("gray.png", temporaryImage);
//    cv::adaptiveThreshold(temporaryImage,temporaryImage,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,3,0);
    cv::threshold(temporaryImage,temporaryImage,200,255,cv::THRESH_BINARY);
    cv::imwrite("THRESH_BINARY.png", temporaryImage);
//    cv::Mat closeCore = cv::getStructuringElement(cv::MORPH_RECT,cv::Size (5,5));
//    cv::morphologyEx(temporaryImage,temporaryImage,cv::MORPH_CLOSE,closeCore);
//    cv::imwrite("close.png",temporaryImage);
    cv::Canny(temporaryImage,pretreatmentImage,3,1,3);
    cv::imwrite("3b1.png",pretreatmentImage);

    //cv::HoughLines() another function
}

