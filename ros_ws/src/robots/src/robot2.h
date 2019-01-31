/**** Projet long N7 2017 ****/

#ifndef ROBOT2
#define ROBOT2

#include <ros/ros.h>

//Services Vrep
#include <vrep_common/simRosEnablePublisher.h>
#include <vrep_common/simRosEnableSubscriber.h>

#include <vrep_common/simRosSetJointState.h>
#include <vrep_common/simRosGetObjectHandle.h>
#include <vrep_common/simRosGetJointState.h>
#include <vrep_common/simRosGetInfo.h>

//Messages
#include <robots/RobotJoints.h>
#include <robots/MoveRobot.h>
#include <std_msgs/Int32.h>

#include <vector>
#include <sstream>
#include <stdlib.h>


class Robot2
{
private:

	/** Services V-Rep **/
	//Service simRosGetObjectHandle
	ros::ServiceClient client_simRosGetHandle;
	vrep_common::simRosGetObjectHandle srv_simRosGetHandle;

	//Service simRosSetJointState
	ros::ServiceClient client_simRosSetJoint;
	vrep_common::simRosSetJointState srv_simRosSetJoint;

	//Service simRosGetJointState
	ros::ServiceClient client_simRosGetJoint;
	vrep_common::simRosGetJointState srv_simRosGetJoint;

	//Service simRosGetInfo
	ros::ServiceClient client_simGetVrepTime;
	vrep_common::simRosGetInfo srv_simGetVrepTime;	

	/** Subscribers aux topics de la commande **/
	ros::Subscriber planifSendPosition;
	ros::Subscriber planifSendJoints;
	ros::Subscriber planifFermerPince;
	ros::Subscriber planifOuvrirPince;
	ros::Subscriber planifDescendreBras;
	ros::Subscriber planifMonterBras;
	ros::Subscriber planifControlerRobot;
	
	/** Publishers **/
	ros::Publisher pub_pince;
	ros::Publisher pub_robotPosition, pub_robotBras, pub_robotPince;
	ros::Publisher pub_retourCommande;

	/** Variables **/
	float pi;
	unsigned char mymodes[7];
	float Rpos[7];
	int Rints[7];

	/** Messages **/
	std_msgs::Int32 robotPosition;
	std_msgs::Int32 robotBras;
	std_msgs::Int32 robotPince;
	std_msgs::Int32 retour;


public:

	Robot2();
	~Robot2();
	
	//Initialisation
	void init(ros::NodeHandle noeud);

	/** Fonctions internes permettant le contrôle du robot **/
	//Pour atteindre une position prédéfinie
	void EnvoyerRobot(int position);

	//Pour atteindre une position définie manuellement
	void EnvoyerJoints(int joint1, int joint2, int joint3, int joint4, int joint5, int joint6, int joint7);

	//Pour monter ou descendre le bras
	void DescendreBras();
	void MonterBras();

	//Pour ouvrir ou fermer la pince
	void FermerPince();
	void OuvrirPince();


	/** Fonctions permettant de controler le robot avec des ordres du noeud commande **/
	//Pour atteindre une position prédéfinie
	void SendPositionCallback(const std_msgs::Int32::ConstPtr& msg);

	//Pour atteindre une position définie manuellement 
	void SendJointsCallback(const robots::RobotJoints::ConstPtr& msg);

	//Pour monter ou descendre le bras
	void DescendreBrasCallback(const std_msgs::Int32::ConstPtr& msg);
	void MonterBrasCallback(const std_msgs::Int32::ConstPtr& msg);	

	//Pour ouvrir ou fermer la pince
	void FermerPinceCallback(const std_msgs::Int32::ConstPtr& msg);
	void OuvrirPinceCallback(const std_msgs::Int32::ConstPtr& msg);

	//Pour contrôler l'ensemble des mouvements du robot
	void ControlerRobotCallback(const robots::MoveRobot::ConstPtr& msg);

};


#endif

