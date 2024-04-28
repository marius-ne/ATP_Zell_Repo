#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <sensor_msgs/msg/point_cloud2.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <pcl_conversions/pcl_conversions.h>

#include "ArenaApi.h"


using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

// pixel format
#define PIXEL_FORMAT "Coord3D_ABCY16"
#define IMAGE_TIMEOUT 2000

#define TAB1 "  "
#define TAB2 "    "
#define TAB3 "      "


class MinimalPublisher : public rclcpp::Node
{
  public:
    MinimalPublisher()
    : Node("minimal_publisher"), count_(0)
    {
      publisher_pointcloud_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("tof_point_cloud", 10);
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
      timer_ = this->create_wall_timer(100ms, std::bind(&MinimalPublisher::timer_callback_message, this));
      timer_pointcloud_ = this->create_wall_timer(100ms, std::bind(&MinimalPublisher::timer_callback_pointcloud, this));
    }

    int InitializeCamera()
    {
      pSystem = Arena::OpenSystem();
      pSystem->UpdateDevices(100);
      std::vector<Arena::DeviceInfo> deviceInfos = pSystem->GetDevices();
      if (deviceInfos.size() == 0)
      {
        std::cout << "\nNo camera connected\nPress enter to complete\n";
        std::getchar();
        return 0;
      }
      pDevice = pSystem->CreateDevice(deviceInfos[0]);
      pNodeMap = pDevice->GetNodeMap();

      // Set acquisition mode
      //    Set acquisition mode before starting the stream. Starting the stream
      //    requires the acquisition mode to be set beforehand. The acquisition
      //    mode controls the number of images a device acquires once the stream
      //    has been started. Setting the acquisition mode to 'Continuous' keeps
      //    the stream from stopping. This example returns the camera to its
      //    initial acquisition mode near the end of the example.
      std::cout << TAB1 << "Set acquisition mode to 'Continuous'\n";

      Arena::SetNodeValue<GenICam::gcstring>(
        pDevice->GetNodeMap(),
        "AcquisitionMode",
        "Continuous");

      // Set buffer handling mode
      //    Set buffer handling mode before starting the stream. Starting the
      //    stream requires the buffer handling mode to be set beforehand. The
      //    buffer handling mode determines the order and behavior of buffers in
      //    the underlying stream engine. Setting the buffer handling mode to
      //    'NewestOnly' ensures the most recent image is delivered, even if it
      //    means skipping frames.
      std::cout << TAB1 << "Set buffer handling mode to 'NewestOnly'\n";

      Arena::SetNodeValue<GenICam::gcstring>(
        pDevice->GetTLStreamNodeMap(),
        "StreamBufferHandlingMode",
        "NewestOnly");

      // validate if Scan3dCoordinateSelector node exists. If not - probaly not
      // Helios camera used running the example
      GenApi::CEnumerationPtr checkpCoordSelector = pNodeMap->GetNode("Scan3dCoordinateSelector");
      if (!checkpCoordSelector)
      {
        std::cout << TAB1 << "Scan3dCoordinateSelector node is not found. Please make sure that Helios device is used for the example.\n";
        return 0;
      }

      // validate if Scan3dCoordinateOffset node exists. If not - probaly Helios
      // has an old firmware
      GenApi::CFloatPtr checkpCoord = pNodeMap->GetNode("Scan3dCoordinateOffset");
      if (!checkpCoord)
      {
        std::cout << TAB1 << "Scan3dCoordinateOffset node is not found. Please update Helios firmware.\n";
        return 0;
      }

      // check if Helios2 camera used for the example
      bool isHelios2 = false;
      GenICam::gcstring deviceModelName = Arena::GetNodeValue<GenICam::gcstring>(pDevice->GetNodeMap(), "DeviceModelName");
      std::string deviceModelName_tmp = deviceModelName.c_str();
      if (deviceModelName_tmp.rfind("HLT", 0) == 0 || deviceModelName_tmp.rfind("HTP", 0) == 0)
      {
        isHelios2 = true;
      }


      // get node values that will be changed in order to return their values at
      // the end of the example
      pixelFormatInitial = Arena::GetNodeValue<GenICam::gcstring>(pNodeMap, "PixelFormat");
      operatingModeInitial = Arena::GetNodeValue<GenICam::gcstring>(pNodeMap, "Scan3dOperatingMode");

      // Set pixel format; Helios2 - has only Coord3D_ABCY16
      std::cout << TAB1 << "Set " << PIXEL_FORMAT << " to pixel format\n";

      Arena::SetNodeValue<GenICam::gcstring>(pNodeMap, "PixelFormat", PIXEL_FORMAT);

      // set operating mode distance
      if (isHelios2)
      {
        std::cout << TAB1 << "Set 3D operating mode to Distance3000mm\n";
        Arena::SetNodeValue<GenICam::gcstring>(pNodeMap, "Scan3dOperatingMode", "Distance3000mmSingleFreq");
      }
      else
      {
        std::cout << TAB1 << "Set 3D operating mode to Distance1500mm\n";
        Arena::SetNodeValue<GenICam::gcstring>(pNodeMap, "Scan3dOperatingMode", "Distance1500mm");
      }

      // get the coordinate scale in order to convert x, y and z values to mm as
      // well as the offset for x and y to correctly adjust values when in an
      // unsigned pixel format
      std::cout << TAB1 << "Get xyz coordinate scales and offsets\n\n";

      Arena::SetNodeValue<GenICam::gcstring>(pNodeMap, "Scan3dCoordinateSelector", "CoordinateA");
      // getting scaleX as float by casting since SetPly() will expect it passed as
      // float
      scaleX = static_cast<float>(Arena::GetNodeValue<double>(pNodeMap, "Scan3dCoordinateScale"));
      // getting offsetX as float by casting since SetPly() will expect it passed
      // as float
      offsetX = static_cast<float>(Arena::GetNodeValue<double>(pNodeMap, "Scan3dCoordinateOffset"));
      Arena::SetNodeValue<GenICam::gcstring>(pNodeMap, "Scan3dCoordinateSelector", "CoordinateB");
      scaleY = Arena::GetNodeValue<double>(pNodeMap, "Scan3dCoordinateScale");
      // getting offsetY as float by casting since SetPly() will expect it passed
      // as float
      offsetY = static_cast<float>(Arena::GetNodeValue<double>(pNodeMap, "Scan3dCoordinateOffset"));
      Arena::SetNodeValue<GenICam::gcstring>(pNodeMap, "Scan3dCoordinateSelector", "CoordinateC");
      scaleZ = Arena::GetNodeValue<double>(pNodeMap, "Scan3dCoordinateScale");

      // enable stream auto negotiate packet size
      Arena::SetNodeValue<bool>(pDevice->GetTLStreamNodeMap(), "StreamAutoNegotiatePacketSize", true);

      // enable stream packet resend
      Arena::SetNodeValue<bool>(pDevice->GetTLStreamNodeMap(), "StreamPacketResendEnable", true);

      // retrieve image
      std::cout << TAB2 << "Acquire image\n";

      pDevice->StartStream();

      return 1;
    }

