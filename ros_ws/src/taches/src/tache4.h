/**** Projet long N7 2017 ****/

#ifndef TACHE4
#define TACHE4

#include <ros/ros.h>

//Services V-Rep
#include <vrep_common/simRosSetIntegerSignal.h>
#include <vrep_common/simRosGetInfo.h>

//Messages
#include <std_msgs/Int32.h>

//Lecture Fichier
#include <map>
#include <string.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <unistd.h>

#include "productTache.h"



class Tache4
{
private:

	/** Services V-Rep **/
	//Service simRosSetIntegerSignal
	ros::ServiceClient client_simRosColor;
	vrep_common::simRosSetIntegerSignal srv_simRosColor;

	//Service simRosGetInfo
	ros::ServiceClient client_simGetVrepTime;
	vrep_common::simRosGetInfo srv_simGetVrepTime;	

	/** Subscribers **/
	ros::Subscriber robotPosition;
	ros::Subscriber robotBras;
	ros::Subscriber robotPince;
	ros::Subscriber posteProduit;
	
	/** Publishers **/
	ros::Publisher pub_traitementProduitTache;
	ros::Publisher pub_retourTraitement;

	/** Variables **/
	int position;
	int bras;
	int pince;
	
	float t0, time;

	int produit, oldproduit;
	int finTraitement;
	std::string table;	

	/** Messages **/
	std_msgs::Int32 retourTraitement;
	std_msgs::Int32 traitementProduit;

	/** Map produits **/
	std::map<int,ProductTache*> ProductsMap;
	std::map<int,ProductTache*>::iterator iteratorPMap;


public:

	Tache4();
	~Tache4();

	//Initialisation
	void init(ros::NodeHandle noeud, std::string executionPath);
	
	//Fonction interne permettant d'évacuer le produit de la table lorsque le robot l'a récupéré
	void FinTraitementProduit(int numTable);

	//Fonctions permettant de connaître la position du robot ainsi que l'état de la pince et du bras
	void PositionRobotCallback(const std_msgs::Int32::ConstPtr& msg);
	void BrasRobotCallback(const std_msgs::Int32::ConstPtr& msg);
	void PinceRobotCallback(const std_msgs::Int32::ConstPtr& msg);

	//Fonction permettant le traitement d'un produit à la réception du message venant du noeud Poste associé
	void TraitementProduitCallback(const std_msgs::Int32::ConstPtr& msg);

	//Fonction init pour le fichier de configuration
	void initProduct(int nJobtime, int pNumber);
};

#endif 
