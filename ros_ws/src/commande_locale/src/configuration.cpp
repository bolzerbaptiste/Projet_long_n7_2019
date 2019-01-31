/**** Maxime Maurin - Projet Long N7 2017 ****/

#include <ros/ros.h>
#include "configuration.h"

// Construteur
Configuration::Configuration(vrepController* VREPC)
{
	vrepCAcces = VREPC;
	numberOfProduct = 0;
	for ( int i = 1 ; i < 7 ; i++) activeProduct[i]=false;
	activeProduct[0] = true;
	maxShuttleNumber = 6;
}

// Initialisation de l'objet 
bool Configuration::init(ros::NodeHandle nh, std::string executionPath)
{
	// Services Initialisation
	client_simRosGetInfo = nh.serviceClient<vrep_common::simRosGetInfo>("/vrep/simRosGetInfo");

	// Publishers Initialisation 
	pubManualProduct = nh.advertise<std_msgs::Bool>("/scheduling/ManualLaunch",10);

// Récupération du chemin vers le Working_Folder
int count = 0 ;
int pos = 0 ;
while (count < 4)
	{
	if(executionPath[pos] == '/') count++;
	pos++;
	}
std::string Working_Folder = executionPath.substr(0,pos);
ROS_INFO ("$%s$", Working_Folder.c_str()) ;

	
//Initialisation des produits à l'aide du fichier de configuration

	//Définition du chemin du fichier de config et log
configFile = Working_Folder + "/ProductConfiguration.config";
logFile = Working_Folder + "/Statistic.txt";

std::ifstream streamConfigFile(configFile.c_str(), std::ios::in);
	
if (streamConfigFile)
{
	std::string pNameFF,destinationPart,maxShuttlePart,contents;

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
	std::size_t pos0 = contents.find(":");
	maxShuttlePart = contents.substr(pos0+1);
	//ROS_INFO("maxShuttlePart =%s",maxShuttlePart.c_str());
	maxShuttleNumber = atoi( maxShuttlePart.c_str());
	ROS_INFO("maxShuttleNumber = %d",maxShuttleNumber);

	//Configuration temps entre lancement
	std::getline(streamConfigFile,contents);
	
	while (std::getline(streamConfigFile, contents))
		{

		//ROS_INFO("%s",contents.c_str())	;
		std::size_t pos2 = contents.find(":");
		std::size_t pos3 = contents.find_last_of(":");
		
		pNameFF = contents.substr(0,pos2);
		ROS_INFO("Product %s",pNameFF.c_str());
		destinationPart = contents.substr(pos2+1,pos3-pos2-1);
		
		int destination[10];
		int jobTime[10];
		int manRSize = 0; //manufacturing range size of the product = number of operation

		char * cstr2 = new char [destinationPart.length()+1]; 
  		std::strcpy (cstr2, destinationPart.c_str());	// création objet cstring

  		// cstr now contains a c-string copy of str
		int n2 = 0; //compteur sur les destinations
 	 	

		char * p2 = std::strtok (cstr2," ");
  		while (p2!=NULL)
  			{
    			//ROS_INFO ("p2 = %s",p2) ;
			destination[n2++] = atoi(p2);
			manRSize++ ;
			ROS_INFO ("destination %d = %d",n2-1,destination[n2-1]);
  			p2 = std::strtok(NULL," ");
			//ROS_INFO ("p2 = %s",p2) ;
  			}

  		delete[] cstr2;

		char charName;
		charName = char(pNameFF.c_str()[0]-16);
		
		int index = atoi(&charName) ;
		int pNumber = index * 10 ;
		activeProduct[index] = true;
		
		initProduct(pNameFF,destination[0], pNumber, manRSize);
		numberOfProduct++;
	
	}
	ROS_INFO("Number of Product = %d", numberOfProduct);
	iteratorPMap = ProductsMap.begin();

	streamConfigFile.close(); //fermeture du fichier ProductConfiguration.txt ouvert en lecture//

}
else ROS_ERROR("Impossible d'ouvrir le fichier ProductConfiguration.txt !");
return false;
}

// Destructor
Configuration::~Configuration()
{
}


