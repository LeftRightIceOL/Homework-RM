#include <iostream>
#include <opencv2/opencv.hpp>
#include "Detector.hpp"

int main()
{
    Detector detector;

    std::cout << "=== 1. 开始 AprilTag 识别 ===" << std::endl;
    std::string tagPath = "tag.jpg";           //定义图片的文件路径
    cv::Mat tagImage = cv::imread(tagPath);    //调用imread读取图片文件,成功就返回Mat类型的图像,失败就返回空Mat  
    
    if (!tagImage.empty())
    {
        detector.Detector_Detect(tagImage);
        std::cout << "按任意键关闭窗口" << std::endl;
        cv::waitKey(0);             //无限等待键盘输入
        cv::destroyAllWindows();
    }
    else
    {
        std::cerr << "未找到图片"  << std::endl;
    }



    std::cout << "=== 2. 开始魔方颜色识别 ===" << std::endl;   //几乎相同逻辑
    std::string videoPath = "cube.mp4"; 
    cv::VideoCapture video(videoPath);
    
    if (!video.isOpened())
    {
        std::cerr << "未找到视频" << std::endl;
        return -1;
    }
    
    cv::Mat frame;   //定义两个变量 存储视频图像
    cv::Mat binaryImage;   //接收输出的二值化图像传入函数
    while (video.read(frame))
    {
        if (frame.empty()) 
        {
            break;
        }

        detector.Detector_Detect(frame, binaryImage);   //调用重载的 detect 函数
        int key = cv::waitKey(30);
        if (key == 27)   //按下 ESC 键退出循环  
        {
            break;
        }
    }

    video.release();
    cv::destroyAllWindows();
    
    return 0;
}