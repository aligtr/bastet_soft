#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include "rc.hpp"

int main(int argc, char **argv){
    ros::init(argc, argv, "mpc");
    ros::NodeHandle nh;
    ros::Publisher feedbackPublisher  = nh.advertise<nav_msgs::Path>("path", 1000);
    ros::Rate loop_rate(5);
    while (ros::ok()){
        ROS_INFO("start");
        
        ROS_INFO("finish");

        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}