    void DisposeCamera()
    {
      // clean up
      pInput = NULL;
      delete[] pInput;
      pIn = NULL;
      delete[] pIn;
      pDevice->RequeueBuffer(pImage);
      pDevice->StopStream();

      // return nodes to their initial values
      Arena::SetNodeValue<GenICam::gcstring>(pNodeMap, "Scan3dOperatingMode", operatingModeInitial);
      Arena::SetNodeValue<GenICam::gcstring>(pNodeMap, "PixelFormat", pixelFormatInitial);
      std::cout << TAB1 << "Nodes were set back to initial values\n";
    }

    // demonstrates acquiring 3D data for a specific point
    // (1) gets image
    // (2) interprets ABCY data to get x, y, z and intensity
    // (3) stores data for point with min and max z values
    // (4) displays 3D data for min and max points
    void AcquireImageAndInterpretData(Arena::IDevice* pDevice)
    {
      pImage = pDevice->GetImage(IMAGE_TIMEOUT);

      // prepare info from input buffer
      size_t width = pImage->GetWidth();
      size_t height = pImage->GetHeight();
      size_t size = width * height;
      size_t srcBpp = pImage->GetBitsPerPixel();
      size_t srcPixelSize = srcBpp / 8;
      pInput = pImage->GetData();
      pIn = pInput;

      // using strcmp to avoid conversion issue
      int compareResult_ABCY16 = strcmp(PIXEL_FORMAT, "Coord3D_ABCY16");	 // if they are equal compareResult_ABCY16 = 0

      bool isSignedPixelFormat = false;

      pcl::PointCloud<pcl::PointXYZRGB> cloud_;

      // if PIXEL_FORMAT is equal to Coord3D_ABCY16
      if (compareResult_ABCY16 == 0)
      {
        for (size_t i = 0; i < size; i++)
        {
          // Extract point data to signed 16 bit integer
          //    The first channel is the x coordinate, second channel is the y
          //    coordinate, the third channel is the z coordinate and the
          //    fourth channel is intensity. We offset pIn by 2 for each
          //    channel because pIn is an 8 bit integer and we want to read it
          //    as a 16 bit integer.
          uint16_t x = *reinterpret_cast<const uint16_t*>(pIn);
          uint16_t y = *reinterpret_cast<const uint16_t*>((pIn + 2));
          uint16_t z = *reinterpret_cast<const uint16_t*>((pIn + 4));
          uint16_t intensity = *reinterpret_cast<const uint16_t*>((pIn + 6));

          // if z is less than max value, as invalid values get filtered to
          // 65535
          if (z < 65535)
          {
            // Convert x, y and z to millimeters
            //    Using each coordinates' appropriate scales, convert x, y
            //    and z values to m. For the x and y coordinates in an
            //    unsigned pixel format, we must then add the offset to our
            //    converted values in order to get the correct position in
            //    millimeters. Afterwards, the values get converted into m 
            //    for the conversion into a sensor_msg pointcloud
            pcl::PointXYZRGB pt;
            pt.r = 255;
            pt.g = 255;
            pt.b = 255;
            pt.x = (float(x) * scaleX + offsetX) * 0.001f;
            pt.y = (float(y) * scaleY + offsetZ) * 0.001f;;
            pt.z = (float(z) * scaleY + offsetZ) * 0.001f;;
          }

          pIn += srcPixelSize;
        }

        pDevice->RequeueBuffer(pImage);

        auto pc2_msg_ = std::make_shared<sensor_msgs::msg::PointCloud2>();
        pcl::toROSMsg(cloud_, *pc2_msg_);
        pc2_msg_->header.frame_id = "map";
     
        pc2_msg_->header.stamp = now();
        publisher_pointcloud_->publish(*pc2_msg_.get());

        RCLCPP_INFO(this->get_logger(), "Publishing point cloud");
      }
      else
      {
        std::cout << "The tof publisher requires the camera to be in either 3D image format Coord3D_ABCY16\n\n";
      }
    }


