/*
 * ********************************* *
 * Copyright 2016, STEC Projet Long. *
 * All rights reserved.  	     *
 * ********************************* *
 * Mise à jour par le Projet Long    *
 * ENSEEIHT 2017		     *
 * ********************************* *
*/

#ifndef VREP_CONTROLLER
#define VREP_CONTROLLER

#include <ros/ros.h>
#include <vector>
#include <string>
#include <math.h> 
#include <std_msgs/Int32.h>

#include <vrep_common/simRosLoadModel.h>
#include <vrep_common/simRosRemoveModel.h>
#include <vrep_common/simRosGetObjectHandle.h>
#include <vrep_common/simRosSetIntegerSignal.h>
#include <vrep_common/simRosGetIntegerSignal.h>
#include <vrep_common/simRosPauseSimulation.h>
#include <vrep_common/simRosStartSimulation.h>

#include <shuttles/srvGetShuttleStatus.h>
#include <shuttles/srvGetEmptyShuttles.h>
#include <shuttles/msgShuttleChange.h>
#include <shuttles/msgShuttleCreate.h>

#include "commande_locale/Msg_Color.h"

#include <aiguillages/ExchangeSh.h>


class vrepController
{
	private:
		ros::ServiceClient client_simRosLoadModelInit;
		vrep_common::simRosLoadModel srv_LoadModelInit;

		ros::ServiceClient client_simRosLoadModel;
		vrep_common::simRosLoadModel srv_LoadModel;

		ros::ServiceClient client_simRosRemoveModel;
		vrep_common::simRosRemoveModel srv_RemoveModel;

		ros::ServiceClient client_simRosGetObjectHandle; 
		vrep_common::simRosGetObjectHandle srv_GetObjectHandle;

		ros::ServiceClient client_simRosStartSimulation;
		vrep_common::simRosStartSimulation srv_StartSimulation;	

		ros::ServiceClient client_simRosPauseSimulation;
		vrep_common::simRosPauseSimulation srv_PauseSimulation;

		ros::ServiceClient client_simRosModelColor;
		vrep_common::simRosSetIntegerSignal srv_ModelColor;

		ros::ServiceClient client_simRosModelColorVerif;
		vrep_common::simRosGetIntegerSignal srv_ModelColor_Verif;

// Gestion de navettes
		ros::Publisher pub_Shuttle_Handle;
		aiguillages::ExchangeSh Sh_Handle;
		
		ros::Subscriber DeleteShuttle;
		ros::Publisher createShuttle;
		shuttles::msgShuttleCreate Cr_Shuttle;

		ros::Subscriber ChangeColor;
		
		int nShuttleF;
		std::string SimulationFileName;
	public:
		vrepController ();
		void init(ros::NodeHandle n,std::string executionPath, std::string simulationFileName);
		void close();
		void loadModelInit(char shuttleNumber);
		void removeModel(int32_t handle);
		int32_t getObjectHandle(std::string);
		void waitVrep();
		void play();
		void pause();
		void deleteShuttleCallBack(const aiguillages::ExchangeSh::ConstPtr& msg);

		int LoadShuttle(char shuttleNumber, int product, int firstDestination);
		void setSimulationFile(std::string);
		void addNewShuttle(int handle_navette, int handle_plateforme, int type, int destination); 
		void ColorCallBack(const commande_locale::Msg_Color::ConstPtr& msg);
};

#endif
