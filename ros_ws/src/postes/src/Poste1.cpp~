/*
 * ************************************* *
 * 	  Projet Long N7 2017  	         *
 * ************************************* *
*/

#include "Poste1.h"  

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Constructeur////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
Poste1::Poste1(ros::NodeHandle nh,  std::string executionPath)
{
	cout<<"Initialisation du poste 1"<<endl;
	
// Pour connaitre l'état des capteurs stop
	VREPsubStopSensor = nh.subscribe("vrep/StopSensor", 10, &Poste1::StopSensorCallback, this);

// Pour arrêter et démarrer les navettes
	ShStop = nh.advertise<std_msgs::Int32>("/commande/ArretNavette", 20);
	ShStart = nh.advertise<std_msgs::Int32>("/commande/DemarrerNavette", 20);

// Pour recevoir et envoyer le numéro de handle des navettes 
	subReceiveShuttle = nh.subscribe("/IOShuttle/A11_P1", 10, &Poste1::NewShuttleCallback, this);	// Reçoit le numéro de handle de la navette venant de A11
	pubSendShuttle = nh.advertise<std_msgs::Int32>("/IOShuttle/P1_P2", 10);	// Envoie le numéro de handle de la navette à P2

// Communication avec Commande
	subStartShuttle = nh.subscribe("/Cmde_P1/Demarrage", 10, &Poste1::StartShuttleCallback, this);	// Si on veut rédemarrer la navette sans attendre une action du robot
	subProductPutOnShuttle = nh.subscribe("/Cmde_P1/ProduitPose", 10, &Poste1::ProductPutOnShuttleCallback, this);	// Pour savoir quand un produit est posé sur la navette
	subProductTakenByRobot = nh.subscribe("/Cmde_P1/ProduitRecupere", 10, &Poste1::ProductTakenByRobotCallback, this);	// Pour savoir quand le produit a été récupéré par le robot

	pubEmptyShuttleReady= nh.advertise<std_msgs::Int32>("/Cmde_P1/NavetteVidePrete", 10);	// Signale à la commande qu'une navette vide est présente au poste
	pubProductInPost= nh.advertise<std_msgs::Int32>("/Cmde_P1/ProduitPresentP1", 10);	// Signale à la commande qu'une navette est au poste avec un produit à traiter

// Pour gérer les ergots
	pubPinOn = nh.advertise<std_msgs::Int32>("/Poste_Cmde/SortirErgots", 10);	// Pour sortir les ergots
	pubPinOff = nh.advertise<std_msgs::Int32>("/Poste_Cmde/RentrerErgots", 10);	// Pour rentrer les ergots

// Communication avec Tâche
	subTaskFinished = nh.subscribe("/Tache_P1/Tache1Finie", 10, &Poste1::TaskFinishedCallback, this);	// Pour savoir quand une tâche est finie
	pubProductToTask= nh.advertise<std_msgs::Int32>("/P1_Tache/ProduitATraiter", 10);	// Envoie à tâche le numéro du produit à traiter
	
// Pour communiquer avec le noeud de navettes
	clientGetShuttleStatus = nh.serviceClient<shuttles::srvGetShuttleStatus>("/commande_navette/srvGetShuttleStatus");	// Pour récupérer toutes les informations d'une navette

	pubProductChange = nh.advertise<shuttles::msgShuttleChange>("/commande_navette/ShuttlePChange", 10);	// Renseigne le noeud shuttle du nouveau numéro du produit
	pubDestinationChange = nh.advertise<shuttles::msgShuttleChange>("/commande_navette/ShuttleDChange", 10);	// Renseigne le noeud shuttle de la nouvelle destination

// Pour gérer les couleurs des plateformes
	pubChangeColor = nh.advertise<commande_locale::Msg_Color>("/commande_locale/Change_Color", 10);

// Pour initialiser la gestion des capteurs
	PS21_past=0;

// Pour initialiser les postes
	tache=0;
	poste_libre=1;
	prod_recup=0;	//variable à 1 quand le robot récupère un produit sur une navette pour la traiter

	num_capt_stop=21;	// Numéro de l'actionneur, au poste 1 c'est ST21
	num_STOP.data=num_capt_stop;	// Pour remplir les données du message qui sera transmis à la commande

	num_ergot=7;	// Numéro de l'actionneur, au poste 1 c'est l'ergot n°7
	num_PIN.data=num_ergot;	// Pour remplir les données du message qui sera transmis à la commande


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

				if(destination[i] == 1)		
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
else ROS_ERROR("Impossible d'ouvrir le fichier ProductConfiguration.config !");


}
// Fin de l'initialisation


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Callback////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

