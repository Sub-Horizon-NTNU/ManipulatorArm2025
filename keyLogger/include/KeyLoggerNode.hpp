#ifndef KEYLOGGERNODE_HPP
#define KEYLOGGERNODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "KeyLogger.hpp"

class KeyLoggerNode : public rclcpp::Node {
public:
    KeyLoggerNode() : Node("key_logger_node") {
        //Lager publisher
        keyPressPublisher = this->create_publisher<std_msgs::msg::String>("keyPresses", 10);
        
        //Timer for publisering, sjekker hvert 10ende millisekund
        publishTimer = this->create_wall_timer(
            std::chrono::milliseconds(1),
            std::bind(&KeyLoggerNode::timerCallback, this));
    }

private:
    void timerCallback() {
        char key = keyLogger.checkKeyPressed();
        if(key != '\0') {
            //Publiserer meldinger
            auto msg = std_msgs::msg::String();
            msg.data = std::string(1, key);
            keyPressPublisher->publish(msg);
            
            RCLCPP_INFO(this->get_logger(), "Pressed key: '%c'", key);
            
            //Escape for å avsluttet programmet
            if(key == 27){
                rclcpp::shutdown();
            }
        }
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr keyPressPublisher;
    rclcpp::TimerBase::SharedPtr publishTimer;
    KeyLogger keyLogger;
};

#endif // KEYLOGGERNODE_HPP