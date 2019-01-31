/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/


#ifndef COMMANDE_SIMU
#define COMMANDE_SIMU

#include "vrep_common/simRosEnablePublisher.h"
#include "vrep_common/simRosEnableSubscriber.h"

#include <ros/ros.h>
#include "actionneurs.h"
#include "capteurs.h" 
#include "robots.h"
#include <std_msgs/Bool.h>
//#include "postes/productPost.h"

#include <std_msgs/Int32.h>
#include <commande_locale/Msg_StopControl.h>
#include <shuttles/msgShuttleChange.h>
#include <shuttles/srvGetShuttleStatus.h>
#include <shuttles/srvGetEmptyShuttles.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "productPost.h"
#include <map>
#include "aiguillages/ExchangeSh.h"

class Commande
{
private:

//Subscriber

	// Start/Stop Navettes
	ros::Subscriber SubArretNavette;
	ros::Subscriber SubDemarreNavette;

	// Aiguillages
	ros::Subscriber SubDeverouilleAiguillages;
	ros::Subscriber SubVerouilleAiguillages;
	ros::Subscriber SubAiguillagesGauches;
	ros::Subscriber SubAiguillagesDroits;

	// Ergots
	ros::Subscriber subPinOn;
	ros::Subscriber subPinOff;

	// Postes
	ros::Subscriber subEmptyShuttleReadyP1;
	ros::Subscriber subEmptyShuttleReadyP2;
	ros::Subscriber subEmptyShuttleReadyP3;
	ros::Subscriber subEmptyShuttleReadyP4;

	ros::Subscriber subProductInPostP1;
	ros::Subscriber subProductInPostP2;
	ros::Subscriber subProductInPostP3;
	ros::Subscriber subProductInPostP4;

	

//Publisher

	// Actionneurs
	ros::Publisher pub_navettes_stops;
	ros::Publisher pub_actionneurs_simu_aiguillages;
        ros::Publisher pub_actionneurs_simu_pins;

	// Vers Postes
	ros::Publisher PubDemarrerNavetteP1;
	ros::Publisher PubDemarrerNavetteP2;
	ros::Publisher PubDemarrerNavetteP3;
	ros::Publisher PubDemarrerNavetteP4;

	ros::Publisher pubProductTakenByRobotP1;
	ros::Publisher pubProductTakenByRobotP2;
	ros::Publisher pubProductTakenByRobotP3;
	ros::Publisher pubProductTakenByRobotP4;

	ros::Publisher pubProductPutOnShuttleP1;
	ros::Publisher pubProductPutOnShuttleP2;
	ros::Publisher pubProductPutOnShuttleP3;
	ros::Publisher pubProductPutOnShuttleP4;

	// Vers shuttles
	ros::Publisher pubDeleteShuttleScheduler;
	ros::Publisher pubDestinationChange;
	shuttles::msgShuttleChange Newdestination;
	ros::Publisher pubDestroyShuttle;
	ros::Publisher pubDeleteShuttle;
	
	ros::Subscriber NewShuttle;

//Services
	//Services shuttle
	ros::ServiceClient client_GetShuttleState;
	shuttles::srvGetShuttleStatus srv_GetShuttleState;

	ros::ServiceClient client_GetEmptyShuttle;
	shuttles::srvGetEmptyShuttles srv_GetEmptyShuttle;


//Variables

	bool ProduitEnP1, ProduitEnP2, ProduitEnP3, ProduitEnP4;
	int NavetteVideEnP1, NavetteVideEnP2, NavetteVideEnP3, NavetteVideEnP4;

	int NavetteEnP1,NavetteEnP2,NavetteEnP3,NavetteEnP4;

	int NewHandle;

	std::map<int,ProductPost*> ProductsMap;


// Initialisation 

	/* Capteurs */
	bool PSx[25],DxD[13],DxG[13],CPx[11],CPIx[9];  

	/* Actionneurs */
	bool STx[25],RxD[13],RxG[13],Vx[13],Dx[13],PIx[9];

public:
	commande_locale::Msg_StopControl actionneurs_simulation_Stop;
	commande_locale::Msg_SwitchControl actionneurs_simulation_Aiguillages;
	commande_locale::Msg_PinControl actionneurs_simulation_Pin;
	

	Commande(ros::NodeHandle noeud, std::string executionPath);
	

	void Initialisation();

	void ArretNavette(const std_msgs::Int32::ConstPtr& msg);
	void DemarreNavette(const std_msgs::Int32::ConstPtr& msg);

	void DeverouilleAiguillages(const std_msgs::Int32::ConstPtr& msg);
	void VerouilleAiguillages(const std_msgs::Int32::ConstPtr& msg);
	void Aiguillagesgauches(const std_msgs::Int32::ConstPtr& msg);
	void Aiguillagesdroits(const std_msgs::Int32::ConstPtr& msg);

	void SortirErgotCallback(const std_msgs::Int32::ConstPtr& msg);
	void RentrerErgotCallback(const std_msgs::Int32::ConstPtr& msg);

	void GestionNavetteVideP1Callback(const std_msgs::Int32::ConstPtr& msg);
	void GestionNavetteVideP2Callback(const std_msgs::Int32::ConstPtr& msg);
	void GestionNavetteVideP3Callback(const std_msgs::Int32::ConstPtr& msg);
	void GestionNavetteVideP4Callback(const std_msgs::Int32::ConstPtr& msg);

	void ProductInPostP1Callback(const std_msgs::Int32::ConstPtr& msg);
	void ProductInPostP2Callback(const std_msgs::Int32::ConstPtr& msg);
	void ProductInPostP3Callback(const std_msgs::Int32::ConstPtr& msg);
	void ProductInPostP4Callback(const std_msgs::Int32::ConstPtr& msg);

	void NewShuttleCallBack(const aiguillages::ExchangeSh::ConstPtr& msg);

	void initProduct(int nDestination, int pNumber);


	//Fonctions haut niveau 
	void PiecePrise(int numPoste);
	void PieceDeposee(int numPoste);

	void DefinirDestination(int handle, int destination);

	int ProduitSurNavette(int handle);		//Renvoie la destination du produit présent sur la navette
	int NavetteStoppee(int numPoste); 		//Renvoie l'handle de la navette stoppée au niveau du poste numPoste si elle contient un produit, 0 sinon
	int NavetteStoppeeVide(int numPoste); 		//Renvoie l'handle de la navette stoppée au niveau du poste numPoste si elle est vide, 0 sinon
	void NavettePartie(int numPoste);		//Remet la variable Navette en Pi à 0;
	int NavetteDisponible();			//Renvoie le handle d'une navette vide dans d0
	int NouvelleNavette(); 				//Renvoie le handle de la navette qui est créée par le noeud Ordonnancement
	void ReinitialiserNouvelleNavette();		//Réinitialise le handle de la navette nouvellement créée
	void DestroyShuttle(int handle);		//Détruit la navette qui porte le shuttle


};


#endif
