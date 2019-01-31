/**** Maxime Maurin - Projet Long N7 2017 ****/

#ifndef ORDO
#define ORDO

#include <ros/ros.h>
#include <string>
#include <std_msgs/Int32.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <cstdlib>
#include <stdlib.h>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vrep_common/simRosGetInfo.h>
#include <shuttles/srvGetShuttleStatus.h>

#include "scheduling/Msg_LoadShuttle.h"
#include "product.h"

//La classe Scheduler permet la gestion de l'ordonnacement, elle s'initialise par rapport au fichier de configuration 


class Scheduler
{
private:

int maxShuttleNumber;	
int scheduledLaunchDate[10];
int numberOfProduct;
int nextCount;
float lastLaunchDate;
bool init_var;
std::string nom_produits[100];

std::string configFile, logFile;


std::map<int,Product*>::iterator iteratorPMap,iteratorPMapOut;  
std::map<int,Product*> ProductsMap; // la clé est le numéro de la phase de lancement

ros::Publisher pubCreateShuttle, pubDelShuttle;
ros::Subscriber subEndOfProductManufacture,subManualLaunchOfProduct;

ros::ServiceClient client_simRosGetInfo;
vrep_common::simRosGetInfo srv_GetInfoVREP;

ros::ServiceClient client_GetShuttleStatus;
shuttles::srvGetShuttleStatus srv_GetShuttleStatus;

ros::Publisher pubNombreDeProduits;
ros::Publisher pubNomProduits;



public:
	
	Scheduler();
	~Scheduler();
	
	bool init(ros::NodeHandle nh, std::string executionPath);
	
	void initProduct(std::string pName, int pFirstDestination, int initProductNumber, int pManRSize, int order);

	void launchNextSchedule();
	
	void productOutCallBack(const std_msgs::Int32::ConstPtr& msg);
	void ManualLaunchCallBack(const std_msgs::Bool::ConstPtr& msg);
	
};


#endif
