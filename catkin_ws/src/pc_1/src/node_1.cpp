#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
// #include <pcl/io/io.h>
// #include <pcl/io/pcd_io.h>

// int user_data;

// void viewerOneOff (pcl::visualization::PCLVisualizer& viewer)
// {
// 	viewer.setBackgroundColor (1.0, 0.5, 1.0);
// 	pcl::PointXYZ o;
// 	o.x = 1.0;
// 	o.y = 0;
// 	o.z = 0;
// 	viewer.addSphere (o, 0.25, "sphere", 0);
// 	std::cout << "i only run once" << std::endl;

// }

// void viewerPsycho (pcl::visualization::PCLVisualizer& viewer)
// {
// 	static unsigned count = 0;
// 	std::stringstream ss;
// 	ss << "Once per viewer loop: " << count++;
// 	viewer.removeShape ("text", 0);
// 	viewer.addText (ss.str(), 200, 300, "text", 0);

//  	user_data++;
// }

void cloud_callback (const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  // pcl::PCLPointCloud2* cloud = new pcl::PCLPointCloud2; 
  // pcl::PCLPointCloud2ConstPtr cloudPtr(cloud);

  // pcl_conversions::toPCL(*cloud_msg, *cloud);

	pcl::PCLPointCloud2 pcl_pc2;
	pcl_conversions::toPCL(*cloud_msg,pcl_pc2);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::fromPCLPointCloud2(pcl_pc2,*cloud);


	// for (size_t i = 0; i < cloud->points.size (); ++i)
	// 	std::cout << " "    << cloud->points[i].x
 //               	  << " "    << cloud->points[i].y
	//               << " "    << cloud->points[i].z << std::endl;

	pcl::visualization::CloudViewer viewer("Cloud Viewer");

    //blocks until the cloud is actually rendered
	viewer.showCloud(cloud);

    //use the following functions to get access to the underlying more advanced/powerful
    //PCLVisualizer

 //    //This will only get called once
	// viewer.runOnVisualizationThreadOnce (viewerOneOff);

 //    //This will get called once per visualization iteration
	// viewer.runOnVisualizationThread (viewerPsycho);
	while (!viewer.wasStopped ())
	{
 //    //you can also do cool processing here
 //    //FIXME: Note that this is running in a separate thread from viewerPsycho
 //    //and you should guard against race conditions yourself...
	// 	user_data++;
	}
}

int main (int argc, char** argv)
{
	ros::init (argc, argv, "node_1");
	ros::NodeHandle nh;

	ros::Subscriber sub = nh.subscribe ("/velodyne_points", 1, cloud_callback);

	ros::spin ();
}