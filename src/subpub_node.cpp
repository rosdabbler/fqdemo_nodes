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

#include <memory>

#include "fqdemo_nodes/demo_sub_pub.hpp"
#include "fqdemo_nodes/subpub_node.hpp"
#include "rclcpp/rclcpp.hpp"

// This is needed to prevent a duplicate definition warning from sphinx and breathe
// documentation generation.
#if !defined(DOXYGEN_SHOULD_SKIP_THIS)

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<fqdemo_nodes::DemoSubPub>());
  rclcpp::shutdown();
  return 0;
}

#endif // DOXYGEN_SHOULD_SKIP_THIS
