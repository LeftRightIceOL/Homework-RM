#ifndef DETECTOR_HPP
#define DETECTOR_HPP
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <vector>
#include <string>  //公式化开局,保护宏和引入

//定义类再封装下私有公有

class Detector
{
private:
    cv::Ptr<cv::aruco::Dictionary> arucoDict;
    cv::Scalar lowerRed1;
    cv::Scalar upperRed1;
    cv::Scalar lowerRed2;
    cv::Scalar upperRed2;
    cv::Scalar lowerGreen;
    cv::Scalar upperGreen;
    cv::Scalar lowerBlue;
    cv::Scalar upperBlue;
    cv::Scalar lowerYellow;
    cv::Scalar upperYellow;
    cv::Scalar lowerOrange;
    cv::Scalar upperOrange;
    cv::Scalar lowerWhite;
    cv::Scalar upperWhite;



public:
//一个识别再返回结果，再来一个重载识别魔方然后返结果再修二值化图像

    Detector();
    cv::Mat Detector_Detect(const cv::Mat &inputImage);
    cv::Mat Detector_Detect(const cv::Mat &inputImage, cv::Mat &binaryImage);
};

#endif