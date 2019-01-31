/*
 * ********************************* *
 * Copyright 2016, STEC Projet Long. *
 * All rights reserved.  	     *
 * ********************************* *
 * Mise à jour par le Projet Long    *
 * ENSEEIHT 2017		     *
 * ********************************* *
*/

#ifndef IN_OUT_CONTROLLER
#define IN_OUT_CONTROLLER

#include "UI.h"
#include "configuration.h"
#include "vrepController.h"

#include <ros/ros.h>

#include "commande_locale/Msg_SwitchControl.h"
#include "commande_locale/Msg_StopControl.h"
#include "commande_locale/Msg_PinControl.h"
#include "commande_locale/Msg_SensorState.h"
 
#include <scheduling/Msg_LoadShuttle.h>
#include <vrep_common/simRosEnablePublisher.h>
#include <vrep_common/simRosEnableSubscriber.h>

#include <std_msgs/Int32.h>


class inOutController
{
private:
	UI* userInterface;
	vrepController* vrepServiceAcces;
	Configuration* configuration;	
	
	ros::Publisher VREPSwitchControllerRight;
	ros::Publisher VREPSwitchControllerLeft;
	ros::Publisher VREPSwitchControllerLock;
	ros::Publisher VREPStopController;
	ros::Publisher VREPGoController;
	ros::Publisher planifRailSensorState;
	ros::Subscriber subSensorState;
	ros::Subscriber VREPsubRailSensor;
	ros::Subscriber VREPsubStopSensor;
	ros::Subscriber VREPsubSwitchSensor;
	ros::Subscriber planifSubSwitchState;
	ros::Subscriber planifSubStopState;
	ros::Subscriber planifSubPinState;
	ros::Subscriber subScheduler;

	commande_locale::Msg_StopControl StopControl;
	commande_locale::Msg_PinControl PinControl;
	commande_locale::Msg_SwitchControl SwitchControl;
	commande_locale::Msg_SensorState SensorState;
public:
	inOutController(UI* usrInt, vrepController* vrepSA, Configuration* config);
	void init(ros::NodeHandle nh);
	// Sensors
	void SensorCallbackRail(const std_msgs::Int32::ConstPtr& msg);
	void SensorCallbackStop(const std_msgs::Int32::ConstPtr& msg);
	void SensorCallbackSwitch(const std_msgs::Int32::ConstPtr& msg);
	// Actuators
	void StateSwitchCallBack(const commande_locale::Msg_SwitchControl::ConstPtr&  msg);
	void StateStopCallBack(const commande_locale::Msg_StopControl::ConstPtr&  msg);
	void StatePinCallBack(const commande_locale::Msg_PinControl::ConstPtr&  msg);
	void SchedulerNextShuttleCallback(const scheduling::Msg_LoadShuttle::ConstPtr& msg);
};
#endif
