/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include "commande.h"
#include <ros/ros.h>
#include <iostream>
#include <std_msgs/Int32.h>

using namespace std;

//the following are UBUNTU/LINUX ONLY terminal color codes.
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



Commande::Commande(ros::NodeHandle noeud, std::string executionPath)
{

	// Commande Stop/Start Navettes
	SubArretNavette = noeud.subscribe("/commande/ArretNavette", 1000, &Commande::ArretNavette, this);
	SubDemarreNavette = noeud.subscribe("/commande/DemarrerNavette", 1000, &Commande::DemarreNavette, this);

	//Commande aiguillages
	SubDeverouilleAiguillages = noeud.subscribe("/commande/DeverouilleAiguillage", 1000, &Commande::DeverouilleAiguillages, this);
	SubVerouilleAiguillages = noeud.subscribe("/commande/VerouilleAiguillage", 1000, &Commande::VerouilleAiguillages, this);
	SubAiguillagesGauches = noeud.subscribe("/commande/AiguillageGauche", 1000, &Commande::Aiguillagesgauches, this);
	SubAiguillagesDroits = noeud.subscribe("/commande/AiguillageDroit", 1000, &Commande::Aiguillagesdroits, this);

	// Publishers messages actionneurs
	cout<<"Initialisation publisher"<<endl;
	pub_navettes_stops = noeud.advertise<commande_locale::Msg_StopControl>("/commande/Simulation/Actionneurs_stops", 1);
	pub_actionneurs_simu_aiguillages = noeud.advertise<commande_locale::Msg_SwitchControl>("/commande/Simulation/Actionneurs_aiguillages", 1);
        pub_actionneurs_simu_pins = noeud.advertise<commande_locale::Msg_PinControl>("/commande/Simulation/Actionneurs_pins", 10);
	
	// Publishers pour redémarrer une navette au niveau des postes
	PubDemarrerNavetteP1 = noeud.advertise<std_msgs::Int32>("/Cmde_P1/Demarrage", 10);
	PubDemarrerNavetteP2 = noeud.advertise<std_msgs::Int32>("/Cmde_P2/Demarrage", 10);
	PubDemarrerNavetteP3 = noeud.advertise<std_msgs::Int32>("/Cmde_P3/Demarrage", 10);
	PubDemarrerNavetteP4 = noeud.advertise<std_msgs::Int32>("/Cmde_P4/Demarrage", 10);

	// Publishers vers Postes - produit récupéré par robot
	pubProductTakenByRobotP1 = noeud.advertise<std_msgs::Int32>("/Cmde_P1/ProduitRecupere", 10);
	pubProductTakenByRobotP2 = noeud.advertise<std_msgs::Int32>("/Cmde_P2/ProduitRecupere", 10);
	pubProductTakenByRobotP3 = noeud.advertise<std_msgs::Int32>("/Cmde_P3/ProduitRecupere", 10);
	pubProductTakenByRobotP4 = noeud.advertise<std_msgs::Int32>("/Cmde_P4/ProduitRecupere", 10);

	// Publishers vers Postes - produit posé sur navette
	pubProductPutOnShuttleP1 = noeud.advertise<std_msgs::Int32>("/Cmde_P1/ProduitPose", 10);
	pubProductPutOnShuttleP2 = noeud.advertise<std_msgs::Int32>("/Cmde_P2/ProduitPose", 10);
	pubProductPutOnShuttleP3 = noeud.advertise<std_msgs::Int32>("/Cmde_P3/ProduitPose", 10);
	pubProductPutOnShuttleP4 = noeud.advertise<std_msgs::Int32>("/Cmde_P4/ProduitPose", 10);

	// Publisher pour changer les destinations
	pubDestinationChange = noeud.advertise<shuttles::msgShuttleChange>("/commande_navette/ShuttleDChange", 10);

	// Publisher pour détruire les navettes
	pubDestroyShuttle = noeud.advertise<std_msgs::Int32>("/commande_navette/Destroy_Shuttle",10);

	// Subscribers quand navettes vides présentes aux postes
	subEmptyShuttleReadyP1 = noeud.subscribe("/Cmde_P1/NavetteVidePrete", 10, &Commande::GestionNavetteVideP1Callback, this);
	subEmptyShuttleReadyP2 = noeud.subscribe("/Cmde_P2/NavetteVidePrete", 10, &Commande::GestionNavetteVideP2Callback, this);
	subEmptyShuttleReadyP3 = noeud.subscribe("/Cmde_P3/NavetteVidePrete", 10, &Commande::GestionNavetteVideP3Callback, this);
	subEmptyShuttleReadyP4 = noeud.subscribe("/Cmde_P4/NavetteVidePrete", 10, &Commande::GestionNavetteVideP4Callback, this);

	// Subscribers quand produit à récuperer aux postes
	subProductInPostP1 = noeud.subscribe("/Cmde_P1/ProduitPresentP1", 10, &Commande::ProductInPostP1Callback, this);
	subProductInPostP2 = noeud.subscribe("/Cmde_P2/ProduitPresentP2", 10, &Commande::ProductInPostP2Callback, this);
	subProductInPostP3 = noeud.subscribe("/Cmde_P3/ProduitPresentP3", 10, &Commande::ProductInPostP3Callback, this);
	subProductInPostP4 = noeud.subscribe("/Cmde_P4/ProduitPresentP4", 10, &Commande::ProductInPostP4Callback, this);

	// Actionner ergots
	subPinOn = noeud.subscribe("/Poste_Cmde/SortirErgots", 10, &Commande::SortirErgotCallback, this);
	subPinOff = noeud.subscribe("/Poste_Cmde/RentrerErgots", 10, &Commande::RentrerErgotCallback, this);

	
	client_GetShuttleState = noeud.serviceClient<shuttles::srvGetShuttleStatus>("/commande_navette/srvGetShuttleStatus");
	client_GetEmptyShuttle = noeud.serviceClient<shuttles::srvGetEmptyShuttles>("/commande_navette/srvGetEmptyShuttles");
	NewShuttle = noeud.subscribe("/commande_locale/New_Shuttle_Handle", 10, &Commande::NewShuttleCallBack, this);

	// Initialisation des Actionneurs

	for(int i=1;i<=24;i++) actionneurs_simulation_Stop.STOP[i] = 1;
	for(int i=1;i<=24;i++) actionneurs_simulation_Stop.GO[i] = 0;

	for(int i=1;i<=12;i++) actionneurs_simulation_Aiguillages.LOCK[i] = 0;
	for(int i=1;i<=12;i++) actionneurs_simulation_Aiguillages.RD[i] = 0;
	for(int i=1;i<=12;i++) actionneurs_simulation_Aiguillages.RG[i] = 0;

        for(int i=1;i<=8;i++) actionneurs_simulation_Pin.PINON[i] = 0;
        for(int i=1;i<=8;i++) actionneurs_simulation_Pin.PINOFF[i] = 1;


	//Initialisation des variables
	
	ProduitEnP1=0;
	ProduitEnP1=0;
	ProduitEnP1=0;
	ProduitEnP1=0;
	NavetteVideEnP1=0;
	NavetteVideEnP2=0;
	NavetteVideEnP3=0;
	NavetteVideEnP4=0;
	NavetteEnP1=0;
	NavetteEnP2=0;
	NavetteEnP3=0;
	NavetteEnP4=0;

	NewHandle=0;

	
	



////////////////////////////////////////////////////////////////////
//Initialisation des produits à l'aide d'un fichier de configuration
////////////////////////////////////////////////////////////////////


// Récupération du chemin vers le Working_Folder
int count = 0 ;
int pos = 0 ;
while (count < 4)
	{
	if(executionPath[pos] == '/') count++;
	pos++;
	}
std::string Working_Folder = executionPath.substr(0,pos);

	
//Initialisation des produits à l'aide du fichier de configuration


	//Définition du chemin du fichier de config
std::string configFile = Working_Folder + "/ProductConfiguration.config";

std::ifstream streamConfigFile(configFile.c_str(), std::ios::in);
	
	if (streamConfigFile)
	{
	std::string pNameFF,destinationPart,contents;

	//saut des lignes d'entêtes, repèrage du start.
	while(1){
	std::getline(streamConfigFile,contents);
	std::size_t found = contents.find("Start");
  	if (found!=std::string::npos)
		{
		break;
		}
	}
	//Configuration nombre max de shuttle
	std::getline(streamConfigFile,contents);

	//Configuration temps entre lancement
	std::getline(streamConfigFile,contents);
	
	//GAMME/TEMPS
	while (std::getline(streamConfigFile, contents))
		{
		if (contents.find(':') != std::string::npos )
			{
			//ROS_INFO("%s",contents.c_str())	;
			std::size_t pos2 = contents.find(":");
			std::size_t pos3 = contents.find_last_of(":");
		
			pNameFF = contents.substr(0,pos2);
			destinationPart = contents.substr(pos2+1,pos3-pos2-1);
	
			int destination[10];
		
			int manRSize = 0; //manufacturing range size of the produit = number of operation

			char * cstr2 = new char [destinationPart.length()+1]; 
	  		std::strcpy (cstr2, destinationPart.c_str());	// création objet cstring

	  		// cstr now contains a c-string copy of str
			int n2 = 0; //compteur sur les destinations

			char * p2 = std::strtok (cstr2," ");
	  		while (p2!=NULL)
	  			{
				destination[n2++] = atoi(p2);
				manRSize++ ;
	  			p2 = std::strtok(NULL," ");
	  			}

	  		delete[] cstr2;


			char charName;
			charName = char(pNameFF.c_str()[0]-16);
			int pNumberBase = atoi(&charName) * 10 ; 
			int pNumber;
			int nextDestination;


	//  Pour gérer le n° de la prochaine destination d'un produit
			for (int i = 0; i < manRSize+1; i++)	
				{	
				pNumber = pNumberBase + i; 		
				if ( i+1 == manRSize+1 )  // Si i+1 est égal au nombre d'étapes de fabrication du produit 
					{
					nextDestination = 5; 	// Destination qui correspond à la sortie 
					}
				else 	nextDestination = destination[i];
				//ROS_INFO("pNumber : %d, nextdestination : %d",pNumber, nextDestination);
				initProduct(nextDestination,pNumber);
				}
			}
		}
	streamConfigFile.close(); //fermeture du fichier ProductConfiguration.txt ouvert en lecture//

	}

}


