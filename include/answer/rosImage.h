//
// Created by kon on 2/17/24.
//
#pragma once

#include <memory>
#include "rclcpp/rclcpp.hpp"
#include <sensor_msgs/msg/image.hpp>
#include <geometry_msgs/msg/point32.hpp>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

#include "returnPosition.h"

using namespace std::chrono_literals;

class Answer : public rclcpp::Node {
public:
    Answer();
private:
    void getImage(const sensor_msgs::msg::Image::SharedPtr rosImage);

    cv::Mat gameImage;
    geometry_msgs::msg::Point32 position;
    int delayTime=0;

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Point32>::SharedPtr publisher_;
};