  private:

    void timer_callback_message()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, world! " + std::to_string(count_++);
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
    }

    void timer_callback_pointcloud()
    {
      pcl::PointCloud<pcl::PointXYZRGB> cloud_;
      auto num_points_ = 1000;

      for (int i = 0; i < num_points_; ++i) {
        const float fr = static_cast<float>(i) / static_cast<float>(num_points_);
        pcl::PointXYZRGB pt;
        pt = pcl::PointXYZRGB(fr * 255, 255 - fr * 255, 18 + fr * 20);
        pt.x = cos(fr * M_PI * 2.0) * 1.0;
        pt.y = sin(fr * M_PI * 2.0) * 1.0;
        pt.z = 0.0;
        cloud_.points.push_back(pt);
      }

      auto pc2_msg_ = std::make_shared<sensor_msgs::msg::PointCloud2>();
      pcl::toROSMsg(cloud_, *pc2_msg_);
      pc2_msg_->header.frame_id = "map";
     

      pc2_msg_->header.stamp = now();
      publisher_pointcloud_->publish(*pc2_msg_.get());

      RCLCPP_INFO(this->get_logger(), "Publishing point cloud");
    }

    Arena::IImage*  pImage;
    Arena::ISystem* pSystem;
    Arena::IDevice* pDevice;
    GenApi::INodeMap* pNodeMap;
    const uint8_t* pInput;
    const uint8_t* pIn;
    GenICam::gcstring pixelFormatInitial;
    GenICam::gcstring operatingModeInitial;
    float scaleX, scaleY, scaleZ;
    float offsetX, offsetY, offsetZ;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr timer_pointcloud_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_pointcloud_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<MinimalPublisher>();
  node->InitializeCamera();
  rclcpp::spin(node);
  node->DisposeCamera();
  rclcpp::shutdown();
  
  return 0;
}