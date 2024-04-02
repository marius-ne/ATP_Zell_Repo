#include <rclcpp/rclcpp.hpp>
#include "tf2_eigen/tf2_eigen.hpp"

#include "../include/Pose.h"
#include "../include/SceneObjects/SceneObject.h"
#include "../include/Scene.h"

#include "../include/IoInterface.h"
#include "../include/ObjectContainer.h"

#include <math.h>
#include <memory>



int TransformTest() {

  std::shared_ptr<WzlPlanner::Transform> trWorld = std::make_shared<WzlPlanner::Transform>("world");
  std::shared_ptr<WzlPlanner::Transform> trStation = std::make_shared<WzlPlanner::Transform>("station");
  trStation->SetParent(trWorld);

  std::shared_ptr<WzlPlanner::Transform> trSlot1 = std::make_shared<WzlPlanner::Transform>("slot1");
  trSlot1->SetParent(trStation);

  std::shared_ptr<WzlPlanner::Transform> trSlot2 = std::make_shared<WzlPlanner::Transform>("slot2");
  trSlot2->SetParent(trStation);

  std::shared_ptr<WzlPlanner::Transform> trSlot3 = std::make_shared<WzlPlanner::Transform>("slot3");
  trSlot3->SetParent(trStation);

  trStation->GetPoseRelative()->SetPositionXYZ(10, 0, 0);
  trStation->GetPoseRelative()->SetRotationZ(M_PI_2);
  trSlot1->GetPoseRelative()->SetPositionXYZ(0, -1, 2);
  trSlot2->GetPoseRelative()->SetPositionXYZ(0, 0, 2);
  trSlot3->GetPoseRelative()->SetPositionXYZ(0, 1, 2);

  trWorld->Update();
  trWorld->Print();

  return 0;
}

void CreateCell(const std::shared_ptr<rclcpp::Node> node)
{
  auto robot = std::make_shared<WzlPlanner::RobotDummy>(node);
  auto scene = std::make_shared<WzlPlanner::Scene>(robot);
  auto ioInterfaceOpcUa = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  
  RCLCPP_INFO(node->get_logger(), "Robot scheduler cell environment initialization start.");
  RCLCPP_INFO(node->get_logger(), "Initialize ObjectContainer");

  WzlPlanner::ObjectContainer::Get()->Initialize(
    ioInterfaceOpcUa, 
    robot, 
    scene,
    node);

  // gripper change station
  RCLCPP_INFO(node->get_logger(), "Initialize Gripper change station");
  auto gripperChangeStation = std::make_shared<WzlPlanner::SceneObjectGripperChangeStation>("GripperChangeStation");
  scene->AddSceneObject(gripperChangeStation);
  gripperChangeStation->GetTransform()->GetPoseRelative()->SetPositionXYZ(0, 10, 0);

  // clamping device jaws
  RCLCPP_INFO(node->get_logger(), "Initialize Clamping device jaw");
  auto clampingDeviceJaws = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceJaw");
  scene->AddSceneObject(clampingDeviceJaws);
  clampingDeviceJaws->GetTransform()->GetPoseRelative()->SetPositionXYZ(5, 0, 0);

  // clamping device elevation
  RCLCPP_INFO(node->get_logger(), "Initialize clamping device elevation");
  auto clampingDeviceElevation = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceElavation");
  scene->AddSceneObject(clampingDeviceElevation);
  clampingDeviceElevation->GetTransform()->GetPoseRelative()->SetPositionXYZ(5, 0, 0);

  // scanning tower
  RCLCPP_INFO(node->get_logger(), "Initialize visual scan tower");
  auto scanningTower = std::make_shared<WzlPlanner::SceneObjectVisualScanTower>("VisualScanTower");
  scene->AddSceneObject(scanningTower);
  scanningTower->GetTransform()->GetPoseRelative()->SetPositionXYZ(5, 5, 0);

  // carrier
  RCLCPP_INFO(node->get_logger(), "Initialize carrier");
  auto carrier = std::make_shared<WzlPlanner::SceneObjectCarrier>("Carrier");
  RCLCPP_INFO(node->get_logger(), "Initialize carrier");
  scene->AddSceneObject(carrier);
  RCLCPP_INFO(node->get_logger(), "Initialize carrier");
  carrier->GetTransform()->GetPoseRelative()->SetPositionXYZ(-5, 0, 0);
  RCLCPP_INFO(node->get_logger(), "Initialize carrier");

  RCLCPP_INFO(node->get_logger(), "Robot scheduler cell environment initialization end.");
}

void OpcUaTest(const std::shared_ptr<rclcpp::Node> node)
{
  auto ioInterfaceOpcUa = std::make_shared<WzlPlanner::IoInterfaceOpcUa>(node);
  auto testCall = ioInterfaceOpcUa->SetValueBool(0, 0);

  if (testCall)
  {
    std::cout << "OpcUa Test Call was successful" << std::endl;
  }
  else 
  {
    std::cout << "OpcUa Test Call failed" << std::endl;
  }
}

int main(int argc, char* argv[])
{
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);

  //auto trWorld = std::make_shared<WzlPlanner::Transform>("world");

  auto const node = std::make_shared<rclcpp::Node>(
      "robot_planer", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
  std::cout << "Test" << std::endl;
  
  RCLCPP_DEBUG(node->get_logger(), "My log message %d", 4);
  std::cout << "Test" << std::endl;
  CreateCell(node);
  OpcUaTest(node);

  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  //spinner.join();
  return 0;
}