void Commande::Initialisation()
{
	for(int i=0;i<25;i++) PSx[i]=0;
	for(int i=0;i<13;i++) DxD[i]=0;
	for(int i=0;i<13;i++) DxG[i]=0;
	for(int i=0;i<11;i++) CPx[i]=0;
	for(int i=0;i<9;i++) CPIx[i]=0;

	for(int i=0;i<25;i++) STx[i]=1;
	for(int i=0;i<13;i++) RxD[i]=0;
	for(int i=0;i<13;i++) RxG[i]=0;

	for(int i=0;i<13;i++) Vx[i]=0;
	for(int i=0;i<13;i++) Dx[i]=0;
	for(int i=0;i<9;i++) PIx[i]=0;
}

//////////////////////////////
// 	Callback Stop/Start
//////////////////////////////
void Commande::ArretNavette(const std_msgs::Int32::ConstPtr& msg)
{
	STx[msg->data]=0;
	for(int i=0;i<25;i++) actionneurs_simulation_Stop.STOP[i]=!STx[i];
	for(int i=0;i<25;i++) actionneurs_simulation_Stop.GO[i]=STx[i];
	pub_navettes_stops.publish(actionneurs_simulation_Stop);
	
}

void Commande::DemarreNavette(const std_msgs::Int32::ConstPtr& msg)
{
	STx[msg->data]=1;
	for(int i=0;i<25;i++) actionneurs_simulation_Stop.STOP[i]=!STx[i];
	for(int i=0;i<25;i++) actionneurs_simulation_Stop.GO[i]=STx[i];
	pub_navettes_stops.publish(actionneurs_simulation_Stop);
	
}

