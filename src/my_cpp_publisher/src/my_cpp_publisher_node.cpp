#include <cstdio>
#include "my_msg_types/msg/my_msg.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

using namespace std::chrono_literals;

class MyCppPublisher : public rclcpp::Node
{
public:
    MyCppPublisher() : rclcpp::Node("my_cpp_publisher"), count_(0)
    {
        publisher_ = this->create_publisher<my_msg_types::msg::MyMsg>("my_topic", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&MyCppPublisher::timer_callback, this));
    }
private:
    void timer_callback()
    {
        auto message = my_msg_types::msg::MyMsg();
        message.first_name = "Max";
        message.last_name = "Mustermann";
        message.age = 0+count_++;
        message.address = "Musterstrasse 1";

        RCLCPP_INFO(this->get_logger(), "Publishing: '%s %s %d %s'", message.first_name.c_str(), message.last_name.c_str(), message.age, message.address.c_str());

        publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<my_msg_types::msg::MyMsg>::SharedPtr publisher_;
    size_t count_;

};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MyCppPublisher>());
    rclcpp::shutdown();
    return 0;
}
