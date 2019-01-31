/**** Projet long N7 2017 ****/

#include "tache7.h"

#include <ros/ros.h>


int main(int argc, char **argv)
{
	//Initialisation du noeud ROS
	ros::init(argc,argv,"tache7");
	ros::NodeHandle nh;

	Tache7 Tache7;
	Tache7.init(nh,argv[0]);

	while(ros::ok())
	{
		ros::spinOnce();
	}
}
