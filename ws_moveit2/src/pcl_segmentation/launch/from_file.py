from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package="pcl_segmentation",
            executable="file_publisher",
            name="file_publisher_param_node",
            parameters=[{
                'file_path': '/home/aw/restackcell/ws_moveit2/src/pcl_segmentation/data/0.ply',
                "publisher_name": "/test_publisher"
            }]
        ),        
        Node(
            package="pcl_segmentation",
            executable="downsampling",
            name="downsampling_param_node",
            parameters=[{
                "subscription_name": "/tof_point_cloud",
                "publisher_name": "/tof_point_cloud_downsampled",
                "leaf_size": 0.3
            }]
        ),
        Node(
            package="pcl_segmentation",
            executable="plane_filter",
            name="plane_filter_param_node",
            parameters=[{
                "subscription_name": "/tof_point_cloud_downsampled",
                "publisher_name_plane": "/tof_point_cloud_filtered_plane",
                "publisher_name_plane_inverted": "/tof_point_cloud_filtered_plane_inverted",
                "leaf_size": 0.3
            }]
        ),
        Node(
            package="pcl_segmentation",
            executable="clustering",
            name="clustering_param_node",
            parameters=[{
                "subscription_name": "/tof_point_cloud_filtered_plane_inverted",
                "publisher_name_colored": "/tof_point_cloud_colored",
                "publisher_name_clustered": "/tof_point_cloud_clustered",
                "cluster_tolerance": 5,
                "cluster_size_min": 2000,
                "cluster_size_max": 1000000
            }]
        ),
        Node(
            package="pcl_segmentation",
            executable="classification",
            name="matching_param_node",
            parameters=[{
                "subscription_name": "/tof_point_cloud_clustered",
                "publisher_name": "/tof_point_cloud_classified",
            }]
        ),
        Node(
            package="pcl_segmentation",
            executable="matching",
            name="matching_param_node",
            parameters=[{
                "subscription_name": "/tof_point_cloud_clustered",
                "publisher_name_colored": "/tof_point_cloud_matched",
            }]                        
        ),
        Node(
            package="pcl_segmentation",
            executable="pose_snapper",
            name="pose_snapper_param_node",
            parameters=[{
                "subscription_name": "/tof_point_cloud_clustered",
                "publisher_name_colored": "/tof_point_cloud_matched",
            }]                        
        ),

        

    ])