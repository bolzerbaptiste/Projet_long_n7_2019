/**** Maxime Maurin - Projet Long N7 2017 ****/

#include <ros/ros.h>
#include "shuttleManager.h"


int main (int argc, char **argv)
{

// Initialisation du noeud
ros::init(argc, argv, "commande_navette");	
ros::NodeHandle nh;

//Définition de la fréquence
ros::Rate loop_rate(25);
std::string name = ros::this_node::getName();

//Initialisation du ShuttleManager
ShuttleManager myshuttleManager;
myshuttleManager.init(nh);

ROS_INFO("Noeud commande_navette initialise : %s", name.c_str());


  while (ros::ok())
  {

	ros::spinOnce();
	loop_rate.sleep();

  }


  return 0;
}