//StopSensor
void Poste1::StopSensorCallback(const std_msgs::Int32::ConstPtr& msg)
{
	//Récupération de la valeur de PS21
	 	PS21 = (msg->data & (int32_t)pow(2,20)) > 0;

	if(PS21)
	{
		if(!PS21_past)
		{
			PS21_past=PS21;
		}
	}
	else if(PS21_past)
	{
		PS21_past=PS21;
	}
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////   Commande Poste  /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// Fonction Callback pour remplir une liste (FIFO) avec les handles des navettes créées
void Poste1::NewShuttleCallback (const aiguillages::ExchangeSh::ConstPtr& msg) {

	int shuttleNew =  msg->handle; 	// shuttleNew = données du message handle = valeur du handle de la navette qui arrive
	int destination;
	int produit;

		ROS_INFO("Recuperation via service info navette d'handle %d",shuttleNew );
		ShuttleInfo.request.handle = shuttleNew;	// On remplie le message ShuttleInfo avec le handle de la navette (il a seulement besoin du handle)

	if (clientGetShuttleStatus.call(ShuttleInfo)){	// On appelle le service qui a besoin du n° de handle pour retourner toutes les informations d'une navette
		ROS_INFO("%s , destination %d , produit %d, handle de la plateforme %d, zone %d" ,ShuttleInfo.response.name.c_str(),ShuttleInfo.response.destination ,ShuttleInfo.response.product, ShuttleInfo.response.handlePlatform, ShuttleInfo.response.zone);
		
		// On remplie les listes par le bas
		handlesShuttles.push_back(shuttleNew);	// Liste contenant les n° de handle des navettes
		handlesShuttlesMain.push_back(shuttleNew);	// Liste utilisée dans le main contenant les n° de handle des navettes	

		destination = ShuttleInfo.response.destination;	// On attribue à la variable locale destination la valeur de la destination récupérée avec le service
		destinationsShuttles.push_back(destination);	// Liste contenant la destination des navettes	
		destinationsShuttlesMain.push_back(destination);	// Liste utilisée dans le main contenant la destination des navettes	

		produit = ShuttleInfo.response.product;	// On attribue à la variable locale produit la valeur du produit récupérée avec le service
		productShuttles.push_back(produit);	// Liste contenant les n° de produit
		productShuttlesMain.push_back(produit);	// Liste utilisée dans le main contenant les n° de produit

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

	else{	// Si le n° de handle envoyé au service n'existe pas
		ROS_WARN("Cette navette n'existe pas");
	}
}

// Fonction Callback si la commande veut redémarrer la navette
void Poste1::StartShuttleCallback(const std_msgs::Int32::ConstPtr& msg){

	std_msgs::Int32 num_handle;


	pubPinOff.publish(num_PIN);	// Pour dire à la commande de rentrer les ergots
	ShStart.publish(num_STOP);	// Pour dire à la commande de redémarrer la navette

	ROS_INFO("Redemarrage de la navette");

	while(PS21_past && PS21){	// On attend le front descendant du capteur
		ros::spinOnce();	// Permet aux fonction callback de ros dans les objets d'êtres appelées
	}

	num_handle.data = handlesShuttles.front();	// On lie la première ligne de la liste contenant les identifiants des navettes (handle)
			
	PS21_past = PS21;	// Mise à jour des variables des capteurs
	poste_libre = 1;	// Libération du poste
	
	pubSendShuttle.publish(num_handle); // Pour envoyer le numéro du handle de la navette à P2

	// Pour supprimer la première ligne des listes
	handlesShuttles.pop_front();
	destinationsShuttles.pop_front();
	productShuttles.pop_front();		
}

//Fonction Callback si un produit est posé sur la navette
void Poste1::ProductPutOnShuttleCallback(const std_msgs::Int32::ConstPtr& msg){
	
	std_msgs::Int32 num_handle;

	tache = 0;	// Plus de tâche à récupérer
	prod_recup = 0;	// Pas de produit en cours de traitement

	num_handle.data = handlesShuttles.front(); // on récupère le premier handle reçu


//////////////////////////////////////////////////////////////////////////////
	//Pour que le poste attribue lui-même la nouvelle destination
//////////////////////////////////////////////////////////////////////////////

/*	std::map<int,ProductPost*>::iterator it;
	ProductPost* pointerProduct;
	int nouvelle_destination

	it = ProductsMap.find(nouveau_produit-1);	// find() amène l'itérateur à l'emplacement permetant la bonne clé

	if (it != ProductsMap.end()) {		// Vrai si l'itérateur n'est pas hors de la liste
		pointerProduct = it->second;
		nouvelle_destination = pointerProduct->nextDestination;				
	}

	Newdestination.handle = num_handle.data;
	Newdestination.argument = nouvelle_destination;
	pubDestinationChange.publish(Newdestination); // Renseigne la nouvelle destination au service
*/

////////////////////////////////////////////////////////////////////////////////
	
	// Pour changer la couleur de la plateforme
	PlatformColor.Color = nouveau_produit; // On remplie le message PlatformColor avec le n° du produit
	PlatformColor.Handle = num_handle.data;	// On remplie le message PlatformColor avec le n° de handle de la navette
	pubChangeColor.publish(PlatformColor);	// On publie à la commande locale le message

	ROS_INFO("Un produit est pose sur la navette");

	NewProduct.handle = num_handle.data;	// On remplie le message Newproduct avec le n° de handle de la navette
	NewProduct.argument = nouveau_produit;  // On remplie le message Newproduct avec le n° de produit
	pubProductChange.publish(NewProduct);	// Renseigne le nouveau produit au noeud Shuttle

	pubPinOff.publish(num_PIN);	// Pour dire à la commande de rentrer les ergots
	ShStart.publish(num_STOP);	// Pour dire à la commande de redémarrer la navette

	while(PS21_past && PS21){	// On attend le front descendant du capteur
		ros::spinOnce();	// Permet aux fonction callback de ros dans les objets d'êtres appelées
	}
			
	PS21_past = PS21;	// Mise à jour des variables des capteurs
	poste_libre = 1;	// Libération du poste

	pubSendShuttle.publish(num_handle);	// Pour envoyer le numéro du handle de la navette à P2

	// Pour supprimer la première ligne des listes
	handlesShuttles.pop_front();
	destinationsShuttles.pop_front();
	productShuttles.pop_front();	
}


//Fonction Callback si un produit est récupéré par le robot
void Poste1::ProductTakenByRobotCallback(const std_msgs::Int32::ConstPtr& msg){
	
	std_msgs::Int32 num_handle;
	int nouvelle_destination;

	prod_recup = 1; // Pour dire qu'un produit est en cours de traitement
	num_handle.data = handlesShuttles.front();	

	ROS_INFO("Le produit est recupere - Navette vide");

	nouveau_produit = 0;	// On attribue par défaut la valeur 0 au produit pour dire qu'on a une navette vide  
	nouvelle_destination = 0;	// On attribue par défaut la valeur 0 à la destination d'une navette vide

	// Pour changer la couleur de la plateforme
	PlatformColor.Color = nouveau_produit;
	PlatformColor.Handle = num_handle.data;
	pubChangeColor.publish(PlatformColor);

	// Pour renseigner le noeud Shuttle du nouveau n° du produit
	NewProduct.handle = num_handle.data;
	NewProduct.argument = nouveau_produit;
	pubProductChange.publish(NewProduct);

	// Pour renseigner le noeud Shuttle de la nouvelle destination de la navette
	Newdestination.handle = num_handle.data;
	Newdestination.argument = nouvelle_destination;
	pubDestinationChange.publish(Newdestination);


	pubPinOff.publish(num_PIN);
	ShStart.publish(num_STOP);

	while(PS21_past && PS21){
		ros::spinOnce();
	}
			
	PS21_past = PS21;
	poste_libre = 1;

	pubSendShuttle.publish(num_handle);

	// Pour supprimer la première ligne des listes
	handlesShuttles.pop_front();
	destinationsShuttles.pop_front();
	productShuttles.pop_front();	
}


// Fonction Callback pour savoir quand la tâche est finie
void Poste1::TaskFinishedCallback(const std_msgs::Int32::ConstPtr& msg){
	
		nouveau_produit = msg->data;	// On récupère le nouveau n° du produit

		ROS_INFO("Tache terminee");
		tache = 1;	// Pour dire qu'une tâche est finie
}


// Fonction Init du fichier configuration pour créer un produit
void Poste1::initProduct(int nDestination, int pNumber)
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

	
