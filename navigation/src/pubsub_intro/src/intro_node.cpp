    #include "intro_node.hpp"

    IntroNode::IntroNode() : Node("intro_node"), messageCount(0), personalId("wocaishinailong!")
    {
        introPublisher = this->create_publisher<std_msgs::msg::String>("intro_topic", 10); // 创建发布器

        introSubscription = this->create_subscription<std_msgs::msg::String>(
            "/intro/in", 10, std::bind(&IntroNode::Intro_SubCallback, this, std::placeholders::_1)); // 创建订阅器  //把外部触发的事件绑定到类的成员函数

        introTimer = this->create_wall_timer(
            std::chrono::seconds(1), std::bind(&IntroNode::Intro_TimerCallback, this)); // 创建定时器   
            
            
            RCLCPP_INFO(this->get_logger(), "intro_node 已启动，开始发布和订阅...") ;    //终端打印
    }


    //定时器回调
    void IntroNode::Intro_TimerCallback()   
    { 
        auto message = std_msgs::msg::String();      //创建消息对象
        message.data = personalId + " - No." + std::to_string(messageCount);    //拼接字符串
        
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());


        // 发布消息
        introPublisher->publish(message);
        messageCount++;
    }


    //订阅者

    void IntroNode::Intro_SubCallback(const std_msgs::msg::String::SharedPtr msg)
    {
        //打印接收内容
        RCLCPP_INFO(this->get_logger(), "Received: %s", msg->data.c_str());
    }