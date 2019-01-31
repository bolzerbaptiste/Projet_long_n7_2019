#ifndef AIG_A3
#define AIG_A3

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


//aiguillage 1->2 et 2->1
class A3
{
private:

	//Subscribe Sensor
	ros::Subscriber VREPsubStopSensor;
	ros::Subscriber VREPsubRailSensor;
	ros::Subscriber VREPsubSwitchSensor;
	ros::Subscriber Aigok;



	ros::Publisher ShStop;
	ros::Publisher ShStart;
	ros::Publisher AigDev;
	ros::Publisher AigVer;
	ros::Publisher AigGauche;
	ros::Publisher AigDroit;
	ros::Publisher DemiTour;

	//time
	ros::ServiceClient client_get_vrep_time;
	vrep_common::simRosGetInfo srv_get_time;

	std::multimap<int,Sh*> ShuttlesMap;

//transmission des handles des navettes
	
	ros::Publisher SendShuttle_g;
	ros::Publisher DeleteShuttle;
	ros::Publisher DeleteShuttleScheduler;
	ros::Subscriber ReceiveShuttle;
	ros::Subscriber subDestroyShuttle;
	aiguillages::ExchangeSh HandleShuttle;
	std_msgs::Int32 DeleteSh;

	//Services shuttle
	ros::ServiceClient client_SetShuttleState;
	shuttles::srvGetShuttleStatus srv_SetShuttleState;	

	

	int A10_ok; //Aiguillage 10 en position

	bool PS;///Capteur stop 6 en entrée de l'aiguillage bas
	

	
	
	float Dt;

	bool CPb;//Capteur CP droit apres l'aiguillage bas
	bool CPb_past;

	bool Nav_CPb;//ne navette est passée en CP3
	bool Nav_PSh; //Une navette est passée en PS20

	bool Aig_D;//Capteurs aiguillage
	bool Aig_G;

	
	int num_aiguillage;
	int num_capt_stop;
	int num_capt_sortie_haut;
	int num_capt_sortie_bas;


	std_msgs::Int32 num_STOP;

	std_msgs::Int32 num_AIG;



public:
	A3(ros::NodeHandle nh);
	
	void StopSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void RailSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void SwitchSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void AiguillageCallback(const std_msgs::Int32::ConstPtr& msg);

	void NewShuttleCallBack(const aiguillages::ExchangeSh::ConstPtr& msg);
	void DestroyShuttleCallBack(const std_msgs::Int32::ConstPtr& msg);
	
	void Droit();
	void Gauche();
	void Aiguille_Navette();
	void ModeManuel();
	void STOP();
	void START();
	int get_Sh_Handle();
	void Send_Sh(int destination);
	void Send_Sh_Bis(int destination, int handle);
	float get_time();
	void wait_vrep(float dt);

};

#endif
