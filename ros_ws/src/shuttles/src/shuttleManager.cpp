/**** Maxime Maurin - Projet Long N7 2017 ****/

#include <ros/ros.h>
#include "shuttleManager.h"

//Construteur
ShuttleManager::ShuttleManager()
{

}

// Initialisation de l'objet 
void ShuttleManager::init(ros::NodeHandle nh)
{
	//Initialisation des Services
	serviceGetShuttleStatus = nh.advertiseService("/commande_navette/srvGetShuttleStatus", &ShuttleManager::getShuttleStatus,this);
	serviceGetEmptyShuttles = nh.advertiseService("/commande_navette/srvGetEmptyShuttles", &ShuttleManager::getEmptyShuttles,this);

	//Initialisation des Subscribers
	subProductChange = nh.subscribe("/commande_navette/ShuttlePChange", 10, &ShuttleManager::productChangeCallBack, this);
	subDestinationChange = nh.subscribe("/commande_navette/ShuttleDChange", 10, &ShuttleManager::destinationChangeCallBack, this);
	subZoneChange = nh.subscribe("/commande_navette/ShuttleZChange", 10, &ShuttleManager::zoneChangeCallBack, this);
	subAddShuttle = nh.subscribe("/commande_navette/AddShuttle", 10, &ShuttleManager::addShuttleCallBack, this);
	subDelShuttle = nh.subscribe("/commande_navette/DelShuttle", 10, &ShuttleManager::delShuttleCallBack, this);
}


// Destructeur

ShuttleManager::~ShuttleManager(){}

// Services
	
	// Service d'obtention des informations sur un shuttle

bool ShuttleManager::getShuttleStatus(shuttles::srvGetShuttleStatus::Request &req, shuttles::srvGetShuttleStatus::Response &res)
{
	std::map<int,Shuttle*>::iterator it;
	Shuttle* shuttlePointer;	
	
	it = ShuttlesMap.find(req.handle);	// find() améne l'itérateur à l'emplacement permetant la bonne clé (handle) 

	if (it != ShuttlesMap.end()) 		// Vrai si l'itérateur n'est pas hors de la liste, donc qu'on a bien trouvé un shuttle avec l'handler du message
	{
		
		ROS_INFO("serviceGetShuttleStatus est en cours d'execution pour la navette d'handle %d",req.handle);

		// On recupère le pointer Shuttle* dans l'élément second de l'itérateur
		shuttlePointer = it->second;
		
		//  On remplit la réponse du service 
		res.name = shuttlePointer->name;
		res.product = shuttlePointer->product;
		res.destination = shuttlePointer->destination;
		res.handlePlatform = shuttlePointer->handlePlatform;
		res.zone = shuttlePointer->zone;
	
		return true;

	}

	else return false;
}

	// Service d'obtention des navettes vides ( produit = 0 !)	
	
bool ShuttleManager::getEmptyShuttles(shuttles::srvGetEmptyShuttles::Request &req, shuttles::srvGetEmptyShuttles::Response &res)
{
	std::map<int,Shuttle*>::iterator it;
	Shuttle* shuttlePointer;
	
	std::vector<int> zoneTable, handleTable;	// Structure Vector nécessaire pour envoyer des tableaux via les topics ROS

	bool atLeastOneFree = false ;
	ROS_INFO("serviceGetEmptyShuttles est en cours d'execution");


 	for (it=ShuttlesMap.begin(); it!=ShuttlesMap.end(); ++it)	// On parcours l'ensemble de la collection
	{
		shuttlePointer = it->second;
		if ( shuttlePointer->product == 0)			// Permet d'identifier les navettes vides
		{
			ROS_INFO("serviceGetEmptyShuttles a trouve une navette vide! (handle = %d) ", shuttlePointer->handle);
			handleTable.push_back(shuttlePointer->handle);	// Remplissage des vecteurs à retourner 
			zoneTable.push_back(shuttlePointer->zone);	// handles + zones
			atLeastOneFree = true;				// On marque le fait qu'au moins une navette est libre
		}
	}
	
	if (atLeastOneFree)
	{
		res.zones = zoneTable;			// Ecriture de la réponse du service 
		res.handles = handleTable;
		return true;
	}
	else
	{
		ROS_WARN("Aucune navette n'est vide !!!");
		return false;
	}
}




// Subscriber Fonctions Callbacks 

	// CallBack pour l'ajout d'une navette active
