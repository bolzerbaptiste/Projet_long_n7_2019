/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include "Poste2.h"  

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Constructeur////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
Poste2::Poste2(ros::NodeHandle nh,  std::string executionPath)
{
	cout<<"Initialisation du poste 2"<<endl;
	
// Pour connaitre l'état des capteurs
	VREPsubStopSensor = nh.subscribe("vrep/StopSensor", 10, &Poste2::StopSensorCallback, this);

// Pour arréter et démarrer les navettes
	ShStop = nh.advertise<std_msgs::Int32>("/commande/ArretNavette", 20);
	ShStart = nh.advertise<std_msgs::Int32>("/commande/DemarrerNavette", 20);

// Pour recevoir et envoyer l'etat des navettes	
	subReceiveShuttle = nh.subscribe("/IOShuttle/P1_P2", 10, &Poste2::NewShuttleCallback, this);
	pubSendShuttle = nh.advertise<aiguillages::ExchangeSh>("/IOShuttle/P2_A12", 10);

// Communication avec Commande
	subStartShuttle = nh.subscribe("/Cmde_P2/Demarrage", 10, &Poste2::StartShuttleCallback, this);
	subProductPutOnShuttle = nh.subscribe("/Cmde_P2/ProduitPose", 10, &Poste2::ProductPutOnShuttleCallback, this);
	subProductTakenByRobot = nh.subscribe("/Cmde_P2/ProduitRecupere", 10, &Poste2::ProductTakenByRobotCallback, this);

	pubEmptyShuttleReady= nh.advertise<std_msgs::Int32>("/Cmde_P2/NavetteVidePrete", 10);
	pubProductInPost= nh.advertise<std_msgs::Int32>("/Cmde_P2/ProduitPresentP2", 10);

// Pour gérer les ergots
	pubPinOn = nh.advertise<std_msgs::Int32>("/Poste_Cmde/SortirErgots", 10);
	pubPinOff = nh.advertise<std_msgs::Int32>("/Poste_Cmde/RentrerErgots", 10);

// Communication avec Tâche
	subTaskFinished = nh.subscribe("/Tache_P2/Tache2Finie", 10, &Poste2::TaskFinishedCallback, this);
	pubProductToTask= nh.advertise<std_msgs::Int32>("/P2_Tache/ProduitATraiter", 10);
	
// Pour communiquer avec le noeud de navettes
	clientGetShuttleStatus = nh.serviceClient<shuttles::srvGetShuttleStatus>("/commande_navette/srvGetShuttleStatus");

	pubProductChange = nh.advertise<shuttles::msgShuttleChange>("/commande_navette/ShuttlePChange", 10);
	pubDestinationChange = nh.advertise<shuttles::msgShuttleChange>("/commande_navette/ShuttleDChange", 10);

// Pour gérer les couleurs des plateformes
	pubChangeColor = nh.advertise<commande_locale::Msg_Color>("/commande_locale/Change_Color", 10);

// Pour initialiser la gestion des capteurs
	PS22_past=0;

// Pour initialiser les postes
	tache=0;
	poste_libre=1;
	prod_recup=0;	//variable à 1 quand le robot récupère un produit sur une navette pour la traiter

	num_capt_stop=22;
	num_STOP.data=num_capt_stop;

	num_ergot=8;
	num_PIN.data=num_ergot;


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
	std::string pNameFF,destinationPart,jobTimePart,contents;

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
			ROS_INFO("Product %s",pNameFF.c_str());
			destinationPart = contents.substr(pos2+1,pos3-pos2-1);
			ROS_INFO("destination part =%s",destinationPart.c_str());
			jobTimePart = contents.substr(pos3+1);
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
			int nextDestination;


	//  Pour gérer le n° de la prochaine destination d'un produit
			for (int i = 0; i < manRSize; i++)	
				{

				if(destination[i] == 2)		
					{
					pNumber = pNumberBase + i; 		
					if ( i+1 == manRSize )  // Si i+1 est égal au nombre d'étapes de fabrication du produit 
						{
						nextDestination = 5; 	// Destination qui correspond à la sortie 
						}
					else 	nextDestination = destination[i+1]; // On affecte la prochaine destination définie par le gamme
					initProduct(nextDestination,pNumber);
					}
	
				}
		
			}
		}

	streamConfigFile.close(); //fermeture du fichier ProductConfiguration.txt ouvert en lecture//

}
else ROS_ERROR("Impossible d'ouvrir le fichier ProductConfiguration.txt !");
}