//////////////////////////////
// 	Callback Aiguillages
//////////////////////////////
void Commande::DeverouilleAiguillages(const std_msgs::Int32::ConstPtr& msg)
{
	Dx[msg->data]=1;
	Vx[msg->data]=0;
}

void Commande::VerouilleAiguillages(const std_msgs::Int32::ConstPtr& msg)
{
	Dx[msg->data]=0;
	Vx[msg->data]=1;
}

void Commande::Aiguillagesgauches(const std_msgs::Int32::ConstPtr& msg)
{
	RxG[msg->data]=1;

	for(int i=0;i<13;i++) actionneurs_simulation_Aiguillages.RG[i] = RxG[i];
	for(int i=0;i<13;i++) actionneurs_simulation_Aiguillages.RD[i] = RxD[i];
	for(int i=0;i<13;i++) actionneurs_simulation_Aiguillages.LOCK[i] = !Vx[i] && Dx[i];
	pub_actionneurs_simu_aiguillages.publish(actionneurs_simulation_Aiguillages);

	RxG[msg->data]=0;
}

void Commande::Aiguillagesdroits(const std_msgs::Int32::ConstPtr& msg)
{
	RxD[msg->data]=1;

	for(int i=0;i<13;i++) actionneurs_simulation_Aiguillages.RD[i] = RxD[i];
	for(int i=0;i<13;i++) actionneurs_simulation_Aiguillages.RG[i] = RxG[i];
	for(int i=0;i<13;i++) actionneurs_simulation_Aiguillages.LOCK[i] = !Vx[i] && Dx[i];
	pub_actionneurs_simu_aiguillages.publish(actionneurs_simulation_Aiguillages);

	RxD[msg->data]=0;
}

