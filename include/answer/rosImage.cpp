//
// Created by kon on 2/17/24.
//
#include "rosImage.h"

void Answer::getImage(const sensor_msgs::msg::Image::SharedPtr rosImage) {
    cv_bridge::CvImagePtr cvImage;
    cvImage = cv_bridge::toCvCopy(rosImage, sensor_msgs::image_encodings::BGR8);
    cv::resize(cvImage->image, cvImage->image, cv::Size(rosImage->width, rosImage->height));
    ImageProcessing processingImage(cvImage->image);
    int count = 0;
    double A = 0, B = 0, C = 0, distance = 200;

    for (auto &p: processingImage.lines) {
        count++;
        A += p[1] - p[3];
        B += p[2] - p[0];
        C += p[0] * p[3] - p[2] * p[1];
    }
    A = A / count;
    B = B / count;
    C = C / count;

    for (auto &p: processingImage.contours) {
        auto middle = cv::moments(p, false);
        clickPoint.x = middle.m10 / middle.m00;
        clickPoint.y = middle.m01 / middle.m00;

        distance = fabs(A * clickPoint.x + B * clickPoint.y + C) / sqrt(A * A + B * B);
        if (distance < 105 && distance > 75 ) {
            position.x = clickPoint.x;
            position.y = clickPoint.y;
            publisher_->publish(position);
            break;
        }
    }
}

Answer::Answer() : Node("answer") {
    position.z = 0;
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>( // 注意topic_name相对应
            "/raw_image", 10, std::bind(&Answer::getImage, this, std::placeholders::_1));
    publisher_ = this->create_publisher<geometry_msgs::msg::Point32>("/click_position", 10);
}