// Fin de l'initialisation


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Callback////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//StopSensor
void Poste2::StopSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	//Récupération de la valeur de PS22
	 	PS22 = (msg->data & (int32_t)pow(2,21)) > 0;

	if(PS22)
	{
		if(!PS22_past)
		{
			PS22_past=PS22;
		}
	}
	else if(PS22_past)
	{
		PS22_past=PS22;
	}
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////   Commande Poste  /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// Fonction Callback pour remplir une liste (FIFO) avec les handles des navettes créées
void Poste2::NewShuttleCallback (const std_msgs::Int32::ConstPtr& msg) {

	int shuttleNew =  msg->data;
	int destination;
	int produit;

		ROS_INFO("Recuperation via service info navette d'handle %d",shuttleNew );
		ShuttleInfo.request.handle = shuttleNew;  	

	if (clientGetShuttleStatus.call(ShuttleInfo)){
		ROS_INFO("%s , destination %d , produit %d, handle de la plateforme %d, zone %d" ,ShuttleInfo.response.name.c_str(),ShuttleInfo.response.destination ,ShuttleInfo.response.product, ShuttleInfo.response.handlePlatform, ShuttleInfo.response.zone);
		
		handlesShuttles.push_back(shuttleNew);	//Pour remplir la liste par le bas
		handlesShuttlesMain.push_back(shuttleNew);	//Pour remplir la liste par le bas

		destination = ShuttleInfo.response.destination;
		destinationsShuttles.push_back(destination);	
		destinationsShuttlesMain.push_back(destination);	

		produit = ShuttleInfo.response.product;
		productShuttles.push_back(produit);
		productShuttlesMain.push_back(produit);

		//Pour afficher le contenu de la liste
 		std::cout << "Contenu de la liste des handles: "<<std::endl;
  		list<int>::iterator p = handlesShuttles.begin();

  		while(p != handlesShuttles.end()) {
   			std::cout << *p << " "<<std::endl;
    			p++;
		}

 		std::cout << "Contenu de la liste des destinations: "<<std::endl;
  		list<int>::iterator m = destinationsShuttles.begin();

  		while(m != destinationsShuttles.end()) {
   			std::cout << *m << " "<<std::endl;
    			m++;
		}

 		std::cout << "Contenu de la liste des produits: "<<std::endl;
  		list<int>::iterator n = productShuttles.begin();

  		while(n != productShuttles.end()) {
   			std::cout << *n << " "<<std::endl;
    			n++;
		}
	}

	else{
		ROS_WARN("Cette navette n'existe pas");
	}
}

// Fonction Callback si la commande veut redémarrer la navette
void Poste2::StartShuttleCallback(const std_msgs::Int32::ConstPtr& msg){

	aiguillages::ExchangeSh num_handle;

	pubPinOff.publish(num_PIN);
	ShStart.publish(num_STOP);

	ROS_INFO("Redemarrage de la navette");

	while(PS22_past && PS22){
		ros::spinOnce();
	}

	num_handle.handle = handlesShuttles.front();
			
	PS22_past = PS22;
	poste_libre = 1;
	
	pubSendShuttle.publish(num_handle); // Pour envoyer le numéro du handle de la navette à A12

	// Pour supprimer la première ligne des listes
	handlesShuttles.pop_front();
	destinationsShuttles.pop_front();
	productShuttles.pop_front();		
}

