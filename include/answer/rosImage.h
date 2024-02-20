//
// Created by kon on 2/17/24.
//
#pragma once

#include <memory>
#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/image.hpp>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>


class ImageSubscriber : public rclcpp::Node {
public:
    ImageSubscriber();

    cv::Mat gameImage;
private:
    void getImage(const sensor_msgs::msg::Image::SharedPtr rosImage);

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};