void ShuttleManager::addShuttleCallBack(const shuttles::msgShuttleCreate::ConstPtr& msg)
{
	std::string n = msg->name;
	ROS_INFO("Creation navette %s avec un produit numero %d", n.c_str(), msg->product);

		// Création dynamique de l'object shuttle
	Shuttle* newShuttle = new Shuttle(msg->name,msg->destination,msg->product,msg->handle,msg->handlePlatform,msg->zone);

		// Insertion dans le map de la classe de la paire <key=handle,T=Shuttle*>

	std::pair<std::map<int,Shuttle*>::iterator,bool> ret;			// ret permet d'avoir un retour de la fonction insert, il est faux si la key existe dèjà dans la map
	ret = ShuttlesMap.insert(std::pair<int,Shuttle*>(newShuttle->handle,newShuttle));
	//ROS_INFO("shuttle pointer : %p ", newShuttle);

	if (ret.second==false)	// Si un shuttle avec le même handle existe dèjà, celui-ci n'est pas ajouté à la collection
	{
    		ROS_WARN("shuttleManager : A shuttle with this handle (%d) already exists in internal memory !", msg->handle); 
  	} 
}

	// CallBack pour la suppression d'une navette active
void ShuttleManager::delShuttleCallBack(const std_msgs::Int32::ConstPtr& msg)
{		

		
	std::map<int,Shuttle*>::iterator it;
	Shuttle* shuttlePointer;	
	
	it = ShuttlesMap.find(msg->data);	// Principe équivalent à celui expliqué à la fonction getShuttleStatus
	if (it != ShuttlesMap.end())		
	{
		shuttlePointer = it->second;	

		// Suppression de l'objet Shuttle en mémoire
		ROS_INFO("Navette %s en cours de suppression, shuttlepointer : %p", shuttlePointer->name.c_str(),shuttlePointer);
		delete shuttlePointer;

		// Suppression de la paire <int,Shuttle*> dans le map
		ShuttlesMap.erase(msg->data);
		ROS_INFO("Suppression Confirme");
	}
	else
	{
		ROS_WARN("ShuttleManager : Navette d'handle %d non trouve pour suppression ! ", msg->data);
	}
}

	// CallBack pour l'évolution du produit transporter par une navette
void ShuttleManager::productChangeCallBack(const shuttles::msgShuttleChange::ConstPtr& msg)
{

	std::map<int,Shuttle*>::iterator it;
	Shuttle* shuttlePointer;	
	
	it = ShuttlesMap.find(msg->handle); // Principe équivalent à celui expliqué à la fonction getShuttleStatus
	if (it != ShuttlesMap.end()) 
	{
		shuttlePointer = it->second;		
		shuttlePointer->product = msg->argument  ;	//MAJ de l'object
		ROS_INFO("Changement produit navette %s, nouveau produit : %d ", shuttlePointer->name.c_str() , shuttlePointer->product);
	}
	else
	{
		ROS_WARN("ShuttleManager : Navette d'handle %d non trouve pour changement de produit ! ", msg->handle);
	}
}

	// Evolution de la destination de la navette
void ShuttleManager::destinationChangeCallBack(const shuttles::msgShuttleChange::ConstPtr& msg)
{
	
	std::map<int,Shuttle*>::iterator it;
	Shuttle* shuttlePointer;	
	
	it = ShuttlesMap.find(msg->handle); // Principe équivalent à celui expliqué à la fonction getShuttleStatus
	if (it != ShuttlesMap.end()) 
	{
		shuttlePointer = it->second;
		shuttlePointer->destination = msg->argument ;	//MAJ de l'object
		ROS_INFO("Changement destination navette %s, nouvelle destination : %d ", shuttlePointer->name.c_str() , shuttlePointer->destination);
	}
	else
	{
		ROS_WARN("ShuttleManager : Navette d'handle %d non trouve pour changement de destination ! ", msg->handle);
	}
	
}

	// Evolution de la zone de la navette
void ShuttleManager::zoneChangeCallBack(const shuttles::msgShuttleChange::ConstPtr& msg)
{
	
	std::map<int,Shuttle*>::iterator it;
	Shuttle* shuttlePointer;	
	
	it = ShuttlesMap.find(msg->handle); // Principe équivalent à celui expliqué à la fonction getShuttleStatus
	if (it != ShuttlesMap.end()) 
	{
		shuttlePointer = it->second;
		shuttlePointer->zone = msg->argument ;		//MAJ de l'object
		ROS_INFO("Changement zone navette %s, nouvelle zone : %d ", shuttlePointer->name.c_str() , shuttlePointer->zone);
	}
	else
	{
		ROS_WARN("ShuttleManager : Navette d'handle %d non trouve pour changement de zone ! ", msg->handle);
	}
	
}








