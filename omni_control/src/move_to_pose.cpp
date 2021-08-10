#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

#include <iostream>

using namespace std;

nav_msgs::Odometry odom;
void odomCallback(const nav_msgs::Odometry &msg) { odom = msg;}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "move2pose");
    ros::NodeHandle nh;

    ros::Subscriber sub_odom = nh.subscribe("/odom", 10, odomCallback);
    ros::Publisher pub_vel = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::Rate r(10);
    while(nh.ok())
    {
        float pose[3], vel[3];
        // Pose
        pose[0] = odom.pose.pose.position.x;    // x
        pose[1] = odom.pose.pose.position.y;    // y
        
        // Get theta from pose 
        double q0 = odom.pose.pose.orientation.x;
		double q1 = odom.pose.pose.orientation.y;
		double q2 = odom.pose.pose.orientation.z;
		double q3 = odom.pose.pose.orientation.w;

        pose[3] = atan2(2.0*(q2*q3 + q0*q1), 1.0 - 2.0*(q1*q1 + q2*q2)); // theta

        // Velocity:
        vel[0] = odom.twist.twist.linear.x;     // vx
        vel[1] = odom.twist.twist.linear.y;     // vy
        vel[2] = odom.twist.twist.angular.z;    // omega


        ros::spinOnce();
        r.sleep();
    }
    return 0;
}