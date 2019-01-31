#ifndef AIG_10
#define AIG_10

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


//aiguillage 1->2 et 2->1
class A10
{
private:

	//Subscribe Sensor
	ros::Subscriber VREPsubStopSensor;
	ros::Subscriber VREPsubSwitchSensor;
	ros::Subscriber DemiTour;


	ros::Publisher ShStop;
	ros::Publisher ShStart;
	ros::Publisher AigDev;
	ros::Publisher AigVer;
	ros::Publisher AigGauche;
	ros::Publisher AigDroit;
	ros::Publisher Aigok;

	//time
	ros::ServiceClient client_get_vrep_time;
	vrep_common::simRosGetInfo srv_get_time;

	std::multimap<int,Sh*> ShuttlesMap;

//transmission des handles des navettes
	ros::Publisher SendShuttle;
	ros::Subscriber ReceiveShuttle_g;
	ros::Subscriber ReceiveShuttle_d;
	aiguillages::ExchangeSh HandleShuttle;
	
	float Dt;



	bool PS;//capteur 20
	bool PS_past;
	
	bool PSD;///Capteur stop 19 en entrée de l'aiguillage haut
	

	bool Nav_PS; //Une navette est passée en PS20

	bool Aig_D;//Capteurs aiguillage
	bool Aig_G;

	

	int num_aiguillage;
	int num_capt_stop;
	int num_capt_sortie;

	bool Nav_A3;

	std_msgs::Int32 num_STOP;

	std_msgs::Int32 num_AIG;

	std_msgs::Int32 topic;



public:
	A10(ros::NodeHandle nh);
	void StopSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void SwitchSensorCallback(const std_msgs::Int32::ConstPtr& msg);
	void DemiTourCallback(const std_msgs::Int32::ConstPtr& msg);

	void NewShuttleCallBack_d(const aiguillages::ExchangeSh::ConstPtr& msg);
	void NewShuttleCallBack_g(const aiguillages::ExchangeSh::ConstPtr& msg);

	void Droit();
	void Gauche();
	void Aiguille_Navette();
	void ModeManuel();
	void STOP();	
	void START();
	int get_Sh_Handle(int origine);
	void Send_Sh(int origine);
	float get_time();
	void wait_vrep(float dt);

};

#endif
