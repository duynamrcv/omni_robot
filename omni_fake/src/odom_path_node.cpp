#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include <iostream>
using namespace std;

nav_msgs::Odometry odom;
void odomCallback(const nav_msgs::Odometry &msg) { odom = msg; }

int main(int argc, char** argv)
{
    ros::init(argc, argv, "odom_path");
    ros::NodeHandle nh;

    ros::Subscriber sub_odom = nh.subscribe("/odom", 10, odomCallback);
    ros::Publisher pub_odom_path = nh.advertise<nav_msgs::Path>("/odom_path", 10);

    nav_msgs::Path odom_path;
    geometry_msgs::PoseStamped poses;

    ros::Rate r(10);
    while (nh.ok())
    {
        odom_path.header = odom.header;
        poses.header = odom_path.header;
        poses.pose = odom.pose.pose;
        odom_path.poses.push_back(poses);

        pub_odom_path.publish(odom_path);

        ros::spinOnce();
        r.sleep();
    }
    return 0;
}