/**** Projet long N7 2017 ****/

#include "tache4.h"


//Constructeur
Tache4::Tache4()
{}



//Destructeur
Tache4::~Tache4()
{}



/** Fonction interne permettant d'évacuer le produit de la table lorsque le robot l'a récupéré **/
//Fonction permettant de changer la couleur de la table lorsque le traitement est terminé
void Tache4::FinTraitementProduit(int numTable)
{
	if((numTable == 1)&&(position==4)&&(bras == 1)&&(pince == 1))
	{
		srv_simRosColor.request.signalName = table;
		srv_simRosColor.request.signalValue = 0; //couleur de base
		client_simRosColor.call(srv_simRosColor);

		finTraitement = -1;
		oldproduit = -1;
	}
}




/** Fonctions permettant de connaître la position du robot ainsi que l'état de la pince et du bras **/
//Fonction Callback permettant de récupérer la position du robot 1
void Tache4::PositionRobotCallback(const std_msgs::Int32::ConstPtr& msg)
{
	position = msg->data;
}



//Fonction Callback permettant de récupérer l'état du bras du robot 1
void Tache4::BrasRobotCallback(const std_msgs::Int32::ConstPtr& msg)
{
	bras = msg->data;
}



//Fonction Callback permettant de récupérer l'état de la pince du robot 1
void Tache4::PinceRobotCallback(const std_msgs::Int32::ConstPtr& msg)
{
	pince = msg->data;
}



/** Fonction permettant le traitement d'un produit à la réception du message venant du noeud Poste associé **/
//Fonction Callback permettant de traiter le produit s'il est en position
void Tache4::TraitementProduitCallback(const std_msgs::Int32::ConstPtr& msg)
{
	produit=msg->data;	

	finTraitement = 0;
	retourTraitement.data=0;
		
	while(finTraitement != -1)
	{
		ros::spinOnce();
		if(produit != oldproduit)
		{
			if((position==4)&&(bras==0)&&(pince==0))
			{
				//Coloration de la table associée à la tâche lors de la réception du produit
				srv_simRosColor.request.signalName = table;
				srv_simRosColor.request.signalValue = produit;
				client_simRosColor.call(srv_simRosColor);
				
				//Traitement du produit
				//Temps de Traitement du produit
				
				iteratorPMap = ProductsMap.find(produit);
				ProductTache* productPointer;

				if (iteratorPMap != ProductsMap.end()) // Vrai si l'itérateur n'est pas hors de la liste
				{
					productPointer = iteratorPMap->second;

					client_simGetVrepTime.call(srv_simGetVrepTime);
					t0 = srv_simGetVrepTime.response.simulationTime;
					time = t0;
					while(time - t0 < productPointer->jobTime)
					{
						client_simGetVrepTime.call(srv_simGetVrepTime);
						time = srv_simGetVrepTime.response.simulationTime;
					}
					//Fin de traitement
					produit++;
					oldproduit = produit;		
	
					srv_simRosColor.request.signalValue = produit;
					client_simRosColor.call(srv_simRosColor);
		
					//Retour du traitement vers le node poste associé
					traitementProduit.data = produit;
					pub_traitementProduitTache.publish(traitementProduit);
	
					//Retour du traitement vers le node commmande		
					retourTraitement.data=1;
	
					finTraitement = 1;
				}		
			}
		
			pub_retourTraitement.publish(retourTraitement);
		}

		FinTraitementProduit(finTraitement);
	}
}




