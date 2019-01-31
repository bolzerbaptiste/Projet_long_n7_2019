/**** Projet long N7 2017 ****/

#include "tache5.h"

#include <ros/ros.h>


int main(int argc, char **argv)
{
	//Initialisation du noeud ROS
	ros::init(argc,argv,"tache5");
	ros::NodeHandle nh;

	Tache5 Tache5;
	Tache5.init(nh,argv[0]);

	while(ros::ok())
	{
		ros::spinOnce();
	}
}
