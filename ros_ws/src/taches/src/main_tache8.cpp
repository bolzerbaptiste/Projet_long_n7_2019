/**** Projet long N7 2017 ****/

#include "tache8.h"

#include <ros/ros.h>


int main(int argc, char **argv)
{
	//Initialisation du noeud ROS
	ros::init(argc,argv,"tache8");
	ros::NodeHandle nh;

	Tache8 Tache8;
	Tache8.init(nh,argv[0]);

	while(ros::ok())
	{
		ros::spinOnce();
	}
}
