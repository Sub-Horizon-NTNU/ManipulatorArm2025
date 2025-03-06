#ifndef MANUALCONTROLLERNODE_HPP
#define MANUALCONTROLLERNODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/string.hpp"
#include "ManualController.hpp"

class ManualControllerNode : public rclcpp::Node {
public:
    ManualControllerNode() : Node("manual_controller_node") {
        //Publisher
        anglePublisher = this->create_publisher<std_msgs::msg::Float64>("manualControlAngle", 10);
        speedPublisher = this->create_publisher<std_msgs::msg::Int32>("manualControlSpeed", 10);

        //Subscriber
        keySubscriber = create_subscription<std_msgs::msg::String>(
            "keyPresses", 10,
            std::bind(&ManualControllerNode::keyCallback, this, std::placeholders::_1));

        publishTimer = this->create_wall_timer(
            std::chrono::milliseconds(10),
            std::bind(&ManualControllerNode::timerCallback, this));
    }

private:
    void keyCallback(const std_msgs::msg::String::SharedPtr msg) {
        char key = msg->data[0];
        manualController.changeAngleSpeed(key);
        RCLCPP_INFO(this->get_logger(), "Received key: %c", key);

        //Escape for å avslutte programmet
        if(key == 27){
            rclcpp::shutdown();
        }
    }

    void timerCallback() {
        //Angle publisering
        float angle = manualController.getAngle();
        auto angle_msg = std_msgs::msg::Float64();
        angle_msg.data = static_cast<double>(angle);
        anglePublisher->publish(angle_msg);
        RCLCPP_INFO(this->get_logger(), "Angle: %f", angle);

        //Speed publisering
        int speed = manualController.getSpeed();
        auto speed_msg = std_msgs::msg::Int32();
        speed_msg.data = speed;
        speedPublisher->publish(speed_msg);
        RCLCPP_INFO(this->get_logger(), "Speed: %d", speed);
    }

    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr anglePublisher;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr speedPublisher;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr keySubscriber;
    rclcpp::TimerBase::SharedPtr publishTimer;
    ManualController manualController;
};

#endif // MANUALCONTROLLERNODE_HPP