// Scheduling Function
void Configuration::ProductAdd(char shuttleLetter, int typeNextShuttle){

	client_simRosGetInfo.call(srv_GetInfoVREP);
	int firstDestination;

	if (typeNextShuttle > 0)
		{
		std::string ProductName;
		Product* productPointer;
		bool ok = false;

		for (iteratorPMap=ProductsMap.begin(); iteratorPMap!=ProductsMap.end(); ++iteratorPMap)	// On parcours l'ensemble de la collection
			{
				productPointer = iteratorPMap->second;
				if ( productPointer->productNumber == typeNextShuttle ) // Trouve le nom du produit fini
					{
						//ROS_INFO ( "j'ai trouvé le nom du produit !!");
						ProductName = productPointer->name;
						firstDestination = productPointer->firstDestination;
						ok = true;
					}
			}
		iteratorPMap=ProductsMap.begin();
		if (ok)
			{
			int handle = vrepCAcces->LoadShuttle(shuttleLetter,typeNextShuttle,firstDestination);
			//ECRITURE LOG FILE///////////////////////////////////////////////////////////////////////////
			std::ofstream StatsFile(logFile.c_str(), std::ios::out | std::ios::app);
			if(StatsFile)  // si l'ouverture a réussi...
				{
		
				//ROS_INFO("Statistic.txt file ok");
				char logLine[1000];
				// Construction Ligne avec notamment la date de lancement 
				sprintf(logLine, "Produit %s lance a temps Vrep = %f s\n",ProductName.c_str(), srv_GetInfoVREP.response.simulationTime);
				ROS_INFO("Produit %s lance a temps Vrep = %f s\n",ProductName.c_str(), srv_GetInfoVREP.response.simulationTime);
				StatsFile << logLine; // Ecriture dans le fichier 
				StatsFile.close();  // on referme le fichier Statistic.txt

				}
			else ROS_ERROR("Impossible de creer ou ouvrir le fichier Statistic.txt !");
			/////////////////////////////////////////////////////////////////////////////////////////////
			}
		else ROS_ERROR("Probleme Configuration Commande Locale :: Valeur retourné par la trackbar non conforme !!!! " ) ;
		}
	
	if (typeNextShuttle == 0)
		{
		
		int handle = vrepCAcces->LoadShuttle(shuttleLetter,0,0);

		//ECRITURE LOG FILE///////////////////////////////////////////////////////////////////////////
		std::ofstream StatsFile(logFile.c_str(), std::ios::out | std::ios::app);
		if(StatsFile)  // si l'ouverture a réussi...
			{
		
			//ROS_INFO("Statistic.txt file ok");
			char logLine[1000];
			// Construction Ligne avec notamment la date de lancement 
			sprintf(logLine, "Navette vide lance a temps Vrep = %f s\n", srv_GetInfoVREP.response.simulationTime);
			ROS_INFO("Navette vide lance a temps Vrep = %f s\n", srv_GetInfoVREP.response.simulationTime);
			StatsFile << logLine; // Ecriture dans le fichier 
			StatsFile.close();  // on referme le fichier Statistic.txt

			}
		else ROS_ERROR("Impossible de creer ou ouvrir le fichier Statistic.txt !");
		/////////////////////////////////////////////////////////////////////////////////////////////

		}

	
	if (typeNextShuttle == -1)
		{

		std::string ProductName;
		Product* productPointer;

		int tirage = rand() % numberOfProduct;
		for (  int i = 0 ; i <= tirage ;i++) iteratorPMap++;
		productPointer = iteratorPMap->second;
		ProductName = productPointer->name;
		firstDestination = productPointer->firstDestination;
		int product  = productPointer->productNumber;
		iteratorPMap = ProductsMap.begin();
		
		int handle = vrepCAcces->LoadShuttle(shuttleLetter,product,firstDestination);
		//ECRITURE LOG FILE///////////////////////////////////////////////////////////////////////////
		std::ofstream StatsFile(logFile.c_str(), std::ios::out | std::ios::app);
		if(StatsFile)  // si l'ouverture a réussi...
			{
		
			//ROS_INFO("Statistic.txt file ok");
			char logLine[1000];
			// Construction Ligne avec notamment la date de lancement 
			sprintf(logLine, "Produit %s lance a temps Vrep = %f s\n",ProductName.c_str(), srv_GetInfoVREP.response.simulationTime);
			ROS_INFO("Produit %s lance a temps Vrep = %f s\n",ProductName.c_str(), srv_GetInfoVREP.response.simulationTime);
			StatsFile << logLine; // Ecriture dans le fichier 
			StatsFile.close();  // on referme le fichier Statistic.txt

			}
		else ROS_ERROR("Impossible de creer ou ouvrir le fichier Statistic.txt !");
		/////////////////////////////////////////////////////////////////////////////////////////////
	
		}



	std_msgs::Bool msgO;
	msgO.data = true;
	pubManualProduct.publish(msgO); // On informe ordonnancement qu'une navette avec un produit a été lancé.

}


// Création de produit
void Configuration::initProduct(std::string pName, int pFirstDestination, int initProductNumber, int pManRSize)
{
	ROS_INFO("Creation Produit %s, first destination = %d, numero produit = %d , taille gamme = %d", pName.c_str(), pFirstDestination,initProductNumber, pManRSize);

		// Création dynamique de l'object product
	Product* newProduct = new Product(pName,pFirstDestination,initProductNumber, pManRSize);

		// Insertion dans le map de la classe de la paire <key=handle,T=Product*>

	std::pair<std::map<std::string,Product*>::iterator,bool> ret;			// ret permet d'avoir un retour de la fonction insert, il est faux si la key existe dèjà dans la map
	ret = ProductsMap.insert(std::pair<std::string,Product*>(newProduct->name,newProduct));
	//ROS_INFO("Product pointer : %p ", newProduct);

	if (ret.second==false)	// Si un produit avec le même nom existe dèjà, celui-ci n'est pas ajouté à la collection
	{
    		ROS_WARN("commande_locale/config : Un produit de ce nom existe deja ! (%s) ", newProduct->name.c_str()); 
  	} 
} 



	
