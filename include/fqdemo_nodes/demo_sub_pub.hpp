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

#ifndef FQDEMO_NODES__DEMO_SUB_PUB_HPP_
#define FQDEMO_NODES__DEMO_SUB_PUB_HPP_

#include <tuple>
#include "rclcpp/rclcpp.hpp"
#include "fqdemo_msgs/msg/num_pwr_result.hpp"
#include "fqdemo_msgs/msg/num_pwr_data.hpp"

namespace fqdemo_nodes {

class DemoSubPub : public rclcpp::Node
{
public:
  explicit DemoSubPub();
  virtual ~DemoSubPub() {};
  std::tuple<double, double> apply_powers(const double_t number, const double power);

private:
  void topic_callback(const fqdemo_msgs::msg::NumPwrData::SharedPtr msg);
  void timer_callback();
  rclcpp::Subscription<fqdemo_msgs::msg::NumPwrData>::SharedPtr subscriber_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<fqdemo_msgs::msg::NumPwrResult>::SharedPtr publisher_;
  size_t count_;
};

}  // namespace fqdemo_nodes

#endif  // FQDEMO_NODES__DEMO_SUB_PUB_HPP_