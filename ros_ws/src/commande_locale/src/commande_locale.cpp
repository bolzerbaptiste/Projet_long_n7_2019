/*
 * ********************************* *
 * Copyright 2016, STEC Projet Long. *
 * All rights reserved.  	     *
 * ********************************* *
 * Mise à jour par le Projet Long    *
 * ENSEEIHT 2017		     *
 * ********************************* *
*/


using namespace std; 

#include "vrepController.h"  
#include "UI.h"
#include "inOutController.h"
#include "configuration.h"


#include <ros/ros.h>

int main(int argc, char **argv)
{	
			//Initialisation du noeud ROS
			ros::init(argc, argv, "commande_locale");
			ros::NodeHandle nh;
			
			ROS_INFO("Simulation file: %s \n", argv[1]);

			
			// VREP CONTROLLER
			vrepController VREPController;	
			VREPController.init(nh,argv[0], argv[1]);
			
			// CONFIGURATION
			Configuration config(&VREPController);
			config.init(nh, argv[0]);

			// USER INTERFACE
			UI userInterface(&VREPController,&config);
			userInterface.init(nh);

			// IN & OUT CONTROLLER
			inOutController IOController(&userInterface, &VREPController, &config);
			IOController.init(nh);

			// Demarrage de la simu pour avoir la premiere image
			VREPController.play();

			// Pause pour laisser à l'utilisateur le soin de lancer la simu avec le boutton Play
			VREPController.pause();


			while (ros::ok()) // Tant que ROS est actif,
			{
				ros::spinOnce(); // on lance les callback correspondant aux messages entrants.
			}				
				
			userInterface.close(); // Si Ctrl+C -> On ferme la fenetre de l'UI et on quitte la simulation
			VREPController.close();
			return 0;
}