/** Initialisation **/
//Initialisation des différents services, publishers et subscribers
void Tache4::init(ros::NodeHandle noeud, std::string executionPath)
{
	//Déclaration service simRosSetIntegerSignal
	client_simRosColor = noeud.serviceClient<vrep_common::simRosSetIntegerSignal>("/vrep/simRosSetIntegerSignal");

	//Déclaration service simRosGetInfo
	client_simGetVrepTime = noeud.serviceClient<vrep_common::simRosGetInfo>("/vrep/simRosGetInfo");


	//Subscribers
	robotPosition = noeud.subscribe("/robot/PositionRobot2", 10, &Tache4::PositionRobotCallback, this);
	
	robotBras = noeud.subscribe("/robot/BrasRobot2",10,&Tache4::BrasRobotCallback,this);

	robotPince = noeud.subscribe("/robot/PinceRobot2",10,&Tache4::PinceRobotCallback,this);

	posteProduit = noeud.subscribe("/P4_Tache/ProduitATraiter",10,&Tache4::TraitementProduitCallback,this);


	//Publishers	
	pub_traitementProduitTache = noeud.advertise<std_msgs::Int32>("/Tache_P4/Tache4Finie",10);

	pub_retourTraitement = noeud.advertise<std_msgs::Int32>("/commande/Simulation/ProduitTraitement4",10);


	//Définition des noms des signaux
	table = "Table#4_color";


	//Initialisation des variables de retour du robot
	position = -1;
	bras = -1;
	pince = -1;
	oldproduit = -1;


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
		std::string pNameFF,destinationPart,jobTimePart,contents;

		//saut des lignes d'entêtes, repèrage du start.
		while(1)
		{
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
				ROS_INFO("Product %s",pNameFF.c_str());
				destinationPart = contents.substr(pos2+1,pos3-pos2-1);
				ROS_INFO("destination part =%s",destinationPart.c_str());
				jobTimePart = contents.substr(pos3+1);
				ROS_INFO("jobTimePart =%s",jobTimePart.c_str());
				int destination[10];
				int jobTime[10];
				int manRSize = 0; //manufacturing range size of the produit = number of operation

				char * cstr2 = new char [destinationPart.length()+1]; 
		  		std::strcpy (cstr2, destinationPart.c_str());	// création objet cstring
				char * cstr3 = new char [jobTimePart.length()+1]; 
		  		std::strcpy (cstr3, jobTimePart.c_str());

		  		// cstr now contains a c-string copy of str
				int n2 = 0; //compteur sur les destinations
				int n3 = 0; //compteur sur les temps de fabrications
		 	 	

				char * p2 = std::strtok (cstr2," ");
		  		while (p2!=NULL)
		  		{
					destination[n2++] = atoi(p2);
					manRSize++ ;
		  			p2 = std::strtok(NULL," ");
		  		}

				char * p3 = std::strtok (cstr3," ");
				while (p3!=NULL)
		  		{
					jobTime[n3++] = atoi(p3);
		  			p3 = std::strtok(NULL," ");
		  		}

		  		delete[] cstr2;
				delete[] cstr3; 


				char charName;
				charName = char(pNameFF.c_str()[0]-16);
				int pNumberBase = atoi(&charName) * 10 ; 
				int pNumber;
				int JobTimeProduct;


				//  Pour gérer le n° de la prochaine destination d'un produit
				for (int i = 0; i < manRSize; i++)	
				{

					if(destination[i] == 4)		
					{
						pNumber = pNumberBase + i; 		
						JobTimeProduct = jobTime[i];
						initProduct(JobTimeProduct,pNumber);
					}
	
				}
		
			}
		}

		streamConfigFile.close(); //fermeture du fichier ProductConfiguration.txt ouvert en lecture//

	}
	else ROS_ERROR("Impossible d'ouvrir le fichier ProductConfiguration.config !");

}



// Fonction Init du fichier configuration pour créer un produit
void Tache4::initProduct(int nJobtime, int pNumber)
{

	ROS_INFO("Creation Produit, temps de traitement = %d, numero produit = %d ", nJobtime,pNumber);

		// Création dynamique de l'object product
	ProductTache* newProductTache = new ProductTache(nJobtime,pNumber);

		// Insertion dans le map de la classe de la paire <key=pNumber,T=Product*>

	std::pair<std::map<int,ProductTache*>::iterator,bool> ret;			// ret permet d'avoir un retour de la fonction insert, il est faux si la key existe dèjà dans la map
	ret = ProductsMap.insert(std::pair<int,ProductTache*>(newProductTache->productNumber,newProductTache));

	if (ret.second==false)	// Si un produit avec le même nom existe déjà, celui-ci n'est pas ajouté à la collection
	{
    		ROS_WARN("Ordonnanceur : Un Produit de ce nom existe deja !"); 
  	} 

}
