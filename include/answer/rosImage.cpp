//
// Created by kon on 2/17/24.
//
#include "rosImage.h"

void ImageSubscriber::getImage(const sensor_msgs::msg::Image::SharedPtr rosImage) {
    cv_bridge::CvImagePtr cvImage;
    cvImage = cv_bridge::toCvCopy(rosImage, sensor_msgs::image_encodings::BGR8);
    ImageProcessing processingImage(cvImage->image);
}

ImageSubscriber::ImageSubscriber()
        : Node("image_subscriber") {
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>( // 注意topic_name相对应
            "/raw_image", 10, std::bind(&ImageSubscriber::getImage, this, std::placeholders::_1));
}

