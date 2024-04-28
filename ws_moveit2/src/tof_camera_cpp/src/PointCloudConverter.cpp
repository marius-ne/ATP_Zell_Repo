#include "../include/PointCloudConverter.h"

#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <pcl_conversions/pcl_conversions.h>

std::shared_ptr<sensor_msgs::msg::PointCloud2> PointCloudConverter::Convert(Arena::IImage *img)
{
    
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

        return cloud_;
    }
    else
    {
        std::cout << "The tof publisher requires the camera to be in either 3D image format Coord3D_ABCY16\n\n";
    }
}