#ifndef AIG_12
#define AIG_12

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <unistd.h>
#include <vrep_common/simRosEnablePublisher.h>
#include <vrep_common/simRosEnableSubscriber.h>
#include <vrep_common/simRosGetInfo.h>
#include <map>
#include "Sh.h" 
#include "aiguillages/ExchangeSh.h"

using namespace std;

class A12
{
private:

	//Subscribe Sensor
	ros::Subscriber VREPsubSensor;
	ros::Subscriber VREPsubSwitchSensor;

	//Publisher
	ros::Publisher ShStop;
	ros::Publisher ShStart;
	ros::Publisher AigDev;
	ros::Publisher AigVer;
	ros::Publisher AigGauche;
	ros::Publisher AigDroit; 


	std::multimap<int,Sh*> ShuttlesMap;
	std_msgs::Int32 num_STOPg;
	std_msgs::Int32 num_STOPd;

	std_msgs::Int32 num_AIG;

	//time
	ros::ServiceClient client_get_vrep_time;
	vrep_common::simRosGetInfo srv_get_time;

	//transmission des handles des navettes
	ros::Publisher SendShuttle;
	ros::Subscriber ReceiveShuttle_g;
	ros::Subscriber ReceiveShuttle_d;
	aiguillages::ExchangeSh HandleShuttle;



	bool PSG; // capteur PSG en entrée aiguillage gauche
	

	bool PSD; // capteur PSD en entrée aiguillage droit


	bool PS;
	bool PS_past;

	bool Nav_PS;

	bool Aig_D;
	bool Aig_G;

	bool Att_D;
	bool Att_G;



	int num_aiguillage ;
	int num_stop_droit;
	int num_stop_gauche;
	int num_capt_sortie;


	float Dt;



	

 
public:
	A12(ros::NodeHandle nh);


	void NewShuttleCallBack_d(const aiguillages::ExchangeSh::ConstPtr& msg);
	void NewShuttleCallBack_g(const aiguillages::ExchangeSh::ConstPtr& msg);

	void SensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void SwitchSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void STOP_DROIT();
	void STOP_GAUCHE();
	void START_DROIT();
	void START_GAUCHE();
	void Gauche();
	void Droit();
	void Aiguille_Navette();

	int get_Sh_Handle(int origine);
	void Send_Sh(int origine);

	float get_time();
	void wait_vrep(float dt);

};

#endif
