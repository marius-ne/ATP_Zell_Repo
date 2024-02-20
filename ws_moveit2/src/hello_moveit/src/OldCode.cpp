/*   moveit_msgs::msg::CollisionObject co;
   
  shapes::Mesh* m = shapes::createMeshFromResource("package://cube.stl");
  shapes::MESH::createMeshFromResource
  shape_msgs::msg::Mesh co_mesh;
  shapes::ShapeMsg co_mesh_msg;
  shapes::constructMsgFromShape(m,co_mesh_msg);
  co_mesh = boost::get<shape_msgs::Mesh>(co_mesh_msg);
  co.meshes.resize(1);
  co.meshes[0] = co_mesh;
  co.mesh_poses.resize(1);
  co.mesh_poses[0].position.x = 1.0;
  co.mesh_poses[0].position.y = 1.0;
  co.mesh_poses[0].position.z = 0.0;
  co.mesh_poses[0].orientation.w= 1.0;
  co.mesh_poses[0].orientation.x= 0.0;
  co.mesh_poses[0].orientation.y= 0.0;
  co.mesh_poses[0].orientation.z= 0.0;
*/
    //co.primitives.push_back(m);
    //co.primitive_poses.push_back(box_pose);
    //co.operation = collision_object.ADD;

    //return co;
  //}//();






// create collision  object from cad step files
/*
moveit_msgs::CollisionObject co;
shapes::Mesh* m = shapes::createMeshFromResource("package://cube.stl");
shape_msgs::Mesh co_mesh;
shapes::ShapeMsg co_mesh_msg;
shapes::constructMsgFromShape(m,co_mesh_msg);
co_mesh = boost::get<shape_msgs::Mesh>(co_mesh_msg);
co.meshes.resize(1);
co.meshes[0] = co_mesh;
co.mesh_poses.resize(1);
co.mesh_poses[0].position.x = 1.0;
co.mesh_poses[0].position.y = 1.0;
co.mesh_poses[0].position.z = 0.0;
co.mesh_poses[0].orientation.w= 1.0;
co.mesh_poses[0].orientation.x= 0.0;
co.mesh_poses[0].orientation.y= 0.0;
co.mesh_poses[0].orientation.z= 0.0;
//pub_co.publish(co);

co.meshes.push_back(co_mesh);
co.mesh_poses.push_back(co.mesh_poses[0]);
co.operation = co.ADD;

std::vector<moveit_msgs::CollisionObject> collision_objects;  
collision_objects.push_back(co);  
*/
// Now, let's add the collision object into the world
//ROS_INFO("Add an object into the world");  
//planning_scene_interface.addCollisionObjects(collision_objects);

  // Add the collision object to the scene
  //moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  //planning_scene_interface.applyCollisionObject(collision_object);




/*
  // Create collision object for the robot to avoid
  auto const collision_object = [frame_id = move_group_interface.getPlanningFrame()] {
    
    moveit_msgs::msg::CollisionObject collision_object;
    collision_object.header.frame_id = frame_id;
    collision_object.id = "box1";
    shape_msgs::msg::SolidPrimitive primitive;

    // Define the size of the box in meters
    primitive.type = primitive.BOX;
    primitive.dimensions.resize(3);
    primitive.dimensions[primitive.BOX_X] = 0.5;
    primitive.dimensions[primitive.BOX_Y] = 0.1;
    primitive.dimensions[primitive.BOX_Z] = 0.5;

    // Define the pose of the box (relative to the frame_id)
    geometry_msgs::msg::Pose box_pose;
    box_pose.orientation.w = 1.0;
    box_pose.position.x = 0.2;
    box_pose.position.y = 0.2;
    box_pose.position.z = 0.25;

    collision_object.primitives.push_back(primitive);
    collision_object.primitive_poses.push_back(box_pose);
    collision_object.operation = collision_object.ADD;

    return collision_object;
  }();
    
  // Add the collision object to the scene
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  planning_scene_interface.applyCollisionObject(collision_object);
  */


  // set pose for collision mesh
  geometry_msgs::msg::Pose shelf_pose;
    shelf_pose.orientation.w = 0;
    shelf_pose.orientation.x = 0;
    shelf_pose.orientation.y = 0;
    shelf_pose.orientation.z = 0;
    shelf_pose.position.x = 0;
    shelf_pose.position.y = 0;
    shelf_pose.position.z = 0;
    

  //moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  std::string meshPath = "package://hello_moveit/spanneinheit.stl";

  /*
  if (addMeshColllsionObject(move_group_interface, planning_scene_interface, meshPath, "meshTest3", 0.1f, shelf_pose))
  {
    std::cout << "Succesfully added to scene" << std::endl;
  }
  else
  {
    std::cout << "Failed to add object to to scene"<< std::endl;
  }
  */

  

  meshPath = "package://hello_moveit/cube.stl";
  shelf_pose.position.x = 1;





  // erstellen eines tf frames mit header
                  geometry_msgs::msg::Transform t;
                tf2::utils::
                t.transform.translation.x = atof(transformation[2]);
                t.transform.translation.y = atof(transformation[3]);
                t.transform.translation.z = atof(transformation[4]);
                tf2::Quaternion q;
                q.setRPY(
                atof(transformation[5]),
                atof(transformation[6]),
                atof(transformation[7]));
                t.transform.rotation.x = q.x();
                t.transform.rotation.y = q.y();
                t.transform.rotation.z = q.z();
                t.transform.rotation.w = q.w();