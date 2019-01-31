/*
 * ************************************* *
 * Copyright 2016, TER Ligne Transitique *
 * All rights reserved.  	         *
 * ************************************* *
*/


#include <ros/ros.h>
#include <unistd.h>
#include "A3.h"


using namespace std;

#define NOMBRE_PLACE 100
#define RESET   "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */


void SensorCallback()
{
	cout<<"~~~~~~~~Capteur actif~~~~~~~~~~"<<endl;
}


int main(int argc, char **argv)
{	

//initialisation du noeud ros et création d'un handle associé au noeud
	ros::init(argc, argv, "aiguillage_3");	
	ros::NodeHandle noeud;

	A3 Aig3(noeud);

	ros::Rate loop_rate(25); //fréquence de la boucle 



	
	
//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////


cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
cout <<"   Aiguillage 3  "<<endl;
cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;

int mode = 1; // Mode automatique

if(mode==1){cout << "\t Mode Automatique"<< endl;}

if(mode==0){cout << "\t Mode Manuel"<< endl;}
	
	while (ros::ok())
	{

		
		if(mode==1){
			//cout << "\t Mode Automatique"<< endl;
			Aig3.Aiguille_Navette();
		}

		if(mode==0){
			//cout << "\t Mode Manuel"<< endl;
			Aig3.ModeManuel();
		}
		

		ros::spinOnce(); //permet aux fonction callback de ros dans les objets d'êtres appelées
		loop_rate.sleep(); //permet de synchroniser la boucle while. Il attend le temps qu'il reste pour faire le 25Hz (ou la fréquence indiquée dans le loop_rate)
	}

	return 0;


}
