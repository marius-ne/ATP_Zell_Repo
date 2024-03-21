#include <rclcpp/rclcpp.hpp>
#include "tf2_eigen/tf2_eigen.hpp"
#include "Pose.h"
#include "SceneObject.h"
#include "Scene.h"

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

void CreateCell()
{
  auto robot = std::make_shared<WzlPlanner::RobotDummy>();
  auto scene = std::make_shared<WzlPlanner::Scene>(robot);
  
  // gripper change station
  auto gripperChangeStation = std::make_shared<WzlPlanner::SceneObjectGripperChangeStation>("GripperChangeStation");
  scene->AddSceneObject(gripperChangeStation);
  gripperChangeStation->GetTransform()->GetPoseRelative()->SetPositionXYZ(0, 10, 0);

  // clamping device jaws
  auto clampingDeviceJaws = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceJaw");
  scene->AddSceneObject(clampingDeviceJaws);
  clampingDeviceJaws->GetTransform()->GetPoseRelative()->SetPositionXYZ(5, 0, 0);

  // clamping device elevation
  auto clampingDeviceElevation = std::make_shared<WzlPlanner::SceneObjectClampingDeviceJaws>("ClampingDeviceElavation");
  scene->AddSceneObject(clampingDeviceElevation);
  clampingDeviceElevation->GetTransform()->GetPoseRelative()->SetPositionXYZ(5, 0, 0);

  // scanning tower
  auto scanningTower = std::make_shared<WzlPlanner::SceneObjectVisualScanTower>("VisualScanTower");
  scene->AddSceneObject(scanningTower);
  scanningTower->GetTransform()->GetPoseRelative()->SetPositionXYZ(5, 5, 0);

  // carrier
  auto carrier = std::make_shared<WzlPlanner::SceneObjectCarrier>("Carrier");
  scene->AddSceneObject(carrier);
  carrier->GetTransform()->GetPoseRelative()->SetPositionXYZ(-5, 0, 0);




}

int main(int argc, char* argv[])
{
  // Initialize ROS and create the Node
  rclcpp::init(argc, argv);

  //auto trWorld = std::make_shared<WzlPlanner::Transform>("world");

  CreateCell();

  auto const node = std::make_shared<rclcpp::Node>(
      "robot_planer", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

  rclcpp::spin(node);

  // Shutdown ROS
  rclcpp::shutdown();
  //spinner.join();
  return 0;
}