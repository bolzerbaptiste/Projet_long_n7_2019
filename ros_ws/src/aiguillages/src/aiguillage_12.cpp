/*
 * ************************************* *
 * Copyright 2016, TER Ligne Transitique *
 * All rights reserved.  	         *
 * ************************************* *
*/

#include <ros/ros.h>
#include <unistd.h>
#include "A12.h"

using namespace std;

#define NOMBRE_PLACE 100
#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */


void SensorCallbackd()
{
	cout<<"~~~~~~~~Capteur actif~~~~~~~~~~"<<endl;
}

void SensorCallbackg()
{
	cout<<"~~~~~~~~Capteur actif~~~~~~~~~~"<<endl;
}

int main(int argc, char **argv)
{	

//initialisation du noeud ros et création d'un handle associé au noeud
	ros::init(argc, argv, "aiguillage_12");	//numéro de l'aiguillage
	ros::NodeHandle noeud;

	A12 Aig(noeud);


	ros::Rate loop_rate(25); //fréquence de la boucle 

	

	while (ros::ok())
	{
		Aig.Aiguille_Navette();
		
		ros::spinOnce(); //permet aux fonction callback de ros dans les objets d'êtres appelées
		loop_rate.sleep(); //permet de synchroniser la boucle while. Il attend le temps qu'il reste pour faire le 25Hz (ou la fréquence indiquée dans le loop_rate)
	}

	return 0;


}
