/**** Maxime Maurin - Projet Long N7 2017 ****/

#ifndef SHUTTLEMANAGER
#define SHUTTLEMANAGER

#include <ros/ros.h>

#include "shuttles/srvGetShuttleStatus.h"
#include "shuttles/srvGetEmptyShuttles.h"
#include "shuttles/msgShuttleChange.h"
#include "shuttles/msgShuttleCreate.h"
#include "shuttle.h"

#include <string>
#include <std_msgs/Int32.h>
#include <cstdlib>
#include <map>
#include <vector>


class ShuttleManager
{
private:

	std::map<int,Shuttle*> ShuttlesMap;
	/*
	Collection "MAP" <key,Object*>, key = handle, Object* = pointer to shuttle object
	Cette Collection permet le stockage des navettes et de les identifier à l'aide de leur handle qui est un entier unique pour chacune d'entre elle.
	Vous remarquerez que ceux qui est vraiment stocker dans la collection est le pointer vers l'objet pour des question de simplicité.
 	*/

	ros::ServiceServer serviceGetShuttleStatus;
	/*
	Le service "shuttles/srvGetShuttleStatus.h" disponible dans le package shuttles permet de récupérer l'ensemble des informations disponibles sur un shuttle.
    	Pour l'utiliser il suffit de lui transmettre l'handle de la navette.
    	Il retourne true si la navette a bien été renseigner, false si le handle n'existe pas.
	*/

	ros::ServiceServer serviceGetEmptyShuttles;
	/*
    	Ce service permet de récuperer la liste des navettes vides. Il retourne 2 vector handles et zones. Il ne nécessite pas d'argument en entrée. Il retourne false si aucune navette n'est vide.
    	*/


	ros::Subscriber subProductChange, subDestinationChange, subZoneChange, subAddShuttle, subDelShuttle;
	/*
   	Les subscribers permettent la gestion de la collection map fonction des msg recu par les autres noeuds
   	subAddShuttle : un msg de type "shuttles/msgShuttleCreate.h" publié sur le topic "/commande_navette/AddShuttle" permet l'ajout d'une nouvelle navette
   	subDelShuttle : un msg de type "std_msgs/Int32.h"  publié sur le topic "/commande_navette/DelShuttle" permet la suppression d'une navette
   	subProductChange : un msg de type ""shuttles/msgShuttleChange.h""  publié sur le topic "/commande_navette/ShuttlePChange" permet la maj du produit transporter par la navette
    	subDestinationChange : un msg de type ""shuttles/msgShuttleChange.h""  publié sur le topic "/commande_navette/ShuttleDChange" permet la maj de la destination de la navette 
   	subZoneChange : un msg de type ""shuttles/msgShuttleChange.h""  publié sur le topic "/commande_navette/ShuttleZChange" permet la maj de la zone où se trouve la navette
   	*/



public:
	
	ShuttleManager();
	~ShuttleManager();
	
	//Function to initialize subscribers and services
	void init(ros::NodeHandle nh);

	//Callback Function for Services
	bool getShuttleStatus(shuttles::srvGetShuttleStatus::Request &req, shuttles::srvGetShuttleStatus::Response &res);
	bool getEmptyShuttles(shuttles::srvGetEmptyShuttles::Request &req, shuttles::srvGetEmptyShuttles::Response &res);
	
	//Callback Function for Subscribers
	void productChangeCallBack(const shuttles::msgShuttleChange::ConstPtr& msg);
	void destinationChangeCallBack(const shuttles::msgShuttleChange::ConstPtr& msg);
	void zoneChangeCallBack(const shuttles::msgShuttleChange::ConstPtr& msg);
	void addShuttleCallBack(const shuttles::msgShuttleCreate::ConstPtr& msg);
	void delShuttleCallBack(const std_msgs::Int32::ConstPtr& msg);


};


#endif
