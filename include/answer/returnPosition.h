//
// Created by kon on 2/18/24.
//

#ifndef ANSWER_RETURNPOSITION_H
#define ANSWER_RETURNPOSITION_H

#include <opencv2/opencv.hpp>

class ImageProcessing{
private:
    cv::Mat originImage;
    cv::Mat pretreatmentImage;
    void pretreatment();
public:
    ImageProcessing(cv::Mat &image);
    //getLine()
};

#endif //ANSWER_RETURNPOSITION_H
