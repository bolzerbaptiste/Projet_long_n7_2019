/**** Projet long N7 2017 ****/

#include "tache3.h"

#include <ros/ros.h>


int main(int argc, char **argv)
{
	//Initialisation du noeud ROS
	ros::init(argc,argv,"tache3");
	ros::NodeHandle nh;

	Tache3 Tache3;
	Tache3.init(nh,argv[0]);

	while(ros::ok())
	{
		ros::spin();
	}
}
