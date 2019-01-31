/**** Projet long N7 2017 ****/

#include "tache4.h"

#include <ros/ros.h>


int main(int argc, char **argv)
{
	//Initialisation du noeud ROS
	ros::init(argc,argv,"tache4");
	ros::NodeHandle nh;

	Tache4 Tache4;
	Tache4.init(nh,argv[0]);

	while(ros::ok())
	{
		ros::spin();
	}
}
