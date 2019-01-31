/**** Projet long N7 2017 ****/

#include "tache2.h"

#include <ros/ros.h>


int main(int argc, char **argv)
{
	//Initialisation du noeud ROS
	ros::init(argc,argv,"tache2");
	ros::NodeHandle nh;

	Tache2 Tache2;
	Tache2.init(nh,argv[0]);

	while(ros::ok())
	{
		ros::spin();
	}
}
