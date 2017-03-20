#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

pcl::visualization::CloudViewer viewer("Cloud Viewer");

void cloud_callback (const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  pcl::PCLPointCloud2 pcl_pc2;
  pcl_conversions::toPCL(*cloud_msg,pcl_pc2);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::fromPCLPointCloud2(pcl_pc2,*cloud);

  viewer.showCloud(cloud);
}

int main (int argc, char** argv)
{
  ros::init (argc, argv, "node_1");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe ("/velodyne_points", 1, cloud_callback);

  ros::spin ();
}