//Fonction Callback si un produit est posé sur la navette
void Poste2::ProductPutOnShuttleCallback(const std_msgs::Int32::ConstPtr& msg){
	
	aiguillages::ExchangeSh num_handle;


	tache = 0;
	prod_recup = 0;
	num_handle.handle = handlesShuttles.front();

////////////////////////////////////////////////////////////////////////////
	//Pour que le poste attribue lui-même la nouvelle destination
////////////////////////////////////////////////////////////////////////////

/*	int nouvelle_destination;
	std::map<int,ProductPost*>::iterator it;
	ProductPost* pointerProduct;

	it = ProductsMap.find(nouveau_produit-1);	// find() améne l'itérateur à l'emplacement permetant la bonne clé

	if (it != ProductsMap.end()) {		// Vrai si l'itérateur n'est pas hors de la liste
		pointerProduct = it->second;
		nouvelle_destination = pointerProduct->nextDestination;				
	}

	Newdestination.handle = num_handle.data;
	Newdestination.argument = nouvelle_destination;
	pubDestinationChange.publish(Newdestination); // Renseigne la nouvelle destination au service
*/

////////////////////////////////////////////////////////////////////////////
						
	ROS_INFO("Un produit est pose sur la navette");

	// Pour changer la couleur de la plateforme
	PlatformColor.Color = nouveau_produit;
	PlatformColor.Handle = num_handle.handle;
	pubChangeColor.publish(PlatformColor);


	NewProduct.handle = num_handle.handle;
	NewProduct.argument = nouveau_produit;  
	pubProductChange.publish(NewProduct);	// Renseigne le nouveau produit au service 

	pubPinOff.publish(num_PIN);
	ShStart.publish(num_STOP);

	while(PS22_past && PS22){
		ros::spinOnce();
	}
			
	PS22_past = PS22;
	poste_libre = 1;
	
	pubSendShuttle.publish(num_handle);

	handlesShuttles.pop_front();
	destinationsShuttles.pop_front();
	productShuttles.pop_front();	
}


//Fonction Callback si un produit est récupéré par le robot
void Poste2::ProductTakenByRobotCallback(const std_msgs::Int32::ConstPtr& msg){
	
	aiguillages::ExchangeSh num_handle;
	int nouvelle_destination;


	prod_recup = 1;
	num_handle.handle = handlesShuttles.front();

	ROS_INFO("Le produit est recupere - Navette vide");

	nouveau_produit = 0;  
	nouvelle_destination = 0;

	// Pour changer la couleur de la plateforme
	PlatformColor.Color = nouveau_produit;
	PlatformColor.Handle = num_handle.handle;
	pubChangeColor.publish(PlatformColor);


	NewProduct.handle = num_handle.handle;
	NewProduct.argument = nouveau_produit;
	pubProductChange.publish(NewProduct);

	Newdestination.handle = num_handle.handle;
	Newdestination.argument = nouvelle_destination;
	pubDestinationChange.publish(Newdestination);

	pubPinOff.publish(num_PIN);
	ShStart.publish(num_STOP);

	while(PS22_past && PS22){
		ros::spinOnce();
	}
			
	PS22_past = PS22;
	poste_libre = 1;

	pubSendShuttle.publish(num_handle);

	handlesShuttles.pop_front();
	destinationsShuttles.pop_front();
	productShuttles.pop_front();	
}


// Fonction Callback pour savoir quand la tâche est finie
void Poste2::TaskFinishedCallback(const std_msgs::Int32::ConstPtr& msg){

		nouveau_produit = msg->data;

		ROS_INFO("Tache terminee");
		tache = 1;
}


// Fonction Init pour créer un produit
void Poste2::initProduct(int nDestination, int pNumber)
{

	ROS_INFO("Creation Produit, next destination = %d, numero produit = %d ", nDestination,pNumber);

		// Création dynamique de l'object product
	ProductPost* newProductPost = new ProductPost(nDestination,pNumber);

		// Insertion dans le map de la classe de la paire <key=pNumber,T=Product*>

	std::pair<std::map<int,ProductPost*>::iterator,bool> ret;			// ret permet d'avoir un retour de la fonction insert, il est faux si la key existe dèjà dans la map
	ret = ProductsMap.insert(std::pair<int,ProductPost*>(newProductPost->productNumber,newProductPost));

	if (ret.second==false)	// Si un produit avec le même nom existe dèjà, celui-ci n'est pas ajouté à la collection
	{
    		ROS_WARN("Ordonnanceur : Un Produit de ce nom existe dèjà !"); 
  	} 

}

	