///////////////////////////
// 	Callback Ergots
//////////////////////////
void Commande::SortirErgotCallback(const std_msgs::Int32::ConstPtr& msg)
{
	PIx[msg->data]=1;
        for(int i=1;i<=8;i++) actionneurs_simulation_Pin.PINON[i] = PIx[i];
        for(int i=1;i<=8;i++) actionneurs_simulation_Pin.PINOFF[i] = !PIx[i];

	pub_actionneurs_simu_pins.publish(actionneurs_simulation_Pin);
}

void Commande::RentrerErgotCallback(const std_msgs::Int32::ConstPtr& msg)
{
	PIx[msg->data]=0;
        for(int i=1;i<=8;i++) actionneurs_simulation_Pin.PINON[i] = PIx[i];
        for(int i=1;i<=8;i++) actionneurs_simulation_Pin.PINOFF[i] = !PIx[i];

	pub_actionneurs_simu_pins.publish(actionneurs_simulation_Pin);
}

////////////////////////////////////////////////
// Callback Navettes vides au niveau des postes
////////////////////////////////////////////////
void Commande::GestionNavetteVideP1Callback(const std_msgs::Int32::ConstPtr& msg)
{
	NavetteVideEnP1 = msg->data;
}

void Commande::GestionNavetteVideP2Callback(const std_msgs::Int32::ConstPtr& msg)
{
	NavetteVideEnP2 = msg->data;
}

void Commande::GestionNavetteVideP3Callback(const std_msgs::Int32::ConstPtr& msg)
{
	NavetteVideEnP3 = msg->data;
}

void Commande::GestionNavetteVideP4Callback(const std_msgs::Int32::ConstPtr& msg)
{
	NavetteVideEnP4 = msg->data;
}



//////////////////////////////////////////////////
// Callback produit présent au niveau des postes
//////////////////////////////////////////////////
void Commande::ProductInPostP1Callback(const std_msgs::Int32::ConstPtr& msg)
{
	ProduitEnP1 = 1;
	NavetteEnP1=msg->data;
	ROS_INFO("Navette en P1 : %d", NavetteEnP1);
}

void Commande::ProductInPostP2Callback(const std_msgs::Int32::ConstPtr& msg)
{
	ProduitEnP2 = 1;
	NavetteEnP2=msg->data;
}

void Commande::ProductInPostP3Callback(const std_msgs::Int32::ConstPtr& msg)
{
	ProduitEnP3 = 1;
	NavetteEnP3=msg->data;
}

void Commande::ProductInPostP4Callback(const std_msgs::Int32::ConstPtr& msg)
{
	ProduitEnP4 = 1;
	NavetteEnP4=msg->data;
}



//Fonction permettant de récupérer l'handle lors de la création d'une navette
void Commande::NewShuttleCallBack(const aiguillages::ExchangeSh::ConstPtr& msg)
{
	NewHandle=msg->handle;
}



//Fonction init du fichier configuration pour créer un produit
void Commande::initProduct(int nDestination, int pNumber)
{
		// Création dynamique de l'object product
	ProductPost* newProductPost = new ProductPost(nDestination,pNumber);

		// Insertion dans le map de la classe de la paire <key=pNumber,T=Product*>

	std::pair<std::map<int,ProductPost*>::iterator,bool> ret;			// ret permet d'avoir un retour de la fonction insert, il est faux si la key existe déjà dans la map
	ret = ProductsMap.insert(std::pair<int,ProductPost*>(newProductPost->productNumber,newProductPost));

	if (ret.second==false)	// Si un produit avec le même nom existe dèjà, celui-ci n'est pas ajouté à la collection
	{
    		ROS_WARN("Ordonnanceur : Un Produit de ce nom existe dèjà !"); 
  	} 

}



//////////////////////////////////////////////////
// Fonctions haut niveau
//////////////////////////////////////////////////

//Fonction pour savoir si le produit a été pris par le robot
void Commande::PiecePrise(int numPoste)
{
	std_msgs::Int32 msg;
	msg.data = 1;
	switch(numPoste)
	{
		case 1:
			ProduitEnP1=0;
			pubProductTakenByRobotP1.publish(msg);
		break;

		case 2:
			ProduitEnP2=0;
			pubProductTakenByRobotP2.publish(msg);
		break;

		case 3:
			ProduitEnP3=0;
			pubProductTakenByRobotP3.publish(msg);
		break;

		case 4:
			ProduitEnP4=0;
			pubProductTakenByRobotP4.publish(msg);
		break;	
	}	
}


