/**** Projet long N7 2017 ****/

#include "robot1.h"

#include <ros/ros.h>


int main(int argc, char **argv)
{
	//Initialisation du noeud ROS
	ros::init(argc,argv,"robot1");
	ros::NodeHandle nh;

	//CmdRobot
	Robot1 Robot1;
	Robot1.init(nh);

	while(ros::ok())
	{
		ros::spinOnce();
	}
}
