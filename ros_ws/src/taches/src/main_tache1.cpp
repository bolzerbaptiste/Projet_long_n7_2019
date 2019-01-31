/**** Projet long N7 2017 ****/

#include "tache1.h"

#include <ros/ros.h>


int main(int argc, char **argv)
{
	//Initialisation du noeud ROS
	ros::init(argc,argv,"tache1");
	ros::NodeHandle nh;

	Tache1 Tache1;
	Tache1.init(nh,argv[0]);

	while(ros::ok())
	{
		ros::spinOnce();
	}
}