//Fonction pour savoir si le robot a posé un produit
void Commande::PieceDeposee(int numPoste)
{
	std_msgs::Int32 msg;
	msg.data = 1;
	switch(numPoste)
	{
		case 1:
			pubProductPutOnShuttleP1.publish(msg);
		break;

		case 2:
			pubProductPutOnShuttleP2.publish(msg);
		break;

		case 3:
			pubProductPutOnShuttleP3.publish(msg);
		break;

		case 4:
			pubProductPutOnShuttleP4.publish(msg);
		break;	
	}	
}



//Fonction qui permet de définir la destination d'une navette
void Commande::DefinirDestination(int handle, int destination)
{
	ROS_INFO("Definir destination : handle : %d, destination : %d",handle, destination);
	Newdestination.handle =handle;
	Newdestination.argument = destination;
	pubDestinationChange.publish(Newdestination); // Renseigne la nouvelle destination au service
}


//Fonction qui renvoie la destination du produit présent sur la navette
int Commande::ProduitSurNavette(int handle)
{
	srv_GetShuttleState.request.handle=handle;
	client_GetShuttleState.call(srv_GetShuttleState);
	int produit= srv_GetShuttleState.response.product;
	if(produit==0)
	{
		return 0;//Navette vide
	}else
	{
		std::map<int,ProductPost*>::iterator it;
		ProductPost* pointerProduct;
		it = ProductsMap.find(produit);	// find() amène l'itérateur à l'emplacement permetant la bonne clé

		if (it != ProductsMap.end()) {		// Vrai si l'itérateur n'est pas hors de la liste
			pointerProduct = it->second;
			return pointerProduct->nextDestination;	
		}			
	}
}


//Fonction qui renvoie le handle de la navette présente au poste numPoste
int Commande::NavetteStoppee(int numPoste)
{
	switch(numPoste)
	{
		case 1:
		return NavetteEnP1;
		break;

		case 2:
		return NavetteEnP2;
		break;

		case 3:
		return NavetteEnP3;
		break;

		case 4:
		return NavetteEnP4;
		break;
		
	}
}

//Fonction qui renvoie le handle de la navette présente au poste numPoste
int Commande::NavetteStoppeeVide(int numPoste)
{
	switch(numPoste)
	{
		case 1:
		return NavetteVideEnP1;
		break;

		case 2:
		return NavetteVideEnP2;
		break;

		case 3:
		return NavetteVideEnP3;
		break;

		case 4:
		return NavetteVideEnP4;
		break;
		
	}
}


//Fonction qui réinitialise les variables associées à la présence d'une navette à un poste
void Commande::NavettePartie(int numPoste)
{
	switch(numPoste)
	{
		case 1:
			NavetteEnP1=0;
			NavetteVideEnP1=0;
			ProduitEnP1=0;
		break;

		case 2:
			NavetteEnP2=0;
			ProduitEnP2=0;
			NavetteVideEnP2=0;
		break;

		case 3:
			NavetteEnP3=0;
			NavetteVideEnP3=0;
			ProduitEnP3=0;
		break;

		case 4:
			NavetteEnP4=0;
			NavetteVideEnP4=0;
			ProduitEnP4=0;
		break;
		
	}
}


//Fonction pour savoir si une navette est disponible = présente dans D0
int Commande::NavetteDisponible()
{
	client_GetEmptyShuttle.call(srv_GetEmptyShuttle);
	int i=0;
	int handle;
	int destination;
	
	do
	{
		handle=srv_GetEmptyShuttle.response.handles[i];
		srv_GetShuttleState.request.handle=handle;
		
		client_GetShuttleState.call(srv_GetShuttleState);
		destination=srv_GetShuttleState.response.destination;
		i++;
	
	}while(destination!=0 && i<10);
	
	return handle;
			
}


//Fonction permettant d'obtenir le handle d'une navette qui vient d'être créée
int Commande::NouvelleNavette()
{
	return NewHandle;
}


//Fonction permettant de réinitialiser la variable globale contenant le handle d'une navette qui vient d'être créée
void Commande::ReinitialiserNouvelleNavette()
{
	NewHandle=0;
}

//Fonction permettant de détruire une navette
void Commande::DestroyShuttle(int handle)
{
	cout << "destuction naveteeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee" << endl;
	std_msgs::Int32 delmsg;
	delmsg.data = handle;
	cout << delmsg.data << endl;
	pubDestroyShuttle.publish(delmsg);
}



