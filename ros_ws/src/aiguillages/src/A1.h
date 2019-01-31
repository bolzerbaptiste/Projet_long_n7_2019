#ifndef AIG_1
#define AIG_1

#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <unistd.h>
#include <vrep_common/simRosEnablePublisher.h>
#include <vrep_common/simRosEnableSubscriber.h>
#include <vrep_common/simRosGetInfo.h>
#include <map>
#include "Sh.h" 
#include "aiguillages/ExchangeSh.h"


#include <shuttles/srvGetShuttleStatus.h>



using namespace std;


//aiguillage 1->2
class A1
{
private:

	//Subscriber
	ros::Subscriber VREPsubStopSensor;
	ros::Subscriber VREPsubRailSensor;
	ros::Subscriber VREPsubSwitchSensor;

	//time
	ros::ServiceClient client_get_vrep_time;
	vrep_common::simRosGetInfo srv_get_time;


	//Publisher
	ros::Publisher ShStop;
	ros::Publisher ShStart;
	ros::Publisher AigDev;
	ros::Publisher AigVer;
	ros::Publisher AigGauche;
	ros::Publisher AigDroit;


	std::multimap<int,Sh*> ShuttlesMap;
	std_msgs::Int32 num_AIG;
	std_msgs::Int32 num_STOP;

	//transmission des handles des navettes
	ros::Publisher SendShuttle_d;
	ros::Publisher SendShuttle_g;
	ros::Subscriber ReceiveShuttle;
	aiguillages::ExchangeSh HandleShuttle;


	//Services shuttle
	ros::ServiceClient client_SetShuttleState;
	shuttles::srvGetShuttleStatus srv_SetShuttleState;	

	

	float Dt;

	bool PS;///Capteur stop 20 en entrée de l'aiguillage

	bool CPD;//Capteur CP droit apres l'aiguillage
	bool CPD_past;

	bool CPG;
	bool CPG_past;

	bool Nav_CPD;///Une navette est passé en CP9
	bool Nav_CPG;

	bool Aig_D;//Capteurs aiguillage
	bool Aig_G;



	int num_aiguillage;
	int num_capt_stop;
	int num_capt_droit;
	int num_capt_gauche;



public:
	A1(ros::NodeHandle nh);
	void StopSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void RailSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void SwitchSensorCallback(const std_msgs::Int32::ConstPtr& msg);

	void NewShuttleCallBack(const aiguillages::ExchangeSh::ConstPtr& msg);


	void STOP();
	void START();
	void Gauche();
	void Droit();
	void Aiguille_Navette();

	int get_Sh_Handle();
	void Send_Sh(int destination);

	float get_time();
	void wait_vrep(float dt);

};

#endif
