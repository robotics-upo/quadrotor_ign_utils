#include <ros/ros.h>
#include "LeeVelocityController.cc"
#include <string>


int main(int argc, char **argv)
{
    std::string node_name = "lee_velocity_controller_node";

	ros::init(argc, argv, node_name);


    ros::spinOnce();
    createGrid(node_name);


    return 0;
}