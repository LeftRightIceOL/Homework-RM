#ifndef INTRO_NODE_HPP
#define INTRO_NODE_HPP

#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class IntroNode : public rclcpp::Node
{
private:
rclcpp::Publisher<std_msgs::msg::String>::SharedPtr introPublisher;   // 发布器
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr introSubscription; // 订阅器
    rclcpp::TimerBase::SharedPtr introTimer;                              // 定时器

 size_t messageCount;
 std::string personalId;     //变量,消息编号和个人标识



    void Intro_TimerCallback();   //回调
    void Intro_SubCallback(const std_msgs::msg::String::SharedPtr msg);





public: 
    IntroNode();  //构造函数
};
#endif