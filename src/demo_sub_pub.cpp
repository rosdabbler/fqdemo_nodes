//
//   Copyright 2021 R. Kent James <kent@caspia.com>
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cmath>
#include <tuple>

#include "fqdemo_nodes/demo_sub_pub.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

namespace fqdemo_nodes
{

// TODO(rkent): implement logging as shown in
// https://github.com/ros-planning/moveit2/blob/main/doc/MIGRATION_GUIDE.md

DemoSubPub::DemoSubPub()
: rclcpp::Node("demo_sub_pub"),
  count_(0)
{
  publisher_ = this->create_publisher<fqdemo_msgs::msg::NumPwrResult>("power_result", 10);
  subscriber_ = this->create_subscription<fqdemo_msgs::msg::NumPwrData>(
    "num_power", 10, std::bind(&DemoSubPub::topic_callback, this, _1));
  timer_ = this->create_wall_timer(
    2000ms, std::bind(&DemoSubPub::timer_callback, this));
}

std::tuple<double, double> DemoSubPub::apply_powers(
  const double_t number,
  const double_t exponent
)
{
  double to_power = pow(number, exponent);
  double to_root = pow(number, 1. / exponent);
  return std::tuple<double, double>{to_power, to_root};
}

void DemoSubPub::topic_callback(const fqdemo_msgs::msg::NumPwrData::SharedPtr msg)
{
  RCLCPP_INFO(this->get_logger(), "I heard: '%12.3g, %12.3g'", msg->num, msg->power);
  auto message = fqdemo_msgs::msg::NumPwrResult();
  auto pair = apply_powers(msg->num, msg->power);
  message.to_root = std::get<1>(pair);
  message.to_power = std::get<0>(pair);
  RCLCPP_INFO(
    this->get_logger(), "Publishing NumPwrResult power: %12.3g, root: %12.3g",
    message.to_power, message.to_root);
  publisher_->publish(message);
}

void DemoSubPub::timer_callback()
{
  auto message = fqdemo_msgs::msg::NumPwrResult();
  message.to_root = 0.0;
  message.to_power = 0.0;
  RCLCPP_INFO(
    this->get_logger(), "Publishing NumPwrResult power: %12.3g, root: %12.3g",
    message.to_power, message.to_root);
  publisher_->publish(message);
}

}  // namespace fqdemo_nodes
