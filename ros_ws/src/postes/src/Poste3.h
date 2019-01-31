/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#ifndef POSTE
#define POSTE

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <unistd.h>
#include <list>
#include <cstdlib>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <shuttles/srvGetShuttleStatus.h>
#include <shuttles/srvGetEmptyShuttles.h>
#include <shuttles/msgShuttleChange.h>
#include <shuttles/msgShuttleCreate.h>
#include <aiguillages/ExchangeSh.h>
#include <vrep_common/simRosSetIntegerSignal.h>
#include <vrep_common/simRosEnablePublisher.h>
#include <vrep_common/simRosEnableSubscriber.h>
#include <commande_locale/Msg_Color.h>

#include "productPost.h"


using namespace std;


class Poste3
{
private:

	//Subscribe Sensor
	ros::Subscriber VREPsubStopSensor;

public:

	Poste3(ros::NodeHandle nh,  std::string executionPath);
	void StopSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void NewShuttleCallback (const aiguillages::ExchangeSh::ConstPtr& msg);
	void StartShuttleCallback(const std_msgs::Int32::ConstPtr& msg);
	void ProductPutOnShuttleCallback(const std_msgs::Int32::ConstPtr& msg);
	void ProductTakenByRobotCallback(const std_msgs::Int32::ConstPtr& msg);
	void TaskFinishedCallback(const std_msgs::Int32::ConstPtr& msg);
	void initProduct(int nDestination, int pNumber);

	//  Init of the variables
	bool PS2;	// Stop Sensor 2 
	bool PS2_past;

	int tache;
	int poste_libre;
	int prod_recup;

	int num_capt_stop;
	std_msgs::Int32 num_STOP;

	int num_ergot;
	std_msgs::Int32 num_PIN;

	int nouveau_produit;

	// Init of the lists
	std::list<int> handlesShuttles;
	std::list<int> destinationsShuttles;
	std::list<int> productShuttles;

	// Lists used only in the main
	std::list<int> handlesShuttlesMain;
	std::list<int> destinationsShuttlesMain;
	std::list<int> productShuttlesMain;

	// Init Of Map
	std::map<int,ProductPost*> ProductsMap;

	// Publisher and suscriber for the shuttle recognition (communication with the switchpoints)
	ros::Publisher pubSendShuttle;
	ros::Subscriber subReceiveShuttle;

	// Stop and start the shuttles
	ros::Publisher ShStop;
	ros::Publisher ShStart;

	// Pin control
	ros::Publisher pubPinOn;
	ros::Publisher pubPinOff;
	
	// To communicate with the shuttles' services
	ros::ServiceClient clientGetShuttleStatus;
	shuttles::srvGetShuttleStatus ShuttleInfo;

	ros::Publisher pubProductChange;
	shuttles::msgShuttleChange NewProduct;

	ros::Publisher pubDestinationChange;
	shuttles::msgShuttleChange Newdestination;


	// To communicate with the Command
	ros:: Subscriber subStartShuttle;
	ros:: Subscriber subProductPutOnShuttle;
	ros:: Subscriber subProductTakenByRobot;

	ros::Publisher pubEmptyShuttleReady;
	ros::Publisher pubProductInPost;

	//To communicate with Task
	ros:: Subscriber subTaskFinished;
	ros::Publisher pubProductToTask;

	// To change the color
	ros::Publisher pubChangeColor;
	commande_locale::Msg_Color PlatformColor;

};

#endif
