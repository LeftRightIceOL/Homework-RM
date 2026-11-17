#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "intro_node.hpp"


int main(int argc, char * argv[])   // 函数作用：程序主入口
{
    rclcpp::init(argc, argv);  // 初始化 ROS2 客户端库
    auto node = std::make_shared<IntroNode>();  // 创建 IntroNode 节点对象
    rclcpp::spin(node);  // 进入循环，等待回调函数被触发
    rclcpp::shutdown();  // 关闭 ROS2 客户端库
    return 0;  // 返回成功状态码
}