//
// Created by kon on 2/17/24.
//
#include "rosImage.h"

void Answer::getImage(const sensor_msgs::msg::Image::SharedPtr rosImage) {
    cv_bridge::CvImagePtr cvImage;
    cvImage = cv_bridge::toCvCopy(rosImage, sensor_msgs::image_encodings::BGR8);
    cv::resize(cvImage->image, cvImage->image, cv::Size(rosImage->width, rosImage->height));
    ImageProcessing processingImage(cvImage->image,delayTime);
    if (processingImage.decision==1) {
        position.x = processingImage.clickPoint.x;
        position.y = processingImage.clickPoint.y;
        position.z = 0;
        publisher_->publish(position);
    }
}

Answer::Answer() : Node("answer") {
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>( // 注意topic_name相对应
            "/raw_image", 10, std::bind(&Answer::getImage, this, std::placeholders::_1));
    publisher_ = this->create_publisher<geometry_msgs::msg::Point32>("/click_position",10);
}

