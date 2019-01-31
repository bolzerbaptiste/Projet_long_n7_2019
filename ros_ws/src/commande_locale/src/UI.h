/*
 * ********************************* *
 * Copyright 2016, STEC Projet Long. *
 * All rights reserved.  	     *
 * ********************************* *
*/


#ifndef VAR_UI
#define VAR_UI

#include <ros/ros.h>
#include <string>
#include <math.h>
#include <vector>

// Image Streaming
#include <image_transport/image_transport.h>

#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <cv_bridge/cv_bridge.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <commande_locale/Msg_SensorState.h>
#include "vrepController.h"
#include "configuration.h"
#include <ros/package.h>



class UI
{
	private:	
		vrepController* VREPController;		// Attribut de type v-rep controleur permet de controler la simu v-rep 
		Configuration* configuration;		// Attribut de type configuration 
		
		cv::Mat imageSensor;			// Image correspondant au schéma de la cellule
		cv::Mat imageSimu;			// Image de la simu récupérée sur v-rep
		cv::Mat imageTot;			// Image totale de l'interface 
		cv::Mat playButton;			// Bouton de marche	
		cv::Mat playButton_Down;		// Bouton de marche lorsqu'il est appuyé
		cv::Mat playButton_On;			// Bouton de marche lorsque la souris est dessus
		cv::Mat pauseButton;			// Bouton pause
		cv::Mat pauseButton_Down;		// Bouton pause lorsque l'on appuie dessus
		cv::Mat pauseButton_On;			// Bouton pause lrosque la souris est dessus
		cv::Mat shuttleButton;			// Bouton navette 
		cv::Mat shuttleButton_Down;		// Bouton navette lorsque l'on apuie dessus 
		cv::Mat shuttleButton_On;		// Bouton navette lorsque la souris est dessus			
		cv::Mat modeButton;			// Bouton mode
		cv::Mat modeButton_On;                  // Bouton mode lorsque la souris est dessus
		cv::Mat modeRandButton;			// Bouton random
		cv::Mat modeRandButton_On;		// Bouton randon appuyé
		cv::Mat modeManuButton;			// Bouton mode manuel
		cv::Mat modeManuButton_On;		// Bouton mode manuel appuyé 
		cv::Mat modeAutoButton;			// Bouton mode auto 
		cv::Mat modeAutoButton_On;		// Bouton mode auto appuyé 
		
		cv::Mat TERbutton;			// Bouton TER 
		cv::Mat TERbutton_down;			// Bouton TER appuyé
		cv::Mat TERbutton_on;			// Bouton TER lorsque la souris passe dessus 

		int mode;				// Variable contenant l'état de la simu 0 = pause, 1 = play
		int modeShuttle;
		int modeTER;
		std::string TxtNomProduits;
		
		int typeNextShuttle; 

		image_transport::Subscriber subImage;	// Subscriber pour recuperer l'image depuis la simu V-rep
		ros::Publisher pubStateButton;		// Publisher pour envoyer l'état du bouton
		ros::Publisher pubStateTERbutton;	// Publisher pour envoyer l'état du bouton 

		ros::Subscriber subNombreDeProduits; 	// Subscriber pour récuperer le nombre de produits 
		ros::Subscriber subNomProduits;		// Subscriber pour récuperer le nom des produits

	public:
		UI(vrepController* VREPContrl, Configuration* config);    
		void DrawRailSensorImg(commande_locale::Msg_SensorState SensorState);			// Gere l'affichage de l'état des capteurs des rails
		void DrawStopSensorImg(commande_locale::Msg_SensorState SensorState);			// Gere l'affichage de l'état des capteurs des stops
		void DrawStationSensorImg(commande_locale::Msg_SensorState SensorState);		// Gere l'affichage de l'etat des capteurs des stations de travail
		void DrawSwitchSensorImg(commande_locale::Msg_SensorState SensorState);			// Gere l'affichage de l'etat des aiguillage
		void init(ros::NodeHandle nh);								// Initialisation de l'interface de simulation
		void update();
		void getSimuStream(const sensor_msgs::ImageConstPtr& msg);				// Récupère le stream de la simu depuis V-rep pour l'afficher sur l'interface de simulation
		void onMouse_internal( int event, int x, int y);
		friend void onMouse(int event, int x, int y, int, void* userdata);
		void close();
		bool checkWindow();
		void NombreDeProduitsCallBack(const std_msgs::Int32::ConstPtr& NbMsg);			// Affiche le nombre de produit à fabriquer dans la simulation 
		void NomProduitsCallBack(const std_msgs::String::ConstPtr& NomMsg); 		// Affiche le nom des produits à fabriquer dans la simulation
		
	
};

#endif
