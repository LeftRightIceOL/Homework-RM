#include "Detector.hpp"
Detector::Detector()
{
  arucoDict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_APRILTAG_16h5);


    lowerRed1 = cv::Scalar(0, 100, 100);
    upperRed1 = cv::Scalar(10, 255, 255);
    lowerRed2 = cv::Scalar(160, 100, 100);
    upperRed2 = cv::Scalar(179, 255, 255);
    
    lowerGreen = cv::Scalar(40, 50, 50);
    upperGreen = cv::Scalar(80, 255, 255);
    
    lowerBlue = cv::Scalar(100, 150, 0);
    upperBlue = cv::Scalar(140, 255, 255);
    
    lowerYellow = cv::Scalar(20, 100, 100);
    upperYellow = cv::Scalar(30, 255, 255);
    lowerOrange = cv::Scalar(10, 100, 100);
    upperOrange = cv::Scalar(20, 255, 255);
    lowerWhite = cv::Scalar(0, 0, 200);
    upperWhite = cv::Scalar(180, 60, 255);

    cv::Ptr<cv::aruco::DetectorParameters> params = cv::aruco::DetectorParameters::create();
    params->minMarkerPerimeterRate = 0.01; 

}

cv::Mat Detector::Detector_Detect(const cv::Mat &inputImage)  //第一个Detect函数,传入原图返回结果图
{
    cv::Mat result = inputImage.clone();
    cv::Mat grayImage;
    cv::Mat binaryImage;   

    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);
    cv::threshold(grayImage, binaryImage, 128, 255, cv::THRESH_BINARY);
    
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners; //记录AprilTag在图像中的位置和形状
    std::vector<std::vector<cv::Point2f>> rejected;  //AI检测器认为可能是AprilTag但不符合要求的候选区域(我自己没写这行,这个注释也是ai加的。。。。)



    
     cv::Ptr<cv::aruco::DetectorParameters> params = cv::aruco::DetectorParameters::create();
    params->minMarkerPerimeterRate = 0.01;

    cv::aruco::detectMarkers(inputImage, arucoDict, corners, ids, params, rejected); // 调用aruco 模块检测 AprilTag







 if (!ids.empty())
    {
        cv::aruco::drawDetectedMarkers(result, corners, ids);
        std::cout << "成功识别到 AprilTag, 数量: " << ids.size() << std::endl;  //检测到了就在 result 图像上绘制
    }
    else
    {
        std::cout << "未识别到 AprilTag" << std::endl;
    }

    cv::imshow("Image_raw", inputImage);
    cv::imshow("Image_binary", binaryImage);
    cv::imshow("result", result);

    return result;
}

cv::Mat Detector::Detector_Detect(const cv::Mat &inputImage, cv::Mat &binaryImage)
{
    cv::Mat result = inputImage.clone();  //克隆一份原图作为结果底图然后绘制就不会修改原始输入图像
    cv::Mat hsvImage;
    cv::cvtColor(inputImage, hsvImage, cv::COLOR_BGR2HSV);  //opencv的颜色空间转换函数,将BGR图像转换为HSV图像,便于颜色分割
    
    cv::Mat maskRed1, maskRed2, maskRed;
    cv::Mat maskGreen, maskBlue, maskYellow;
    cv::Mat maskOrange;
    cv::Mat maskWhite;

    cv::inRange(hsvImage, lowerRed1, upperRed1, maskRed1);
    cv::inRange(hsvImage, lowerRed2, upperRed2, maskRed2);
    cv::bitwise_or(maskRed1, maskRed2, maskRed);
    cv::inRange(hsvImage, lowerGreen, upperGreen, maskGreen);
    cv::inRange(hsvImage, lowerBlue, upperBlue, maskBlue);
    cv::inRange(hsvImage, lowerYellow, upperYellow, maskYellow);
    cv::inRange(hsvImage, lowerOrange, upperOrange, maskOrange);
    cv::inRange(hsvImage, lowerWhite, upperWhite, maskWhite);     //// 根据设定提取二值化掩码

binaryImage = maskRed | maskGreen | maskBlue | maskYellow | maskOrange | maskWhite;  //合并，作为展示的二值化图像


cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));   //去噪
    cv::morphologyEx(binaryImage, binaryImage, cv::MORPH_OPEN, kernel);     //消白点
    cv::morphologyEx(binaryImage, binaryImage, cv::MORPH_CLOSE, kernel);      //填黑洞


    std::vector<std::vector<cv::Point>> contours;  //提取轮廓
    cv::findContours(binaryImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);  //简单优化
    
    for (size_t i = 0; i < contours.size(); i++)
    {
        double area = cv::contourArea(contours[i]);

        if (area > 1000.0)    //小于一千直接飞
        {
            cv::Rect rect = cv::boundingRect(contours[i]);   //计算最小外接正矩形,用`Rect`类型存储
            cv::rectangle(result, rect, cv::Scalar(0, 255, 0), 2);   //在结果图上外接矩形,默认绿色
            cv::Point center(rect.x + rect.width / 2, rect.y + rect.height / 2);  //计算中心点坐标
            std::string colorName = "Unknown";
            cv::Scalar textColor(0, 255, 0); 
            
            if (maskRed.at<uchar>(center) > 0) //uchar读取掩码中中心点的像素值并判定,其余颜色同理
            {
                colorName = "Red";
                textColor = cv::Scalar(0, 0, 255);
            }
            else if (maskGreen.at<uchar>(center) > 0)
{
    colorName = "Green";
    textColor = cv::Scalar(0, 255, 0);
}
else if (maskBlue.at<uchar>(center) > 0)
{
    colorName = "Blue";
    textColor = cv::Scalar(255, 0, 0);
}
else if (maskYellow.at<uchar>(center) > 0)
{
    colorName = "Yellow";
    textColor = cv::Scalar(0, 255, 255);
}
else if (maskOrange.at<uchar>(center) > 0)
{
    colorName = "Orange";
    textColor = cv::Scalar(0, 165, 255);
}
else if (maskWhite.at<uchar>(center) > 0)
{
    colorName = "White";
    textColor = cv::Scalar(255, 255, 255);
}

            cv::putText(result, colorName, center, cv::FONT_HERSHEY_SIMPLEX, 0.9, textColor, 2); //在中心点写颜色名称
        }
    }

    cv::imshow("Image_raw", inputImage);
    cv::imshow("Image_binary", binaryImage);
    cv::imshow("result", result);

    return result;
}